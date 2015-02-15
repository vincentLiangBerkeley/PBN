#include <cstdlib>
#include "Interactor.h"

void Interactor::initializeIterator(){
	Iterator::IteratorStatus status;
	Iterator::RandomTypes type;
	string fileName, suffix;
	int numOfGenes;
	if (getIteratorParams(status, type, fileName, suffix, numOfGenes)){
		myIterator = new Iterator();
	}else{
		myIterator = new Iterator(status, type);
	}
	initializeIterator(suffix, fileName, numOfGenes);
}

void Interactor::initializeIterator(string suffix, string fileName, int numOfGenes){
	myIterator->setFileSuffix(suffix);
	if (myIterator->readFile(fileName, numOfGenes) == FileCoordinator::READ_FAILURE){
		cout << myIterator->getFailureMessage();
		exit(1);
	}
}

void Interactor::initializeSimulator(){
	int numOfGenes, simulateType;
	string suffix;
	getSimulatorParams(numOfGenes, simulateType, suffix);
	initializeSimulator(numOfGenes, simulateType, suffix);	
}

void Interactor::initializeSimulator(int numOfGenes, int simulateType, string suffix){
	mySimulator = new Simulator(numOfGenes, simulateType);
	mySimulator->setFileSuffix(suffix);
}

string Interactor::startSimulator(){
	string message = mySimulator->simulate();
	return message;
}

string Interactor::startIterator(){
	// Iterator should not start if the matrix is insane
	if (!myIterator->sanityCheck()){
		return "0" + myIterator->getFailureMessage();
	}
	string message;
	string testMessage; 
	message = "\nTesting on " + myIterator->getFileName();	
	testMessage = message + " using " + Iterator::RANDOM_TYPE[myIterator->getType()] + " method.\n";
	return testMessage;
}