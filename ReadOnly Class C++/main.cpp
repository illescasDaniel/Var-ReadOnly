#include <iostream>
#include "ReadOnly.hpp"

using namespace std;

class Human {
public:
	ReadOnly<int> age;
	ReadOnly<string> name;
	
	Human() {}
	Human(const int& age, const string& name) {
		this->age = age;
		this->name = name;
	}
	
	// Optional Setters
	void setAge(const int& age) {
		this->age = age;
	}
	void setName(const string& name) {
		this->name = name;
	}
};

int main(int argc, const char * argv[]) {
	
	Human daniel(20, "Daniel");
	
	cout << daniel.name << ' ' << daniel.age << endl;
	
	string name = daniel.name;
	string lastName = " Illescas";
	
	string completeName = daniel.name + lastName;
	
	daniel.setName(completeName);
	daniel.setAge(21);
	
	cout << "Name and last name: " << daniel.name << endl;
	cout << 1 + daniel.age + 10 << endl;

    return 0;
}
