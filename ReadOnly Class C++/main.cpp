#include <iostream>
#include "ReadOnly.hpp"

using namespace std;

/// Class example
class Human {

	static bool setAge(const int& value) {
		return (value > 0 && value <= 150);
	}
	static bool setName(const string& value) {
		return (value.length() <= 20);
	}
	
public:
	ReadOnly<int> age {Human::setAge, 1};	// Setter & Default value
	ReadOnly<string> name {Human::setName}; // Setter
	ReadOnly<string> id = "123456";			// Initialize value, alternative: id {"123456"}
	
	ReadOnly<string> test;
	
	// Only way to change value of variables which doesn't have a setter
	Human() {
		test.value = "bla";
	}
	Human(const int& age, const string& name) {
		this->age = age;
		this->name = name;
	}
};

int main() {
	
	Human daniel;
	cout << daniel.age << ' ' << daniel.id << endl;
	
	cout << "a: " << daniel.test << endl;
	
	daniel.age = 20;
	
	cout << daniel.age << endl;
	
	daniel.age = 5000;
	
	cout << 7 + daniel.age * 6 << endl;
	
	//
	
	daniel.name = "daniel";
	cout << daniel.name << endl;
	
	daniel.name = "hahahahahahhahhahahahahahahah";
	cout << daniel.name << endl;
	
	daniel.id = "hello"; // Can't assign value because "id" doesn't have a setter
	
	cout << daniel.id << endl;		  // string
	cout << stoi(daniel.id) << endl;  // int
	cout << stof(daniel.id) << endl;  // float

	//
	
	Human sofia(20, "Sofía");
	cout << sofia.name << ' ' << sofia.age << ' ' << daniel.id << endl;
	
    return 0;
}
