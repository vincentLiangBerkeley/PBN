#include "Menu.h"
#include <ctype.h>
#include <cstdlib>

static const string PROVIDED_CASES[] = {"CEM", "CET", "CMT", "EMT", "overall"};
static const int PROVIDED_GENES[] = {3, 3, 3, 3, 4};
static const int TEST_CASES_SIMULATED = 4;
static const int TEST_CASES_PROVIDED = 5;
static const int SIMULATED_GENES[] = {3, 4, 5, 6};
static const string TEST_PREPARE = "Prepared";

void Menu::showMenu(){
	displayMessage(Displayer::WELCOME);
	for (int i = 0; i < Displayer::NUM_OPTIONS; ++i){
		displayMessage(Displayer::BEFORE);
		displayMessage(Displayer::OPTIONS[i]);
	}
}

void Menu::getChoice(){
	cin >> choice;
	choice = tolower(choice);
	while(true){
		parseChoice();
		showMenu();
		cin >> choice;
	}
	displayMessage(Displayer::COMPLETE);
}

void Menu::parseChoice(){
	switch(choice){
		case '1':
			initializeSimulator();
			startSimulator();
			if (mySimulator->isSimulated){
				checkMatrix(mySimulator->getMatrix());
			}
			break;
		case '2':
			initializeIterator();
			checkMatrix(myIterator->getMatrix());
			startIterator();
			break;
		case '3':
			testAllOnSimulator();
			testAllOnIterator(Iterator::SIMULATED);
			break;
		case '4':
			testAllOnIterator(Iterator::PROVIDED);
			break;
		case 'q':
			exitProgram();
		default:
			displayMessage(Displayer::INVALID_CHOICE);
			break;
	}
}

void Menu::exitProgram(){
	displayMessage(Displayer::GOODBYE);
	exit(1);
}

void Menu::testAllOnSimulator(){
	// Simulate matrix using Sparse method for 3, 4, 5, 6 genes
	for (int i = 0; i < TEST_CASES_SIMULATED; ++i){
		char geneNumber = SIMULATED_GENES[i] + '0';
		string suffix = TEST_PREPARE + geneNumber;
		initializeSimulator(SIMULATED_GENES[i], 1, suffix);

		string fileName = "../Input/Simulated/sparseTransition_" + suffix + ".txt";
		ifstream test(fileName.c_str());
		if(!test.good()) startSimulator();

		test.close();
	}
}

void Menu::testIteratorOnFile(string fileName, int numOfGenes){
	initializeIterator("", fileName, numOfGenes);
	for (int i = 0; i != Iterator::DEFAULT; ++i){
		Iterator::RandomTypes type = static_cast<Iterator::RandomTypes>(i);
		myIterator->setType(type);
		startIterator();
	}
}

void Menu::testAllOnIterator(Iterator::IteratorStatus status){
	if (status == Iterator::SIMULATED){
		myIterator = new Iterator(Iterator::SIMULATED);
		for (int i = 0; i < TEST_CASES_SIMULATED; ++i){
			string fileName = "sparseTransition_";
			char geneNumber = SIMULATED_GENES[i] + '0';
			string suffix = TEST_PREPARE + geneNumber;
			fileName += suffix;
			testIteratorOnFile(fileName, SIMULATED_GENES[i]);
		}
	}else if (status == Iterator::PROVIDED){
		myIterator = new Iterator(Iterator::PROVIDED);
		for (int i = 0; i < TEST_CASES_PROVIDED; ++i){
			string fileName = PROVIDED_CASES[i];
			testIteratorOnFile(fileName, PROVIDED_GENES[i]);
		}
	}
}

bool Menu::getIteratorParams(Iterator::IteratorStatus& status, Iterator::RandomTypes& type, string& fileName, string& suffix, int& numOfGenes){
	suffix = getSuffix();
	cout << "Run in default mode(y/n)? (Files provided are from 'Provided' folder, and "
		 << "method used is Optimal)." << endl;
	char c = getchar();
	cin.ignore();
	if (c == 'y' || c == 'Y'){
		cout << "\nPlease provide the file name of your input without extension(i.e overall.txt as overall)" << endl;
		cout << "For instructions about formating of input files, please refer to \"readme.txt\"." << endl;
		cout << "Also include the number of genes corresponding to your file, separated with space." << endl;
		getline(cin, fileName, ' ');
		cin >> numOfGenes;
		cin.ignore();
		return true;
	} 
	
	startStatus:cout << "Please specify input file types : " << endl;
	cout << "1. SIMULATED;" << endl;
	cout << "2. PROVIDED;" << endl;
	cout << "q. Quit." << endl;
	c = getchar();
	cin.ignore();
	switch(c){
		case '1':
			status = Iterator::SIMULATED;
			break;
		case '2':
			status = Iterator::PROVIDED;
			break;
		case 'q':
			exitProgram();
			break;
		default:
			displayMessage(Displayer::INVALID_CHOICE);
			goto startStatus;
			break;
	}
	startType:cout << "Please specify random process type : " << endl;

	for (int i = 0; i < Iterator::RANDOM_TYPE.size(); ++i){
		cout << i + 1 << ". " << Iterator::RANDOM_TYPE[i] << ";" << endl;
	}
	cout << "q. Quit." << endl;
	c = getchar();
	cin.ignore();
	if (c == 'q') exitProgram();
	else if ('1' <= c && c <= static_cast<int>(Iterator::DEFAULT) + '0'){
		type = static_cast<Iterator::RandomTypes>(c - '0' - 1); 
	}else{
		displayMessage(Displayer::INVALID_CHOICE);
	 	goto startType;
	}

	cout << "\nPlease provide the file name of your input without extension(i.e overall.txt as overall)" << endl;
	cout << "For instructions about formating of input files, please refer to \"readme.txt\"." << endl;
	cout << "Also include the number of genes corresponding to your file, separated with space." << endl;
	getline(cin, fileName, ' ');
	cin >> numOfGenes;
	cin.ignore();
	return false;
}

void Menu::checkMatrix(tMatrix* transition){
	if (transition == NULL){
		cout <<  "The matrix to iterate with has not been initialized!\n";
	}else{
		cout << "The result matrix is :" << endl;
		transition->print(cout);
	}
}

void Menu::getSimulatorParams(int& numOfGenes, int& simulateType, string& suffix){
	cout << "Please input the number of genes you want to simulate." << endl;
	cin >> numOfGenes;
	cout << "Please specify the type of simulation: " << endl;
	cout << "1. Sparse(the number of non-zeros will be at most n;" << endl;
	cout << "2. Forward(generate BNs and weights." << endl;
	cin >> simulateType;
	suffix = getSuffix();
}

string Menu::getSuffix(){
	string suffix;
	cout << "Please specify a file suffix for the output data, that suffix"
		 << " will be added after an '_' of the files generated." << endl;
	cin >> suffix;
	cin.ignore();
	return suffix;
}