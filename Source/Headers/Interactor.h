/**
 * @file Interactor.h
 * @brief An abstract controller class.
 *
 * This controller has reference to Simulator and Iterator objects that 
 * do the background computation. 
 *
 * @author Vincent
 * @version 2.1 22/04/2014
 */

#ifndef INTERACTOR_H
#define INTERACTOR_H 

#include <iostream>
#include <string>
#include <stdlib.h>
#include "Simulator.h"
#include "Iterator.h"
using namespace std;

/**
 * \ingroup UI
 * @class Interactor
 * @brief An abstract controller class that contains method prototypes or 
 * basic implementations of methods for further overriding. 
 */
class Interactor
{
protected:
	Simulator* mySimulator;
	Iterator* myIterator;

	/**
	 * Initialize the owned Iterator object.
	 */
	void initializeIterator();

	/**
	 * Initialize the owned Simulator object.
	 */
	void initializeSimulator();

	/**
	 * Overloaded version, initialize the Iterator with specified params.
	 * @param suffix     File suffix added to the end of the file
	 * @param fileName   The file name of input
	 * @param numOfGenes Number of genes corresponding to the input file
	 *
	 * @note This method is called by the Interactor::initializeIterator() method internally.
	 */
	void initializeIterator(string suffix, string fileName, int numOfGenes);

	/**
	 * Overloaded version, initialize the Simulator with specified params.
	 * @param numOfGenes   Number of genes the user wants to simulate
	 * @param simulateType The type of simulation, the default is SPARSE
	 * @param suffix       The file suffix of the output file
	 *
	 * @note This method is called by the Interactor::initializeSimulator() method internally.
	 */
	void initializeSimulator(int numOfGenes, int simulateType, string suffix);

	/**
	 * Starts the Iterator object, will be overridden in concrete implementation.
	 * @return A message indicating the status of the Iterator
	 */
	string startIterator();

	/**
	 * Starts the Simulator object, will be overridden in concrete implementation.
	 * @return A message indicating the status of the Simulator
	 */
	string startSimulator();

private:
	/**
	 * Function prototype for getting Simulator parameters.
	 * @param numOfGenes   Number of genes to simulate
	 * @param simulateType Type of simulation, default is SPARSE
	 * @param suffix       Suffix added to the end of output file
	 */
	virtual void getSimulatorParams(int& numOfGenes, int& simulateType, string& suffix) = 0;

	/**
	 * Function prototype for getting Iterator parameters.
	 * @param  status     Iterator status, SIMULATED or PROVIDED. @see Iterator::IteratorStatus
	 * @param  type       Iteration type. @see Iterator::RandomTypes
	 * @param  fileName   The input filename. i.e "overall" for "overall.txt"
	 * @param  suffix     File suffix added to output file
	 * @param  numOfGenes Number of genes corresponding to the input file
	 * @return            True if the Iterator parameters are default values
	 */
	virtual bool getIteratorParams(Iterator::IteratorStatus& status, Iterator::RandomTypes& type, string& fileName, string& suffix, int& numOfGenes) = 0;

	/**
	 * Prototype for the method used to get file suffix from user
	 * @return The file suffix provided by the user
	 */
	virtual string getSuffix() = 0;

	/**
	 * Test all prepared simulation cases.
	 */
	virtual void testAllOnSimulator() = 0;

	/**
	 * Test all prepared iteration cases, either PROVIDED or SIMULATED
	 * @param status Input file type. PROVIDED or SIMULATED.
	 */
	virtual void testAllOnIterator(Iterator::IteratorStatus status) = 0;
};
#endif