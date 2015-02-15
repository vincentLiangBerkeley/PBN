/**
 * @mainpage PBN Analyzer 2.1
 *
 * @brief An application for Simulation/Inverse Decomposition of Probabilistic
 * Boolean Networks.
 *
 * @section Introduction
 * This is an open-source application that can be used in the research/analysis
 * of PBN systems.
 * 
 * For users, you can inverse decompose your own transition matrix data and get
 * the Entropy, Decomposition and Time data, or you can simulate random boolean 
 * matrices and weights for transition matrices.
 *
 * For developer users, you can test your own algorithms using this API. Only the 
 * inverse algorithm part has to be implemented, all other functionalities are 
 * provided by the application itself.
 *
 * @section Compilation
 * This application now comes with the source file with makefile and is currently
 * a console application working on UNIX-like systems. 
 * 
 * If you are on MacOS or Linux System, just unzip the "Analyzer.zip" file, then use 
 * the terminal to go into "Release" folder, type "make" to compile the binary. Then
 * type "./Analyzer" to run the application.
 *
 * If you are on Windows system, you should first download and install "cygwin"
 * with "gcc, make" packages following the website 
 * After that, put the unzipped file in your home directory where your "cygwin"
 * executable is. Then repeat the steps for MacOS system.
 *
 * @section Mannual
 * When running the Analyzer application, first a menu will pop up and user are aked
 * to choose a funcional module. 
 * 1. Simulate data : This module will simulate test data and save the data in 
 * directory "Input/Simulated". It is advised to input descriptive suffix when asked
 * for.
 * 2. Test provided data : This module will let the user test their own provided data.
 * First make sure that your matrix data is in ".txt" format with columns separated by
 * "Tabs" and rows separated by "newLines". The application has a "default mode" where 
 * it assumes you are testing "Provided data" rather than "Simulated data" and the 
 * algorithm used will be "OPTIMAL". User can configure the mode according to their
 * own need. 
 * 3. and 4. are batch testing modules, on "Simulated data" and "Provided data" respectively.
 * The test data are prepared and upon chosen, the module will directly start running.
 *
 * @section Developer
 * If you want to use the application for testing your own inverse decomposition algorithm,
 * you should follow the steps:
 * Step 1 : Go to "Release/config.txt" and add the name of your algorithm in a new line 
 * before "_DEFAULT_";
 * Step 2 : Go to "Interactor.h" and add your algorithm name to the Enum "RandomTypes";
 * Step 3 : Here since the class responsible for doing inverse decomposition is the
 * "Iterator" class, there are basically two ways to add a new algorithm. One is write
 * a subclass of "Iterator" class and override the "Iterate" method to include your 
 * new algorithm. The second will be just modifying the original "Iterate" method. But
 * for the second way you might need to check the implementation of "iterateOnce" and
 * "chooseEntry" methods. Both method requires your implementation of the algorithm
 * in as separate function. 
 *
 * @section Design 
 * The major design used in this application is the "Model-View-Controller" design, where
 * the "Interactor" serves as the "Abstract of Controller". The "View" part is abstracted
 * in an interface called "Displayer". When moving to other platforms or building a GUI,
 * the most important part to rewrite is the "Menu" which is a subclass of "Interactor"
 * that implements the "Displayer" interface. Hence completing the task of user interaction.
 *
 * The algorithms are encapsulated in the "Model" part consists of "Simulator" and 
 * "Iterator", where "Simulator" class is responsible for simulating transition matrix
 * and "Iterator" class is responsible for doing inverse decomposition. 
 *
 * For further details, or usage of classes during development, please refer to the 
 * documentation of this application that follows.
 */


#include "Menu.h"
using namespace  std;


vector<string> Iterator::RANDOM_TYPE;

/**
 * A function that reads in the random algorithms from "config.txt" before starting
 * the application.
 */
void readRandomTypes(){
	ifstream input("config.txt");
	if (input.fail()){
		cout << "Configuration file : config.txt cannot be found!"
			 << "Please check whether it is in the folder 'Release'." << endl;
	}
	string type;
	while(true){
		getline(input, type);
		if (type.length() == 0) break;
		Iterator::RANDOM_TYPE.push_back(type);
	}
	input.close();
}

int main(){
	Menu myMenu;
	system("clear");
	readRandomTypes();
	myMenu.showMenu();
	myMenu.getChoice();
	return 0;
}