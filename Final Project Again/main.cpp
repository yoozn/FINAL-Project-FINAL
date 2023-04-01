#include <iostream>
//fstream for file input and output
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <iomanip>
//stdlib.h for changing colour of terminal and text (purely cosmetic)
#include <stdlib.h>
#include "Employee.h"
using namespace std;

void MainLoop();

//Used when creating new employee ids
bool isIDTaken(vector<Employee> employees, string id) {
	for (int i = 0; i < employees.size(); i++) {
		if (id == employees[i].getID()) {
			return true;
		}
	}
	return false;
}

//Method used to save new employee into file. Only used when adding an employee, not when editing or erasing current employees. 
//This method just appends to the end of existing file the new employee, rather than rewriting whole file
void SaveEmployeeToFile(Employee employee) {
	//fstream is object for outputting and inputting
	fstream output;
	//ios::app opens the file without overwriting, and appends the data to the end of the file
	output.open("EmployeeData.txt", ios::app);
	//write to the file employee password, name, role and salary
	output << employee.getID() << " " << employee.getPassword() << " " << employee.getName() << " " << employee.getRole() << " " << employee.getSalary();
	for (int i = 0; i < 7; i++) {
		output << " " << employee.getSchedule(i);
	}
	output << endl;
	output.close();
}

//Other method used for saving. This one is used for when editing or deleting current employees. This method rewrites the entire file from scratch.
void OverwriteSaveFile(vector<Employee> employees) {
	fstream output;
	output.open("EmployeeData.txt", ios::out);
	for (int i = 0; i < employees.size(); i++) {
		output  << employees[i].getID() << " " << employees[i].getPassword() << " " << employees[i].getName() << " " << employees[i].getRole() << " " << employees[i].getSalary();
		for (int j = 0; j < 7; j++) {
			output << " " << employees[i].getSchedule(j);
		}
		output << endl;
	}
	output.close();
}

//Method to add new employees. Needs to be changed to only be accessible to managers
Employee AddEmployee(vector<Employee> employees) {
	string id;
	string password;
	string name;
	//Name has to be combined from first and last name since cin only takes one word at a time. Alternatively getline can be used, but can be finicky when combined with cin.
	string firstName;
	string lastName;
	string role;
	string salary;
	//ask user for new employees password, name, and role. Then make new employee object from these inputs, and return it. Also save to the file this new employee
	do {
		cout << "Set employee id" << endl;
		cin >> id;
		if (isIDTaken(employees, id)) {
			cout << "ID already taken." << endl;
		}
	} while (isIDTaken(employees, id) == true);

	do {
		cout << "Set employee password: " << endl;
		cin >> password;
		if (password.length() < 4) {
			cout << "Password is too short." << endl;
		}
	} while (password.length() < 4);
	cout << "Enter employee name:" << endl;
	cin >> firstName >> lastName;
	name += firstName + " " + lastName;
	cout << "Enter the employees role: " << endl;
	cin >> role;
	cout << "Enter the salary for the employee" << endl;
	cin >> salary;
	//cout << name << endl << password << endl << role << endl;
	Employee employeeToAdd(id, password, name, role, salary);
	SaveEmployeeToFile(employeeToAdd);
	return employeeToAdd;
}

//Loop through the employee array, and print out each employee and their datafields
void ViewEmployees(vector<Employee> employees) {
	system("CLS");
	cout << setw(55) << "Information" << endl;
	cout << setw(10) << "ID" << setw(25) << "Name" << setw(28) << "Password" << setw(24) << "Role" << setw(26) << "Salary/h" << endl;
	for (int i = 0; i < employees.size(); i++) {
		cout << setw(10) << employees[i].getID() << setw(25) << employees[i].getName() << setw(28) << employees[i].getPassword() << setw(24) << employees[i].getRole() << setw(26) << employees[i].getSalary() << endl;
	}
	cout << endl;
}

bool CanRemoveEmployee(vector<Employee> employees, Employee employee) {
	if (employee.getRole() == "Manager") {

	int count = 0;
	for (int i = 0; i < employees.size(); i++) {
		if (employees[i].getRole() == "Manager") {
			count++;
			if (count > 1) {
				return true;
			}
		}
	}
	return false;
	}
	else {
		return true;
	}
}

