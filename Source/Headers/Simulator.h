/**
 * @file Simulator.h
 * @brief This file contains class definitions of Simulator class.
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H 
#include "FileCoordinator.h"

/**
 * \ingroup Processor
 * @class Simulator
 * @brief This is a class that handles simulation process.
 *
 * The Simulator class serves to simulate transition matrix with a given
 * number of genes. There are two types of simulation: SPARSE and FORWARD.
 * The SPARSE simulation will control the number of non-zero entries in 
 * each column below the number of genes.
 *
 * The FORWARD simulation will simulate 10 BNs and their corresponding 
 * weights and construct a final transition matrix. But the result of this
 * simulation is not guaranteed to be sparse, especially when the number of
 * genes are small.
 */
class Simulator : public FileCoordinator
{
public:
	Simulator(int number, int type);
	~Simulator() {delete transition;}
	/**
	 * The main method available for clients. After setting the number of 
	 * genes and type of simulation, the client needs only to call this 
	 * method to simulate and save results in output files.
	 * @return A message indicating location and type of simulation.
	 *
	 * @see Interactor::startSimulator
	 */
	string simulate();
	bool isSimulated;
private:
	/**
	 * The method for generating SPARSE transition matrix.
	 * @param n The number of genes to simulate
	 */
	void generateTransition(int n);

	/**
	 * The method for generating FORWARD transition matrix.
	 * @param n      The number of genes to simulate
	 * @param m      The number of BNs used in simulation. The default value is 10
	 * @param output An output stream to save the BNs and their weights
	 */
	void generateTransition(int n, int m, ostream& output);
	virtual string saveMatrix(); // Method from the interface
	enum TYPES { SPARSE, FORWARD };	
	TYPES simulationType;
	int numOfGenes;
	int MAX_NON_ZERO;
};
#endif
