#pragma once
#include <iostream>
#include <string>
#include "Employee.h"
#include <string>
#include <iostream>
using namespace std;




	Employee::Employee(string id, string password, string name, string role, string schedule[7], string salary) {
		this->id = id;
		this->password = password;
		this->name = name;
		this->role = role;
		for (int i = 0; i < 7; i++) {
			this->schedule[i] = schedule[i];
		}
		this->salary = salary;

	}

	Employee::Employee(string id, string password, string name, string role, string salary) {
		this->id = id;
		this->password = password;
		this->name = name;
		this->role = role;
		this->salary = salary;
	}
	//default constructor with blank datafields
	Employee::Employee() {
		id = "";
		password = "";
		name = "";
		role = "";
	}

	//setters and getters for data fields
	void Employee::setID(string id) {
		this->id = id;
	}

	void Employee::setName(string name) {
		this->name = name;
	}

	void Employee::setRole(string role) {
		this->role = role;
	}

	void Employee::setPassword(string password) {
		this->password = password;
	}

	void Employee::setSalary(string salary) {
		this->salary = salary;
	}
	void Employee::setSchedule(int day, string hours) {
		schedule[day] = hours;
		cout << "Setted the day: " << day << " hours: " << hours << endl;
	}

	string Employee::getSchedule(int day) {
		return schedule[day];
	}

	string Employee::getID() {
		return id;
	}

	string Employee::getName() {
		return name;
	}

	string Employee::getRole() {
		return role;
	}

	string Employee::getPassword() {
		return password;
	}
	string Employee::getSalary() {
		return salary;
	}