//Used for both editing and deleting employees. Whether editing or removing is decided from the 'editOrRemove' parameter
void EditEmployees(vector<Employee> employees, string editOrRemove, Employee user) {
	string id;
	int index;
	bool found = false;
	//change colour of output window and text depending on if editing or removing
	if (editOrRemove == "edit") {
		system("Color E0");
	}
	else if (editOrRemove == "remove") {
		system("Color C0");
	}
	//Ask for employee id
	cout << "Enter employees ID: " << endl;
	cin >> id;



	//Search array for employee id, if found return index of employee
	for (int i = 0; i < employees.size(); i++) {
		if (employees[i].getID() == id) {
			index = i;
			found = true;
			break;
		}
	}



	//if the employee was found, ask for futher input
	if (found == true) {
		string input;
		//if editing, ask what the user wants to edit
		if (editOrRemove == "edit") {

			cout << "Employee to edit: " << employees[index].getName() << endl;
			cout << "What to edit? " << endl;
			cout << "1. Name" << endl;
			cout << "2. Password" << endl;
			cout << "3. Job" << endl;
			cout << "4. ID" << endl;
			cout << "5. Salary" << endl;

			cin >> input;
			if (input == "1") {
				//Change the name of the index of the account the user wants to change
				string firstName;
				string lastName;
				string name;
				cout << "Enter the new name (first and last): " << endl;
				cin >> firstName >> lastName;
				name = firstName + " " + lastName;
				employees[index].setName(name);
			}
			else if (input == "2") {
				//Change the password of the account of index the user wants to change 
				string password;
				cout << "Enter the new password: " << endl;
				cin >> password;
				if (password.length() > 3) {
					employees[index].setPassword(password);
				}
				else {
					cout << "Password is too short." << endl;
					return;
				}

			}
			else if (input == "3") {
				//Change the job [or role] of the account of index chosen by user
				string job;
				cout << "Enter the new job: " << endl;
				cin >> job;
				employees[index].setRole(job);
			}
			else if (input == "4") {
				string id;
				cout << "Enter the new id: " << endl;
				cin >> id;
				for (int i = 0; i < employees.size(); i++) {
					if (id == employees[i].getID()) {
						cout << "ID already taken." << endl;
						return;
					}
				}
				employees[index].setID(id);
			}
			else if (input == "5") {
				string salary;
				cout << "Enter the new salary: " << endl;
				cin >> salary;
				employees[index].setSalary(salary);
			}
			else {
				//if user chooses other invalid input, let them know, and break out of method
				cout << "Invalid input." << endl;
				return;
			}
		}
		//Check if the user is trying to remove themselves, and prevent it. This prevents the case of the only manager removing themselves, and requires a second manager to remove them.
		else if (editOrRemove == "remove" && user.getID() != employees[index].getID()) {
			cout << "Employee vector size: " << employees.size() << endl;
			//Alternatively, if not editing but removing employees
			string removeInput;
			//Ask for confirmation they want to remove an employee
			cout << "Employee to remove: " << employees[index].getName() << endl;
			cout << "Are you sure you want to remove them? (y/n)" << endl;
			cin >> removeInput;
			if (removeInput == "y" or removeInput == "Y") {
				cout << "Removed " << employees[index].getName() << endl;
				//erase the employee at index found. vector.erase() method takes in a pointer value, so have to use vector.begin() then add the index
				employees.erase(employees.begin() + index);
			}
			else if (removeInput == "n" or removeInput == "N") {
				cout << "Cancelled remove." << endl;
				return;
			}
			else {
				cout << "Invalid input. Noone was removed." << endl;
				return;
			}
		}
		else {
			cout << "Invalid operation. Cannot remove yourself." << endl;
		}
		//Once employee is edited or removed, rewrite the file with new data
		OverwriteSaveFile(employees);
	}
	else {
		cout << "Could not find that id." << endl;
	}
}



void ViewSchedule(Employee user) {
	cout << setw(60) << "Schedule" << endl;
	//cout << "Monday" << setw(15) << "Tuesday" << setw(15) << "Wednesday" << setw(15) << "Thursday" << setw(15) << "Friday" << setw(15) << "Saturday" << setw(15) << "Sunday" << endl;
	cout << "Monday" << setw(17) << "Tuesday" << setw(19) << "Wednesday" << setw(18) << "Thursday" << setw(17) << "Friday" << setw(18) << "Saturday" << setw(17) << "Sunday" << endl;
	//cout << user.getSchedule(0) << setw(17) <<	user.getSchedule(1) << setw(13) << user.getSchedule(2) << setw(14) << user.getSchedule(3) << setw(17) << user.getSchedule(4) << setw(14) << user.getSchedule(5) << setw(16) << user.getSchedule(6) << endl;
	cout << setw(3) << user.getSchedule(0) << setw(17) << user.getSchedule(1) << setw(18) << user.getSchedule(2) << setw(19) << user.getSchedule(3) << setw(17) << user.getSchedule(4) << setw(18) << user.getSchedule(5) << setw(17) << user.getSchedule(6) << endl;
}

