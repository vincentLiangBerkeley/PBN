#include "Iterator.h"

int main(){
	Iterator myIterator;
	cout << "Read from existing file." << endl;
	string fileName;
	int numOfGenes;
	cout << "\nPlease provide the file name of your input without extension(i.e overall.txt as overall)" << endl;
	cout << "For instructions about formating of input files, please refer to \"readme.txt\"." << endl;
	cout << "Also include the number of genes corresponding to your file, separated with space." << endl;
	// getline(cin, fileName, ' ');
	// cin >> numOfGenes;
	// cin.ignore();
 	string Inputs[] = {"CEM", "CET", "CMT", "EMT", "overall"};
 	int Genes[] = {3, 3, 3, 3, 4};
	for (int i = 0; i < 5; ++i){
		fileName = Inputs[i];
		numOfGenes = Genes[i];

		cout << "Testing " << fileName << ".txt" << endl;
		// This method should also handle the exception
		// And provide indicator whether to proceed
		if (myIterator.readFile(fileName, numOfGenes) == fileCoordinator::READ_FAILURE){
			cout << myIterator.getFailureMessage();
			exit(1);
		}; 

		if (myIterator.checkMatrix() == Iterator::ERROR){
			cout << myIterator.getErrorMessage();
			exit(1);
		}
		// cout << "Start 1000 times iteration?(y/n) " << endl;
		// if (getchar() == 'y' || getchar() == 'Y'){
		// 	cout << myIterator.iterateOnce() << endl;
		// }
		cout << myIterator.iterateOnce() << endl;
		myIterator.iterate();
	}
	
	return 0;
}