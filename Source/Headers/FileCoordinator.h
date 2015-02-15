/**
 * @file FileCoordinator.h
 * 
 * @brief An abstract class for file manipulation.	
 *
 * This file contains the declaration of the abstract class responsible
 * for file manipulation.
 *
 * @author Liang RuoChen
 * @version 2.1 09/04/2014
 */

#ifndef FILE_COORDINATOR_H
#define FILE_COORDINATOR_H
#include <string>
#include <fstream>
#include "tMatrix.h"
using namespace std;

/**
 * @class FileCoordinator
 * 
 * @brief Abstract class for file manipulations.
 *
 * This is an abstract class that declared function prototypes used for
 * file manipulations. Classes encapsulating algorithms should derive
 * from this class for file interaction and should implement the virtual
 * methods as needed.
 *
 */

class FileCoordinator
{
public:
	virtual ~FileCoordinator() {};
	void setFileSuffix(string _suffix){suffix = _suffix;}
	tMatrix* getMatrix(){
		return transition;
	}

	/**
	 * @enum fileStates
	 * @brief Specifies the states of the file being processed.
	 *
	 * The file being read could be read successfully or there might
	 * be an exception. When the state is "READ_FAILURE", a failure
	 * message will be generated for the user to correct.
	 */
	enum fileStates { 
		READ_SUCCESS, ///< File successfully read in.
		READ_FAILURE ///< Error occurred when reading file.
	};

	/**
	 * @enum saveTypes
	 * @brief Specifies the types of data to be saved.
	 *
	 * The types of data to be saved will be used to determine which
	 * method to be used for saving process. 
	 */
	enum saveTypes { 
		MATRIX, ///< Type MATRIX is used when a transition matrix is saved;
		ENTROPY, ///< Type ENTROPY is used when saving entropies of decomposition;
		WEIGHTS, ///< Type WEIGHTS is used when saving wegits of decomposition;
		ITERATION ///< Type ITERATION is used when saving the iteration information containing minimal entropy result.
	};

	/**
	 * Get the full path of the file that is currently being processed
	 * or created. 
	 * @return The full path of the file.
	 */
	string getFullPath(){
		return FOLDER + FILEPREFIX + suffix + ".txt";
	}

	/**
	 * Get the filename for the file that is currently being processed
	 * or created. i.e If full path is "Input/Provided/CEM.txt", will 
	 * return "CEM".	
	 * @return The name of the file(without extension) being processed.
	 */
	string getFileName(){
		return filename;
	}

	/**
	 * Get the failure message if exceptions happen during file manipulation
	 * process. 
	 * @return The failure message.
	 */
	string getFailureMessage(){
		return FAILURE_MESSAGE;
	}
	
	/**
	 * A function prototype declared for reading in a transition matrix from
	 * a certain file. Overriden by "Iterator" class.
	 * @param  fileName   The name of the file, without extension and path;
	 * @param  numOfGenes The number of genes corresponding to the matrix in the file;
	 * @return            A fileStates indicating whether the reading process is successful.
	 */
	virtual fileStates readFile(string fileName, int numOfGenes){
		return READ_SUCCESS;
	};

protected:
	string FAILURE_MESSAGE; ///< Failure message expressing the cause of read file failure;
	string FOLDER; ///< Folder of the file to process;
	string FILEPREFIX; ///< Prefix of the file. i.e "sparseTransition_"
	string suffix; ///< Suffix of the file specified by user; i.e "newTest"
	string filename;///< Name of the file; i.e "CEM", "overall"
	tMatrix* transition; ///< The transition matrix currently being processed.

private:
	/**
	 * Saves the transition matrix to current file.
	 * @return Returns the full path of the file.
	 */
	virtual string saveMatrix(){return "";};

	/**
	 * Saves a vector into the current file, depending on the parameters.
	 * @param stats The vector data to save.
	 * @param type  The saveType specifying the type of data. i.e ENTROPY, WEIGHTS
	 */
	virtual void saveVector(vector<double>& stats, saveTypes type){};

	/**
	 * Saves iteration information into current file.
	 */
	virtual void saveIteration(){}; // The data to be saved should be provided by the child

};
#endif