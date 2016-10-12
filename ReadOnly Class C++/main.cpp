#include <iostream>
#include "ReadOnly.hpp"

using namespace std;

/// Class example
class Human {

	static bool setAge(const int& value) {
		return (value >= 0 && value <= 150);
	}
	static bool setName(const string& value) {
		return (value.length() <= 20);
	}
	
public:
	ReadOnly<int> age{Human::setAge, 0};
	ReadOnly<string> name{Human::setName, ""};
	ReadOnly<string> lastName{"12.1"};
	
	Human() { }
	Human(const int& age, const string& name) {
		this->age = age;
		this->name = name;
		lastName.value = ""; // This is how you change ReadOnly values which doesn't have a setter
	}
	
	/* In this case, this assignment and constructor wouldn't make sense (and it wouldn't work) on a read only variable without a setter
	Human(const string& lastName) {
	 
		this->lastName = lastName;
		
		// But this always works without restriction
		// this->lastName.value = "";
	 }
	*/
};

int main() {

	Human daniel;
	cout << daniel.age << ' ' << daniel.lastName << endl;
	
	daniel.age = 20;
	
	cout << daniel.age << endl;
	
	daniel.age = 5000;
	
	cout << daniel.age << endl;
	
	//
	
	daniel.name = "daniel";
	cout << daniel.name << endl;
	
	daniel.name = "hahahahahahhahhahahahahahahah";
	cout << daniel.name << endl;
	
	daniel.lastName = "hello";
	cout << daniel.lastName << endl;		// string
	cout << stoi(daniel.lastName) << endl;	// int
	cout << stof(daniel.lastName) << endl;	// float

	//
	
	Human sofia(20, "Sofía");
	cout << sofia.name << ' ' << sofia.age << ' ' << daniel.lastName << endl;
	
    return 0;
}