void setSchedule(vector<Employee> employees) {
	string id;
	bool found = false;
	int day;
	int index;
	string hours;
	cout << "Enter the employee ID: " << endl;
	cin >> id;
	for (int i = 0; i < employees.size(); i++) {
		if (id == employees[i].getID()) {
			found = true;
			index = i;
			break;
		}
	}
	if (found) {
		cout << "Changing schedule for " << employees[index].getName() << endl;
		cout << "Enter the day (1 - Monday, 2 - Tuesday...): " << endl;
		cin >> day;
		switch (day) {
		case 1:
			cout << "Enter the hours for Monday: " << endl;
			cin >> hours;
			break;
		case 2:
			cout << "Enter the hours for Tuesday: " << endl;
			cin >> hours;
			break;
		case 3:
			cout << "Enter the hours for Wednesday: " << endl;
			cin >> hours;
			break;
		case 4:
			cout << "Enter the hours for Thursday: " << endl;
			cin >> hours;
			break;
		case 5:
			cout << "Enter the hours for Friday: " << endl;
			cin >> hours;
			break;
		case 6:
			cout << "Enter the hours for Saturday: " << endl;
			cin >> hours;
			break;
		case 7:
			cout << "Enter the hours for Sunday: " << endl;
			cin >> hours;
			break;
		default:
			cout << "Invalid input" << endl;
			break;
		}


	}
	else {
		cout << "Invalid id." << endl;
		return;
	}
	employees[index].setSchedule(day - 1, hours);
	OverwriteSaveFile(employees);
}

void DisplayInformation() {
	system("CLS");
	string input;
	cout << "Welcome to the Employee Management Information System." << endl << endl;
	cout << "You will first be prompted to set up the machine by creating an initial manager account" << endl;
	cout << "This account can be used to create, edit, or delete other accounts. You can also create" << endl;
	cout << "other manager accounts by making their role 'Manager' during the account creation process." << endl << endl;
	cout << "Normal employees have less access than managers, and are able to view their schedule, and personal" << endl;
	cout << "information." << endl << endl;
	cout << "When prompted with options such as:" << endl << "1: Option 1. " << endl << "2. Option 2. " << endl << "3. Option..." << endl;
	cout << "You can selected the option you want by entering the corresponding number such as '1' for option 1." << endl << endl;
	cout << "Enter '1' to continue!" << endl;
	do {
		cin >> input;

	} while (input != "1");
}



void LoadingBar(string Message, int speed) {
	system("CLS");
	cout << "\n\n\n\n\n\t\t\t\t\t " << Message << " Please wait..." << endl;
	char loading = 221;
	cout << "\t\t\t";
	for (int i = 0; i <= 50; i++) {
		Sleep(speed);
		cout << loading;
	}
	cout << "\n" << endl;
	system("CLS");
}

//Load employee vector from the file, if the file exists
vector<Employee> LoadEmployees() {
	vector<Employee> employees;
	fstream input;
	input.open("EmployeeData.txt");

	if (input.fail() || input.peek() == ifstream::traits_type::eof()) {
		//cout << "Could not open save file." << endl;
		DisplayInformation();
		system("CLS");
		cout << "This is your first time setting up! Welcome!" << endl;
		string id;
		string password;
		//Name has to be combined from first and last name since cin only takes one word at a time. Alternatively getline can be used, but can be finicky when combined with cin.
		string role;
		string firstName;
		string lastName;
		string name;
		string salary;
		cout << "What is your name? (first and last)" << endl;
		cin >> firstName >> lastName;
		name += firstName + " " + lastName;
		system("CLS");
		cout << "I assume that you are the manager of this corporation, please create a password" << endl;
		role = "Manager";
		do {
			cin >> password;
			if (password.length() < 4) {
				cout << "Password is too short. Try again." << endl;
			}
		} while (password.length() < 4);
		system("CLS");
		cout << "Perfect!, What will be your ID?" << endl;
		cin >> id;
		cout << "Enter the salary" << endl;
		cin >> salary;
		system("CLS");
		srand(time(0));

		Employee firstEmployee(id, password, name, role, salary);
		employees.push_back(firstEmployee);
		//SaveEmployeeToFile(firstEmployee);
		OverwriteSaveFile(employees);

	}
	else {
		//Keep looping until end of file, and read the data from file one word at a time. Create the employee objects from this file data, and pushback to employee vector each object
		while (!input.eof()) {
			string id;
			string name;
			string firstName;
			string lastName;
			string role;
			string password;
			string schedule[7];
			string salary;
			input >> id;
			input >> password;
			input >> firstName;
			input >> lastName;
			input >> role;
			input >> salary;
			for (int i = 0; i < 7; i++) {
				input >> schedule[i];
			}
			name = firstName + " " + lastName;
			Employee employee(id, password, name, role, schedule, salary);
			employees.push_back(employee);
			OverwriteSaveFile(employees);
		}
	}
	//close file
	input.close();
	return employees;
}

