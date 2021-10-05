#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

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
	PyObject* my_module = PyImport_ImportModule("PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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




void displayMenu() {
	cout << "1: Show Grocery List" << endl;
	cout << "2: Find Item Quantity" << endl;
	cout << "3: Display Histogram" << endl;
	cout << "4: Exit" << endl << endl;
}

int validateInt() {
	int input;

	while (!(cin >> input)) {
		cin.clear();
		std::string dummy;
		cin >> dummy;
		cout << endl << "Please input a number." << endl << endl;
	}

	return input;
}

int getIntResponse(string prompt) {
	cout << endl << prompt << endl << endl;

	int response = validateInt();

	return response;
}

int validateCommand() {
	int command = getIntResponse("Enter your selection as a number 1, 2, 3, or 4: ");

	while (command != 1 && command != 2 && command != 3 && command != 4) {
		cout << endl << "Please enter either 1, 2, 3, or 4" << endl << endl;
		command = validateInt();
	}

	return command;
}

void performAction(int command) {
	if (command == 1) {
		cout << endl;
		CallProcedure("showGroceryList");
		cout << endl;
	}

	if (command == 2) {
		string groceryItem;

		cout << endl << "Enter Grocery Item: " << endl << endl;
		cin >> groceryItem;

		int itemQuantity = callIntFunc("findItemQuantity", groceryItem);

		cout << endl << "There are " << itemQuantity << " " << groceryItem << endl << endl;
	}

	if (command == 3) {
		cout << endl;
		CallProcedure("showHistogram");
		cout << endl;
	}
}


bool continueLoop = true;

void endProgram() {
	continueLoop = false;
}


int main() {
	while (continueLoop) {
		displayMenu();
		int command = validateCommand();
		command != 4 ? performAction(command) : endProgram();
	}
}