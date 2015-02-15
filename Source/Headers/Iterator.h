/**
 * @file Iterator.h
 * @brief A file containing class definitions for Iterator.
 *
 * Apart from Iterator, this file also includes definitions for IteratorStatus 
 * and RandomTypes, which are important enumeration types for simulation and
 * iteration.
 *
 * \defgroup Processor Processor
 * @brief This group contains classes for actual processing of data, both 
 * simulation and inverse iteration. 
 *
 * The classes in this module are Iterator and Simulator, serve the purposes
 * of backward iterations and forward simulations. The usage of these two
 * classes follows the pattern of "Initialization-Configuration-Start". In
 * the "Initialization" phase, the user will be asked to input necessary 
 * parameters like "Input file name", "Number of Genes", "File Suffix". In
 * the "Configuration" phase, the user has the opportunity of configuring
 * the processor objects to the proper state like "OPTIMAL" or "CUBIC" 
 * algorithm in the inverse problem. After that, the objects will start
 * running, generating messages indicating their states. 
 */
#ifndef ITERATOR_H
#define ITERATOR_H
#include "FileCoordinator.h"
#include <set>

/**
 * \ingroup Processor
 * @class Iterator
 * @brief This class encapsulates the functionality of an inverse iterator.
 *
 * The Iterator inherits from FileCoordinator to use the file-related 
 * manipulations. The methods used for iteration are separated into two 
 * categories : Random and Deterministic. The currently used "Optimal"
 * algorithm is a deterministic algorithm. The algorithm and input file type for iteration 
 * could be set when initializing the object, like :
 * 
 * @code
 * Iterator* myIterator = new Iterator(IteratorStatus::PROVIDED, RandomTypes::OPTIMAL);
 * @endcode
 * It can also be set later by invoking the "setType" method, like:
 * 
 * @code
 * myIterator->setType(RandomTypes::MAXIMUM);
 * myIterator->setIteratorStatus(IteratorStatus::SIMULATED);
 * @endcode
 *
 * To let the Iterator object work, clients only need to call the public
 * method "iterate" after configuration. 
 * 
 * @code
 * myIterator->iterate();
 * @endcode
 *
 */
class Iterator : public FileCoordinator
{
public:
	/**
	 * @enum IteratorStatus
	 * @brief The status of the Iterator, what kind of input file it is dealing with.
	 * 
	 */
	enum IteratorStatus { 
		SIMULATED, ///< Iterator will iterate on SIMULATED data
		PROVIDED, ///< Iterator will iterate on PROVIDED real data
		ERROR, ///< Iterator is in error status
		READY ///< Iterator is ready to start working
	};

	/**
	 * @enum RandomTypes
	 * @brief The algorithms used to conduct the inverse iteration.
	 *
	 * Although called "RandomTypes", this enumeration actually contains both 
	 * random and deterministic algorithms. Moreover, clients can add self-developed
	 * algorithms into the enumeration.
	 */
	enum RandomTypes { 
		QUADRATIC, ///< A random algorithm, refer to the report for details.
		UNIFORM, ///< A random algorithm, refer to the report for details.
		CUBIC, ///< A random algorithm, refer to the report for details.
		MAXIMUM, ///< Deterministic algorithm, refer to the report for details.
		OPTIMAL, ///< Deterministic algorithm, refer to the report for details.
		DEFAULT ///< Ending mark of the enumeration
	};

	/**
	 * A static container of names of iteration algorithms.
	 * This vector is initialized in Analyzer.cpp.
	 */
	static vector<string> RANDOM_TYPE;

	/**
	 * Construct a new Iterator object, and set its IteratorStatus and RandomTypes.
	 * If no parameters provided, the default construction will use PROVIDED and
	 * OPTIMAL.
	 */
	Iterator(IteratorStatus status = PROVIDED, RandomTypes types = OPTIMAL);
	~Iterator(){delete transition;}

	/**
	 * Main method for iteration. This is a "Strategy Pattern" design. The iterate
	 * method will check the IteratorStatus and RandomType of the Iterator object
	 * and determine which method will be used on which file.\\
	 *
	 * It will also save the results in output files after iteration.
	 */
	void iterate();

	/**
	 * A check of internal consistency of input by verifying that the column sums 
	 * are ones. 
	 * @return True if the input file has no problem. 
	 */
	bool sanityCheck();

	/**
	 * Read a transition matrix from input file.
	 * @param  fileName   The file name of the file. i.e "overall" for "overall.txt"		
	 * @param  numOfGenes Number of genes corresponding to the input files
	 * @return Whether the read-in process is successful. @see FileCoordinator::fileStates           
	 */
	virtual	fileStates readFile(string fileName, int numOfGenes);

	void setIteratorStatus(IteratorStatus status){
		this->status = status;
	}

	string getErrorMessage(){
		return ERROR_MESSAGE;
	}

	RandomTypes getType(){
		return type;
	}

	void setType(RandomTypes type){
		this->type = type;
	}
private:
	RandomTypes type;
	IteratorStatus status;
	string ERROR_MESSAGE;
	double elapsedTime;

	/**
	 * Perform one iteration for random algorithms.
	 * @return The entropy of this iteration.
	 *
	 * @note For random algorithms, 1000 iterations will be performed and the iteration with
	 * least entropy will be selected. For implementation details, refer to Iterator.cpp.
	 */
	double iterateOnce();

	/**
	 * Perform the iteration for deterministic algorithms.
	 * @return The entropy of the iteration.
	 */
	double deterministicIterate();

	/**
	 * Helper function that calculates entropy of a given output.
	 * @param  inputWeights A vector containing the weights of a specific iteration
	 * @return              The entropy of this iteration
	 */
	double calculateEntropy(vector<double>& inputWeights);
	
	/**
	 * Helper method to choose a non-zero entry in the iteration process. 
	 * This method chooses entry based on Random or Deterministic methods. 
	 * Clients are also required to override or create new method for entry-choosing
	 * when testing self-developed algorithms.
	 * @param  column The column of the transition matrix to choose entry from
	 * @param  type   The type of entry choosing
	 * @return        The row number of the chosen entry.
	 *
	 * @note This method is internally used by Iterator::iterateOnce and Iterator::deterministicIterate.
	 * General usage is like :
	 * @code 
	 * map<int, double>& column = copy.get(col);
	 * int chosenRow = chooseEntry(column, type);
	 * @endcode
	 * For detailed used, refer to Iterator.cpp
	 */
	int chooseEntry(map<int, double>& column, RandomTypes type = QUADRATIC);
	
	virtual void saveVector(vector<double>& stats, saveTypes type);
	virtual void saveIteration();
	void saveTime();
	void saveResult();
	string getStatus(){
		if (status == PROVIDED) return "Provided/";
		else if (status == SIMULATED) return "Simulated/";
		else return "";
	}
	vector<rMatrix> boolNetworks;
	vector<double> weights;

	vector<double> entropies;
	vector<vector<rMatrix> > BNs;
	vector<vector<double> > qs;

};
#endif