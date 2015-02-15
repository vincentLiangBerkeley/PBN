#include "Iterator.h"
#include <cstdlib>
#include <queue>
#include <math.h>
#include <random>
#include <algorithm>
#include <sstream>
#include <chrono>
static const double LIMIT = 0.001;
static const double SANITY = 0.05;
const int ITERATION_NUM = 1000;

int minIndex(vector<double>& entropies);

Iterator::Iterator(Iterator::IteratorStatus status, Iterator::RandomTypes type){
	this->status = status;		
	this->type = type;
}

Iterator::fileStates Iterator::readFile(string fileName, int numOfGenes){
	FOLDER = "../Input/" + getStatus();
	// Also set prefix here for output purpose
	this->filename = fileName;
	string matrix = FOLDER + this->filename + ".txt";
	ifstream input;
	input.open(matrix.c_str());

	// Catch the exception where the file does not exist
	if (input.fail()){
		ostringstream os;
		os << matrix + " cannot be opened, please check!\n";
		os << "Please make sure the input files are in the same folder with 'Source'\n";
		os << "Current directory is:" << system("pwd") << endl;
		FAILURE_MESSAGE = os.str();
		return READ_FAILURE;
	}

	this->transition = new tMatrix(numOfGenes);
	for (int i = 0; i < this->transition->getSize(); ++i){
		for (int j = 0; j < this->transition->getSize(); ++j){
			double value;
			input >> value;
			if(value != 0) this->transition->set(i, j, value);
		}
	}
	input.close();
	return READ_SUCCESS;
}

bool Iterator::sanityCheck(){
	// Do a basic sanity check : whether the transition matrix is probabilistic or not
	for (int i = 0; i < this->transition->getSize(); ++i){
		map<int, double> column = this->transition->get(i);
		double sum = 0;
		for (std::map<int, double>::iterator i = column.begin(); i != column.end(); ++i){
			sum += i->second;
		}
		//cout << sum << endl;
		if (sum - 1 < - SANITY || sum - 1 > SANITY){
			ostringstream os;
			os << "The number of genes is wrong with respect to your file : \n"
				<< FOLDER << this->filename << ".txt\n"
			   << "Column " << i + 1 << "'s sum is: " << sum << endl;
			FAILURE_MESSAGE = os.str();
			return false;
		}
	}
	return true;
} 

//#warning Could be improved by returning the elapsed time and display in the Menu object
void Iterator::iterate(){
	BNs.clear();
	qs.clear();
	entropies.clear();
	chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();
	double e;
	if (type == OPTIMAL){
		e = deterministicIterate();
	}else if (type == MAXIMUM){
		e = iterateOnce();
	}else{
		for (int i = 0; i < ITERATION_NUM; ++i){
			e = iterateOnce();
		}
	}

	BNs.push_back(boolNetworks);
	qs.push_back(weights);
	entropies.push_back(e);
	
	chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
	chrono::microseconds ticks = chrono::duration_cast<chrono::microseconds>(end - begin);
	elapsedTime = (double)ticks.count() / 1000000;

	cout << "Elapsed time is: " << elapsedTime << endl;
	if (type != MAXIMUM && type != OPTIMAL) cout << "Average elapsed time per iteration is: " << elapsedTime / ITERATION_NUM << endl;
	saveResult();
}

void Iterator::saveResult(){
	FILEPREFIX = this->filename + RANDOM_TYPE[type];
	int min = minIndex(entropies);
	weights = qs[min];
	boolNetworks = BNs[min];
	saveIteration();
	saveTime();
	saveVector(weights, WEIGHTS);
	saveVector(entropies, ENTROPY);
}

double Iterator::deterministicIterate(){
	tMatrix copy = *this->transition;
	weights.clear();
	boolNetworks.clear();
	while(copy.module() > LIMIT){
		vector<int> rows;
		priority_queue<double> randomWeights;
		for (int col = 0; col < copy.getSize(); ++col){
			map<int, double> column = copy.get(col);

			if (column.empty()) return calculateEntropy(this->weights);
			int row = chooseEntry(column, type);
			randomWeights.push(-column[row]);
		}

		double weight = randomWeights.top();
		
		for (int col = 0; col < copy.getSize(); ++col){
			double closest  = 1.00;
			int chosenRow;
			map<int, double> column = copy.get(col);
			for(map<int, double>::iterator it = column.begin(); it != column.end(); ++it){
				if (it->second >= -weight && it->second + weight < closest){
					closest = it->second + weight;
					chosenRow = it->first;
				}
			}
			rows.push_back(chosenRow);
		}

		// Generate the rMatrix with the rows
		rMatrix A = rMatrix(rows);

		copy += tMatrix::times(A, weight);
		boolNetworks.push_back(A);
		weights.push_back(-weight);
	}
	// cout << copy.module() << endl;
	return calculateEntropy(this->weights);
}

