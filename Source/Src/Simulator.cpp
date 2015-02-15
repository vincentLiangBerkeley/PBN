#include "Simulator.h"
#include "randomHelper.h"
static const int DEFAULT_NUM_BN = 10;
Simulator::Simulator(int n, int type){
	numOfGenes = n;
	isSimulated = false;
	MAX_NON_ZERO = n;
	if (type == 1) simulationType = SPARSE;
	else if (type == 2) simulationType = FORWARD;
	FOLDER = "../Input/Simulated/";
}

string Simulator::simulate(){
	string saveMessage;
	if (simulationType == SPARSE){
		FILEPREFIX = "sparseTransition_";
		generateTransition(numOfGenes);
		saveMessage = saveMatrix();	
		
	}
	else if (simulationType == FORWARD){
		FILEPREFIX = "matrices_";
		string fileName = getFullPath();
		ofstream ofile;
		ofile.open(fileName.c_str());
		generateTransition(numOfGenes, DEFAULT_NUM_BN, ofile);
		ofile.close();
		cout << "Components BNs stored in " + getFullPath() + "\n";

		FILEPREFIX = "transition_";
		saveMessage = saveMatrix();
	}
	isSimulated = true;
	return saveMessage;
}

void Simulator::generateTransition(int n, int m, ostream& output){
	// Generate m random matrices and a weight, add them together
	double* randomWeight = weights(m);
	tMatrix transition = tMatrix(n);
	for (int i = 0; i < m; ++i){
		rMatrix rm = rMatrix(n);
		output << "\nThe random matrix no. " << i + 1 << " is :" << endl;
		output << "With corresponding probability q = " << randomWeight[i] << endl;
		rm.print(output);
		transition += tMatrix::times(rm, randomWeight[i]);
	}
	this->transition = new tMatrix(transition);
}

void Simulator::generateTransition(int n){
	this->transition = new tMatrix(n); // Empty transition matrix for n genes

	// Generate each column of the transition matrix, keeping n num of non-zeros
	for (int i = 0; i < pow(2, n); ++i){ //  i iterates through columns
		double sum = 0.0;
		for (int j = 0; j < MAX_NON_ZERO; ++j){
			// Re-fetch is needed since we are changing the column during simulation
			map<int, double> column = this->transition->get(i);
			// Generate a random weight for a random row
			double weight = randomDouble(1);
			int row = rand() % (int) pow(2, n);
			//cout << "Currently generating (" << row << "," << i << ")" << endl;
			//cout << "Current Weight, sum are : " << weight << " " << sum << endl;
			// Control number of random weights by checking whether we exceed 1
			if (weight + sum >= 1 || j == n - 1){
				weight = 1 - sum;
				//cout << "Sum of the " << i << "th column is: " << sum + weight << endl;
				// Check whether the random row is non-zero or not
				if (column.find(row) != column.end()){
					weight += column.find(row) ->second;
					//cout << weight << endl;
 				}
				this->transition->set(row, i, weight);
				break;
			}else{
				sum += weight;
				if (column.find(row) != column.end()){
					weight += column.find(row) ->second;
 				}
				this->transition->set(row, i, weight);
			}
		}
	}
}

string Simulator::saveMatrix(){
	ofstream ofile;
	string fileName = getFullPath();
	ofile.open(fileName.c_str());

	this->transition->print(ofile);
	ofile.close();
	return "Matrix saved in " + fileName + "\n";
}

