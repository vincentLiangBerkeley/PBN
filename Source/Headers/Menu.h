/**
 * @file Menu.h
 * 
 * @brief This file contains declaration of the class Menu.
 *
 *
 * @author Liang RuoChen
 * @version 2.1 09/04/2014
 */
#ifndef MENU_H
#define MENU_H 

#include "Interactor.h"
#include "Displayer.h"

 /**
 * \ingroup UI
 * 
 * @class Menu
 * 
 * @brief This is a concrete controller class for the application.
 *
 * This class is a subclass of the "Interactor" that also implements the 
 * "Displayer" interface. This class serves as a controller that gets
 * user choice using "Displayer" interface methods and process it using
 * "Interactor" class methods.
 *
 */
class Menu : public Interactor, public Displayer::DisplayerClass
{
public:
	 /**
	 * The method that shows the menu to user. This implementation will 
	 * print the menu to the console output. The information of the menu
	 * is stored in the namespace "Displayer".
	 */
	virtual void showMenu();

	/**
	 * Get the choice from the user by taking in input from c++ standard
	 * keyboard input.
	 */
	virtual void getChoice();


private:
	/**
	 * Specific implementation of abstract method in "Displayer" interface.
	 * This method prints a message to console output.
	 * @param message The message to be shown.
	 */
	virtual void displayMessage(string message){cout << message;}

	/**
	 * Prints the transition matrix to standard output and ask the user to 
	 * ensure the correctness of the matrix.
	 * @param transition A pointer reference to the matrix to be checked.
	 */
	virtual void checkMatrix(tMatrix* transition);
	virtual void parseChoice();

	/**
	 * Display a "Process Complete" message then directly exit the program.
	 */
	virtual void exitProgram();

	/**
	 * Get the file suffix from user by prompting a message to standard output.
	 * @return The suffix entered by the user.
	 */
	virtual string getSuffix();

	/**
	 * Get the necessary parameters for initializing an "Iterator" instance.
	 * Information will be prompted to user from standard output.
	 * 
	 * @param  status     Status of the "Iterator", can be "PROVIDED" or "SIMULATED";	
	 * @param  type       Type of algorithms used for decomposition;
	 * @param  fileName   The file name of the file storing the transition matrix;	
	 * @param  suffix     Suffix obtained from user;
	 * @param  numOfGenes The number of genes corresponding to the file with <var> fileName </var>
	 * @return            <VAR>"True"</VAR> if the "Iterator" is initialized in "Default" mode.
	 *
	 * @note This function is an implementation of a function prototype from "Interactor" class.
	 * Implementation should be different depending on different types of user interaction.
	 * This is how it is used :
	 * @code 
	 * if (getIteratorParams(status, type, fileName, suffix, numOfGenes)){
	 *		myIterator = new Iterator();
	 * }else{
	 *	    myIterator = new Iterator(status, type);
	 * }
	 * initializeIterator(suffix, fileName, numOfGenes);
	 * @endcode
	 *
	 * @see Interactor::initializeIterator(string, string, int).
	 * 
	 * @warning This method must be implemented, or the initialization process cannot complete.
	 */
	virtual bool getIteratorParams(Iterator::IteratorStatus& status, Iterator::RandomTypes& type, string& fileName, string& suffix, int& numOfGenes);
	
	/**
	 * Get the necessary parameters for initializing a "Simulator" instance.
	 * Information will be prompted to user from standard output.
	 * 			
	 * @param numOfGenes   The number of genes to simulate.
	 * @param simulateType The type for simulation, either SPRASE or FORWARD.
	 * @param suffix       The file suffix added to the end of the output files.
	 * Implementation should be different depending on different types of user interaction.
	 * This is how it is used :
	 * @code 
	 * int numOfGenes, simulateType;
	 * string suffix;
	 * getSimulatorParams(numOfGenes, simulateType, suffix);
	 * initializeSimulator(numOfGenes, simulateType, suffix);
	 * @endcode
	 *
	 * @see Interactor::initializeSimulator(int, int, string).
	 * 
	 * @warning This method must be implemented, or the initialization process cannot complete.
	 */
	virtual void getSimulatorParams(int& numOfGenes, int& simulateType, string& suffix);

	//@Override
	string startSimulator(){
		cout << endl;
		displayMessage(Interactor::startSimulator());
		return "";
	}
	 
	//@Override
	string startIterator(){
		cout << endl;
		string message = Interactor::startIterator();
		displayMessage(message.substr(1));
		if (message[0] != '0') myIterator->iterate();
		return "";
	}
	virtual void testAllOnSimulator();
	virtual void testAllOnIterator(Iterator::IteratorStatus status);
	void testIteratorOnFile(string fileName, int numOfGenes);
};
#endif