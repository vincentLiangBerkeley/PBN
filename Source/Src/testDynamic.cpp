#include <iostream>
#include "Iterator.h"
using namespace std;
const string Iterator::RANDOM_TYPE[] = {
		"_QUADRATIC_",
		"_UNIFORM_",
		"_CUBIC_",
		"_MAXIMUM_",
		"_OPTIMAL",
		"_DEFAULT_"
	};

int main(){
	Iterator myIterator;
	string fileName = "CEM";
	int numOfGenes = 3;
	if (myIterator.readFile(fileName, numOfGenes) != Iterator::READ_SUCCESS){
		cout << myIterator.getErrorMessage() << "Error" << endl;;
		exit(1);
	}
	myIterator.setFileSuffix("Dynamic");
	myIterator.setType(Iterator::MAXIMUM);
	myIterator.iterate();
	myIterator.getMatrix()->print(cout);
	return 0;
}