#pragma once
#include <iostream>
#include <string>
using namespace std;

class Employee {
	string id;
	string password;
	string name;
	string role;
	string salary;
	string schedule[7] = { "X", "X", "X", "X","X","X","X" };
public:
	//constructor for data fields
	Employee(string id, string password, string name, string role, string schedule[7], string salary);

	Employee(string id, string password, string name, string role, string salary);
	//default constructor with blank datafields
	Employee();

	//setters and getters for data fields
	void setID(string id);

	void setName(string name);

	void setRole(string role);

	void setPassword(string password);

	void setSalary(string salary);
	void setSchedule(int day, string hours);

	string getSchedule(int day);

	string getID();

	string getName();

	string getRole();
	string getPassword();
	string getSalary();
};