Employee login(vector<Employee> employees, bool& loggedIn) {
	string id;
	string password;
	int index;
	bool found = false;
	cout << "Login" << endl;
	cout << "ID: ";
	cin >> id;
	for (int i = 0; i < employees.size(); i++) {
		if (id == employees[i].getID()) {
			index = i;
			found = true;
			break;
		}
	}

	if (found == true) {
		cout << "Enter password for user " << employees[index].getName() << " " << endl;
		cout << "Password: ";
		cin >> password;
		if (password == employees[index].getPassword()) {
			cout << "Logged in!" << endl;
			loggedIn = true;
			return employees[index];
		}
		else {
			cout << "Invalid password. Try again." << endl;
			//login(employees, loggedIn);
			Sleep(800);
			MainLoop();
		}
	}
	else {
		cout << "Invalid ID. Try again." << endl;
		//login(employees, loggedIn);
		Sleep(800);
		MainLoop();
	}
}

int Reset(vector<Employee> employees) {

	string opt;
	cout << "Do you want to reset the system? (Y/N)" << endl;
	cin >> opt;
	//Get line for the employee data
	if (opt == "Y" || opt == "y") {
		LoadingBar("Restarting.", 70);
		//Opens the file in which the employees are stored in
		fstream input;
		input.open("EmployeeData.txt", ofstream::out | ofstream::trunc);
		input.close();
		LoadEmployees();
		//Failsafe, if somehow the user resets this
		if (input.fail()) {
			LoadEmployees();
			return 1;
		}
	}
	else if (opt == "N" || opt == "n") {
		LoadEmployees();
	}

}


int getIndex(vector<Employee> employees, string id) {
	bool found = false;
	int index;
	for (int i = 0; i < employees.size(); i++) {
		if (employees[i].getID() == id) {
			found = true;
			index = i;
		}
	}
	if (found) {
		return index;
	}
	else {
		return 0;
	}
}

void DisplayEmployeeInformation(Employee employee) {
	system("CLS");
	cout << setw(55) << "Information" << endl;
	cout << setw(10) << "ID" << setw(25) << "Name" << setw(28) << "Password" << setw(24) << "Role" <<  setw(26) << "Salary/h" << endl;
	cout << setw(10) << employee.getID() << setw(25) << employee.getName() << setw(28) << employee.getPassword() << setw(24) << employee.getRole() <<  setw(26) << employee.getSalary() << endl;
}

//main loop that all other functions are childed to
void MainLoop() {
	system("CLS");
	Employee user;
	bool loggedIn = false;
	while (true) {
		system("Color 9F");
		//vector of all employees. Filled by the file, if the file exists
		vector<Employee> employees = LoadEmployees();
		//cout << "Employees size: " << employees.size() << endl;
		if (loggedIn == false) {
			user = login(employees, loggedIn);
		}
		else {
			user = employees[getIndex(employees, user.getID())];
		}
		//prompt user for input
		if (user.getRole() == "Manager") {
			//cout << "Employees size 3: " << employees.size() << endl;
			cout << "1: Add Employee" << endl;
			cout << "2: Remove Employee" << endl;
			cout << "3: Edit Employee" << endl;
			cout << "4: View Employees" << endl;
			cout << "5: Set Schedules" << endl;
			cout << "6: View Schedule" << endl;
			cout << "7: Logout" << endl;
			cout << "9: Reset Everything" << endl;
			string input;
			cin >> input;
			if (input == "1") {
				employees.push_back(AddEmployee(employees));
			}
			else if (input == "2") {
				EditEmployees(employees, "remove", user);
			}
			else if (input == "3") {
				EditEmployees(employees, "edit", user);
			}
			else if (input == "4") {
				ViewEmployees(employees);
			}
			else if (input == "5") {
				setSchedule(employees);
			}
			else if (input == "6") {
				ViewSchedule(user);
			}
			else if (input == "7") {
				LoadingBar("Exiting.", 50);
				cout << "Logged out!" << endl;
				MainLoop();
			}

			else if (input == "9") {
				system("CLS");
				loggedIn = false;
				Reset(employees);
			}
			else {
				cout << endl;
				cout << "Invalid input" << endl;
				cout << "Try again" << endl;
				cout << endl;
			}
		}
		else {
			cout << "User: " << user.getName() << endl;
			cout << "1: View Schedule" << endl;
			cout << "2: " << "View Information" << endl;
			cout << "3: Logout" << endl;
			string input;
			cin >> input;
			if (input == "1") {
				ViewSchedule(user);
			}
			else if (input == "2") {
				DisplayEmployeeInformation(user);
			}
			else if (input == "3") {
				LoadingBar("Exiting.", 50);
				cout << "Logged out!" << endl;
				MainLoop();
			}
		}
	}

}

int main() {
	LoadingBar("Loading.", 30);
	MainLoop();
}