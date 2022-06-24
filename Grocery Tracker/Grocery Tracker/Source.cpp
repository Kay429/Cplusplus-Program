
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

	using namespace std;

	ifstream inFS;


	/*
	Description:
		To call this function, simply pass the function name in Python that you wish to call.
	Example:
		callProcedure("printsomething");
	Output:
		Python will print on the screen: Hello from python!
	Return:
		None
	*/
	void CallProcedure(string pName)
	{
		char* procname = new char[pName.length() + 1];
		std::strcpy(procname, pName.c_str());

		Py_Initialize();
		PyObject* my_module = PyImport_ImportModule("PyCode");
		PyErr_Print();
		PyObject* my_function = PyObject_GetAttrString(my_module, procname);
		PyObject* my_result = PyObject_CallObject(my_function, NULL);
		Py_Finalize();

		delete[] procname;
	}

	/*
	Description:
		To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
	Example:
		int x = callIntFunc("PrintMe","Test");
	Output:
		Python will print on the screen:
			You sent me: Test
	Return:
		100 is returned to the C++
	*/
	int callIntFunc(string proc, string param)
	{
		char* procname = new char[proc.length() + 1];
		std::strcpy(procname, proc.c_str());

		char* paramval = new char[param.length() + 1];
		std::strcpy(paramval, param.c_str());


		PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
		// Initialize the Python Interpreter
		Py_Initialize();
		// Build the name object
		pName = PyUnicode_FromString((char*)"PyCode");
		// Load the module object
		pModule = PyImport_Import(pName);
		// pDict is a borrowed reference 
		pDict = PyModule_GetDict(pModule);
		// pFunc is also a borrowed reference 
		pFunc = PyDict_GetItemString(pDict, procname);
		if (PyCallable_Check(pFunc))
		{
			pValue = Py_BuildValue("(z)", paramval);
			PyErr_Print();
			presult = PyObject_CallObject(pFunc, pValue);
			PyErr_Print();
		}
		else
		{
			PyErr_Print();
		}
		//printf("Result is %d\n", _PyLong_AsInt(presult));
		Py_DECREF(pValue);
		// Clean up
		Py_DECREF(pModule);
		Py_DECREF(pName);
		// Finish the Python Interpreter
		Py_Finalize();

		// clean 
		delete[] procname;
		delete[] paramval;


		return _PyLong_AsInt(presult);
	}

	/*
	Description:
		To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
	Example:
		int x = callIntFunc("doublevalue",5);
	Return:
		25 is returned to the C++
	*/
	int callIntFunc(string proc, int param)
	{
		char* procname = new char[proc.length() + 1];
		std::strcpy(procname, proc.c_str());

		PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
		// Initialize the Python Interpreter
		Py_Initialize();
		// Build the name object
		pName = PyUnicode_FromString((char*)"PyCode");
		// Load the module object
		pModule = PyImport_Import(pName);
		// pDict is a borrowed reference 
		pDict = PyModule_GetDict(pModule);
		// pFunc is also a borrowed reference 
		pFunc = PyDict_GetItemString(pDict, procname);
		if (PyCallable_Check(pFunc))
		{
			pValue = Py_BuildValue("(i)", param);
			PyErr_Print();
			presult = PyObject_CallObject(pFunc, pValue);
			PyErr_Print();
		}
		else
		{
			PyErr_Print();
		}
		//printf("Result is %d\n", _PyLong_AsInt(presult));
		Py_DECREF(pValue);
		// Clean up
		Py_DECREF(pModule);
		Py_DECREF(pName);
		// Finish the Python Interpreter
		Py_Finalize();

		// clean 
		delete[] procname;

		return _PyLong_AsInt(presult);
	}

	string NCharString(int n, char c) {
		// Returns a string of length n repeating char c
		string outputString = "";
		outputString.append(n, c);
		return outputString;
	}

	void PrintHistogram() {
		// Reads item names and their purchase frequency from frequency.dat
		// Then prints a histogram displaying the information
		string item;
		int frequency;
		inFS.open("frequency.dat");
		if (!inFS.is_open()) {
			cout << "Could not open file frequency.dat" << endl;
		}
		else {
			inFS >> item;
			inFS >> frequency;
			cout << left;
			while (!inFS.fail()) {
				cout << " " << setw(12) << item << "   " << NCharString(frequency, '*') << endl;
				inFS >> item;
				inFS >> frequency;
			}
			inFS.close();
		}
	}

	void DisplayMenu() {
		// Prints the main menu
		cout << NCharString(12, '*') << " Grocery Tracker " << NCharString(12, '*') << endl;
		cout << "* 1 - Print frequency for all items      *" << endl;
		cout << "* 2 - Print frequency of a specific item *" << endl;
		cout << "* 3 - Print histogram                    *" << endl;
		cout << "* 4 - Exit                               *" << endl;
		cout << NCharString(41, '*') << endl << endl;
		cout << "Please input a number from the menu: ";
	}

	int GetUserInput() {
		// Receives and validates user input on the menu
		int userInput = 0;
		cin >> userInput;
		while (!(userInput == 1 || userInput == 2 || userInput == 3 || userInput == 4)) { // Valid inputs are 1, 2, 3, and 4
			userInput = 0;
			while (!cin) {
				// clearing out cin if a string was entered
				cin.clear();
				cin.ignore(1);
			}
			cout << endl << "Please enter a valid input." << endl << endl;
			cin >> userInput;
		}
		cout << endl << endl;
		return userInput;
	}

	void ProcessMenuInput(int menuInput) {
		// Once validated, user's menu input is passed to this function
		// which takes action corresponding to the user's menu selection
		if (menuInput == 1) {
			// Prints frequency of all the items in produce.txt
			CallProcedure("PrintAllFrequency");
			cout << endl;
		}
		else if (menuInput == 2) {
			// Prints the number of times a user entered string appears in produce.txt
			string userString;
			cout << "Which word would you like to search for?" << endl;
			cin >> userString;
			cout << "'" << userString << "' has been purchased " << callIntFunc("FindSpecificFrequency", userString) << " times." << endl;
		}
		else if (menuInput == 3) {
			// Creates a file with the frequency of all items in produce.txt
			// Then prints a histogram after reading this data
			CallProcedure("CreateHistogram");
			PrintHistogram();
			cout << endl;
		}
		else if (menuInput == 4) {
			// Program will be exited
		}
		else {
			cout << "ERROR - Invalid value passed to ProcessMenuInput()";
		}
	}


	int main()
	{
		int menuInput = 0;
		while (menuInput != 4) {
			DisplayMenu();
			menuInput = GetUserInput();
			ProcessMenuInput(menuInput);
			cout << endl << endl;
		}

		return 0;
	}