#include <iostream>
#include "ReadOnly.hpp"

#include <vector>

using namespace std;

/// Class example
class Human {

	static bool setAge(const uint32_t& value) {
		return (value > 0 && value <= 150);
	}
	static bool setName(const string& value) {
		return (value.length() <= 20);
	}
	
public:
	ReadOnly<uint32_t> age {Human::setAge, 1};	// Setter & Default value
	ReadOnly<string> name {Human::setName};		// Setter
	ReadOnly<string> id = "123456";				// Initialize value, alternative: id {"123456"}
	ReadOnly<float> height = 170;
	ReadOnly<bool> isAlien;						// Default value: false, if it's int: 0, string: "" ...
	ReadOnly<char> chr = 'a';
	ReadOnly<vector<int>> numbers;				// Vectors are working too, more or less...
	
	// Only way of changing value of variables which doesn't have a setter
	Human() {
		numbers.value = {1,2,3};
	}
	Human(const int& age, const string& name) {
		this->age = age;
		this->name = name;
		
		numbers.value = {1,2,3,4};
		// This would be the only way of changing the default value if the variable doesn't have a setter:
		// height.value = 170;
	}
};

int main() {
	
	Human daniel;
	cout << "Age: " << daniel.age << ' ' << ", ID: " << daniel.id << endl;
	
	cout << "Height: " << daniel.height << endl;
	cout << boolalpha << "Is alien?: " << daniel.isAlien << endl;
	
	uint32_t age = daniel.age + 10;
	cout << "Age var: " << age << endl;
	
	daniel.age = 20;
	cout << "New age: " << daniel.age << endl;
	
	cout << "\n(Trying to assign age value: 5000)" << endl;
	daniel.age = 5000;
	
	cout << "\nAge with operators: " << 7 + daniel.age * 6 << endl;
	
	daniel.name = "daniel";
	cout << "Name: " << daniel.name << endl;
	
	cout << "\n(Trying to assign a too long value for the name)" << endl;
	daniel.name = "hahahahahahhahhahahahahahahah";
	cout << "\nName: " << daniel.name << endl;
	
	cout << "\n(Trying to change value of an attribute that doesn't have a setter specified)" << endl;
	daniel.id = "hello"; // Can't assign value because "id" doesn't have a setter
	
	cout << '\n' << "string: "  << daniel.id	   << endl; // string
	cout << "string to int: "   << stoi(daniel.id) << endl; // int
	cout << "string to float: " << stof(daniel.id) << endl; // float
	
	Human sofia(20, "Sofía");
	cout << '\n' << sofia.name << ' ' << sofia.age << ' ' << daniel.id << endl;
	
	cout << daniel.age << ' ' << daniel.age % 15 << endl;
	
	daniel.age = 150;
	cout << ++daniel.age << endl;
	
	
	cout << daniel.age-- << ' ' << --daniel.age << endl;
	
	daniel.age = 20;
	cout << (daniel.age *= 2) << ' ' << daniel.age + 10.2 << endl;
	
	cout << daniel.age << endl;
	cout << daniel.age++ << endl;
	cout << daniel.age << endl;
	
	daniel.age = 150;
	cout << (daniel.age += 20) << endl;
	
	string test = to_string(daniel.age);
	cout << test << endl;
	cout << char(toupper(daniel.chr)) << endl;
	
	cout << endl;
	cout << daniel.numbers[0] << ' ' << daniel.numbers[1] << endl;
    return 0;
}
