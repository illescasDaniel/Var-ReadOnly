#include <iostream>
#include "Var.hpp"
#include "ReadOnly.hpp"
#include <vector>
#include <stdexcept>
#include <memory>

using namespace std;

// Macros examples to manage errors
#define display_defaultError(_Variable_) cerr << "Error: value (" << _Variable_ << ") of Variable (" #_Variable_ ") doesn't satisfy setter condition" << endl
#define throw_defaultError(_Variable_) throw logic_error("Error: value (" + to_string(_Variable_) + ") of Variable (" #_Variable_ ") doesn't satisfy setter condition")

/// Class example
class Human {
	
	static void setName(string& name, const string& newName) {
		if (newName.length() <= 20) (name = newName);
		else display_defaultError(newName);
	}
	static void setAge(int& age, const int& newAge) {
		if (newAge > 0 && newAge <= 150) (age = newAge);
		else display_defaultError(newAge); // or: throw_defaultError(newAge)
	}
	
public:
	Var<int> age {Human::setAge, 1};		// Setter & Default value
	Var<string> name {Human::setName};		// Setter
	Var<string> id = "123456";				// Initialize value, alternative: id {"123456"}
	Var<float> height = 170;
	Var<bool> isAlien;						// Default value: false, if it's int: 0, string: "" ...
	Var<char> chr = 'a';
	
	// Arrays
	Var<vector<int>> numbers;				// std::vector
	Var<unique_ptr<int[]>> numbers2;		// Smart pointer (similar to "int *")
	ReadOnly<unique_ptr<int[]>> numbers3;
	
	ReadOnly<int> age2 = 1;					// Read only attribute (don't have setter)
	
	Human() {

		numbers.value = {1,2,3};
		numbers2.value = unique_ptr<int[]>(new int[3] {1,2,3});
		numbers3.value = unique_ptr<int[]>(new int[3] {1,2,3});
		
		isAlien.value = true;
		// height = 9000; ERROR, Variable doesn't have a setter
	}
	Human(const int& age, const string& name) {
		this->age = age;
		this->age2 = age; // No need to use the "value" attribute in most cases
		this->name = name;
		
		numbers.value = {1,2,3,4};
		
		// If the Variable doesn't have a setter you can set it's value to whatever you want if you use the "value" attribute
		// height.value = 999999.7;
	}
};

struct Car {
	
	ReadOnly<uint16_t,Car> wheels = 4;
	ReadOnly<string,Car> plateNumber;
	ReadOnly<string,Car> brand;
	// ...
	
	Car(const string& plateNumber, const string& brand, const uint16_t& wheels) {
		this->plateNumber = plateNumber;
		this->brand = brand;
		this->wheels = wheels;
	}
};

int main() {
	
	
	Car toyota("2020CE", "Toyota", 4);
	
	cout << toyota.wheels << endl;
	//toyota.brand = "another"; // Compilation ERROR
	
	//

	Human daniel;
	
	cout << "Trying to assign a value to a variable (\"isAlien\") that doesn't have a setter" << endl;
	daniel.isAlien = false; // ERROR
	
	cout << endl;
	
	cout << "Age: " << daniel.age << ", " << daniel.age2 << ' ' << ", ID: " << daniel.id << endl;
	
	cout << "Height: " << daniel.height << endl;
	cout << boolalpha << "Is alien?: " << daniel.isAlien << endl;
	
	int age = daniel.age + 10;
	cout << "Age Var: " << age << endl;
	
	daniel.age = 20;
	cout << "New age: " << daniel.age << endl;
	
	cout << "\n(Trying to set age value to: 5000)" << endl;
	daniel.age = 5000;
	
	cout << "\nAge with operators: " << 7 + daniel.age * 6 << endl;
	
	daniel.name = "daniel";
	cout << "Name: " << daniel.name << endl;
	
	cout << "\n(Trying to change the name for a too long value)" << endl;
	daniel.name = "hahahahahahhahhahahahahahahah";
	cout << "Name: " << daniel.name << endl;
	
	cout << "\n(Trying to change value of an attribute that doesn't have a setter specified)" << endl;
	daniel.id = "hello"; // Can't assign value because "id" doesn't have a setter
	
	cout << '\n' << "string: "  << daniel.id	   << endl; // string
	cout << "string to int: "   << stoi(daniel.id) << endl; // int
	cout << "string to float: " << stof(daniel.id) << endl; // float
	
	Human sofia(20, "Sofía");
	cout << '\n' << sofia.name << ' ' << sofia.age << ' ' << sofia.age2 << ' ' << daniel.id << endl;
	
	cout << daniel.age << ' ' << daniel.age % 15 << endl;
	
	daniel.age = 150;
	cout << ++daniel.age << endl;

	daniel.age = 20;
	cout << daniel.age++ << ' ' << ++daniel.age << endl;
	cout << daniel.age-- << ' ' << --daniel.age << endl;
	
	cout << (daniel.age *= 2) << ' ' << daniel.age + 10.2 << endl;
	
	cout << daniel.age << endl;
	cout << daniel.age++ << endl;
	cout << daniel.age << endl;
	
	daniel.age = 150;
	cout << (daniel.age += 20) << endl;
	
	string test = to_string(daniel.age);
	cout << test << endl;
	cout << char(toupper(daniel.chr)) << endl;
	
	cout << daniel.numbers[0] << ' ' << daniel.numbers[1] << endl;
	
	cout << "\nSize of types (bytes):\n" << "int: " << sizeof(int) << "\nReadOnly<int>: " << sizeof(ReadOnly<int>)
	<< "\nVar<int>: " << sizeof(Var<int>) << '\n' << endl;
	
	cout << "Size of array types: \n" << "Var<vector<int>>: " << sizeof(daniel.numbers) << '\n'
	<< "Var<unique_ptr<int[]>: " << sizeof(daniel.numbers2) << '\n'
	<< "ReadOnly<unique_ptr<int[]>: " << sizeof(daniel.numbers3) << endl;
	
}
