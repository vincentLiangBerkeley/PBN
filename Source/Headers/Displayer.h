/**
 * @file Displayer.h
 * 
 * @brief This is an interface for the "View".
 *
 * This interface abstracts methods needed for the "View". Any controller
 * class should implement this interface. Besides, the namespace Displayer
 * also provides some interaction messages that could be presented to end
 * users.
 *
 *
 * \defgroup UI User Interaction
 * @brief This group contains classes used for user interaction.
 * 
 * This group contains an interface for User Interaction and also a concrete
 * class that implements the functionality. Upgrading or migrating to other
 * platforms/languages need reimplementation of this class.
 */
#ifndef DISPLAYER_H
#define DISPLAYER_H

namespace Displayer{
	static const string BEFORE = "\t\t\t";
	static const int NUM_OPTIONS = 5;
	static const string OPTIONS[] = {
		"1. Simulate transition matrix.\n",
		"2. Test on provided matrix.\n",
		"3. Set random process parameters.\n",
		"4. Test all prepared data.\n", 
		"q. Quit.\n"
	};
	static const string WELCOME = 
	"Thank you for using PBN analyzer.\nPlease choose from the following options.\n";
	static const string GOODBYE = 
	"Thank you for using PBN analyzer.\n";
	static const string COMPLETE = 
	"\nProcess Complete!\n";
	static const string INVALID_CHOICE = 
	"Invalid choice, please choose again!\n";

	/**
	 *
	 * \ingroup UI
	 * 
	 * @class DisplayerClass
	 * 
	 * @brief Abstract interface for direct interation with end users.
	 *
	 * This class declares function prototypes for user interactions. 
	 * Any controller class should implement this interface.  
	 *
	 */
	
	class DisplayerClass
	{
	public:
		/**
		 * Displaying the menu containing choices to end users. This
		 * method should be implemented differently according to 
		 * different purposes. i.e GUI or Console.
		 */
		virtual void showMenu() = 0;

		/**
		 * Get the choice from end users. 
		 */
		virtual void getChoice() = 0;

	protected:
		/// A character representing the choice of users
		char choice;

	private:
		/**
		 * A method to parse the choice from user. Deciding which mehod
		 * to call upon each choice.
		 */
		virtual void parseChoice() = 0;

		/**
		 * Display a message to end user.
		 * @param message The message to display.
		 */
		virtual void displayMessage(string message) = 0;

		/**
		 * Display the resulting matrix to end user for double-check.
		 * @param transition A tMatrix instance to display
		 */
		virtual void checkMatrix(tMatrix* transition) = 0;

		/**
		 * Action taken to exit the program. Specific behaviors when exiting
		 * could be included in this method.
		 */
		virtual void exitProgram() = 0;
	};
};
#endif