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
	ReadOnly<string> id{"123456"};
	
	Human() { }
	Human(const int& age, const string& name) {
		this->age = age;
		this->name = name;
		this->id.value = ""; // This is how you change ReadOnly values which doesn't have a setter
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
	cout << daniel.age << ' ' << daniel.id << endl;
	
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