double Iterator::iterateOnce(){
	// The transition matrix must have been initialized for iteration since readFile is called
	tMatrix copy = *this->transition;
	weights.clear();
	boolNetworks.clear();
	while(copy.module() > LIMIT){
		vector<int> rows;
		priority_queue<double> randomWeights;
		// copy.print(cout);
		// cout << "The module is : " << copy.module() << endl;
		// Iterate through the columns of the matrix
		// Choose a row randomly from the column
		for (int col = 0; col < copy.getSize(); ++col){
			map<int, double> column = copy.get(col);

			if (column.empty()) return calculateEntropy(this->weights);
			
			int row = chooseEntry(column, type);
			rows.push_back(row);
			randomWeights.push(-column[row]);
		}

		// Generate the rMatrix with the rows
		rMatrix A = rMatrix(rows);

		double weight = randomWeights.top();

		copy += tMatrix::times(A, weight);
		boolNetworks.push_back(A);
		weights.push_back(-weight);
	}
	// cout << copy.module() << endl;
	return calculateEntropy(this->weights);
}

bool compare(pair<int, double> lhs, pair<int, double> rhs){
	return lhs.second < rhs.second;
}

int Iterator::chooseEntry(map<int, double>& column, RandomTypes type){
	vector<int> rows;//Record the row information
	vector<double> values;//Record the values corresponding to the rows
	vector<double> randomWeights;

	if (type == OPTIMAL || type == MAXIMUM){
		map<int,double>::iterator max = max_element(column.begin(), column.end(), compare);
		return max->first;
	}

	for (std::map<int, double>::iterator it = column.begin(); it != column.end(); ++it){
		rows.push_back(it->first);
		values.push_back(it->second);
		double randomWeight;
		switch (type){
			case QUADRATIC:
				randomWeight = it->second * it->second;
				break;
			case UNIFORM:
				randomWeight = it->second;
				break;
			case CUBIC:
				randomWeight = it->second * it->second * it->second;
				break;
			default :
				cout << "Input random type mistake !" << endl;
				exit(1);	
		}
		randomWeights.push_back(randomWeight);
	}

	// Used to choose a random row according to the weights
	random_device rd;
	mt19937 gen(rd());

	// This is a new feature added to c++11 or GNU
	discrete_distribution<> dis(randomWeights.begin(), randomWeights.end());
	return rows[dis(gen)];
}

void Iterator::saveTime(){
	FOLDER = "../Output/" + getStatus() + "Time/";
	string fileName = getFullPath();
	ofstream output(fileName.c_str());
	output << "Elapsed time is: " << elapsedTime << endl;
	output << "Average elapsed time per iteration is: " << elapsedTime / ITERATION_NUM << endl;
	output.close();
}

void Iterator::saveIteration(){
	FOLDER = "../Output/" + getStatus() + "Iterations/";
	string fileName = getFullPath();
	ofstream output(fileName.c_str());
	output << "The transition matrix is : " << endl;
	this->transition->print(output);

	int minimunm = minIndex(entropies);
	output << "The iteration with least entropy is No. " 
		   << minimunm + 1 << " with entropy: " << entropies[minimunm] << endl;
	output << "This iteration used N = " << boolNetworks.size() << " BNs" << endl;
	output << "The probabilities and corresponding BNs are : " << endl;

	for (int i = 0; i < boolNetworks.size(); ++i){
		output << "\nNo. " << i + 1 << " weights = " << weights[i] << "\nBoolean Matrix = :" << endl;
		boolNetworks[i].print(output);
	}

	output.close();
}

void Iterator::saveVector(vector<double>& stats, FileCoordinator::saveTypes type){
	switch(type){
		case Iterator::ENTROPY:
			FOLDER = "../Output/" + getStatus() + "Entropies/";
			break;
		case Iterator::WEIGHTS:
			FOLDER = "../Output/" + getStatus() + "Weights/";
			break;
		default:
			break;
	}
	string fileName = getFullPath();
	ofstream output(fileName.c_str());
	output.width(6);
	output.precision(4);
	output.setf(ios::fixed);
	for (int i = 0; i < (int)stats.size(); ++i){
		output << stats[i] << "\t";
	}
	output.close();
}

double Iterator::calculateEntropy(vector<double>& inputWeights){
	double entropy = 0;
	for (int i = 0; i < (int)inputWeights.size(); ++i){
		entropy += -1 * inputWeights[i] * log(inputWeights[i]);
	}
	return entropy;
}

int minIndex(vector<double>& entropies){
	vector<double> ::iterator it = min_element(entropies.begin(), entropies.end());
	return it - entropies.begin();
}