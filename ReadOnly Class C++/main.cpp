#include <iostream>
#include "ReadOnly.hpp"
#include "ReadOnly_alt.hpp"
#include <vector>
#include <stdexcept>
#include <memory>

using namespace std;

// Macros examples to manage errors
#define display_defaultError(_variable_) cerr << "Error: value (" << _variable_ << ") of variable (" #_variable_ ") doesn't satisfy setter condition" << endl
#define throw_defaultError(_variable_) throw logic_error("Error: value (" + to_string(_variable_) + ") of variable (" #_variable_ ") doesn't satisfy setter condition")

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
	ReadOnly<int> age {Human::setAge, 1};		// Setter & Default value
	ReadOnly<string> name {Human::setName};		// Setter
	ReadOnly<string> id = "123456";				// Initialize value, alternative: id {"123456"}
	ReadOnly<float> height = 170;
	ReadOnly<bool> isAlien;						// Default value: false, if it's int: 0, string: "" ...
	ReadOnly<char> chr = 'a';
	
	// Arrays
	ReadOnly<vector<int>> numbers;				// std::vector
	ReadOnly<unique_ptr<int[]>> numbers2;		// Smart pointer (similar to "int *")
	ReadOnly_alt<unique_ptr<int[]>> numbers3;
	
	ReadOnly_alt<int> age2 = 1;					// Alternative read only attribute (don't have setter)
	
	Human() {

		numbers.value = {1,2,3};
		numbers2.value = unique_ptr<int[]>(new int[3] {1,2,3});
		numbers3.value = unique_ptr<int[]>(new int[3] {1,2,3});
		
		isAlien.value = true;
		// height = 9000; ERROR, variable doesn't have a setter
	}
	Human(const int& age, const string& name) {
		this->age = age;
		this->age2 = age; // No need to use the "value" attribute in most cases
		this->name = name;
		
		numbers.value = {1,2,3,4};
		
		// If the variable doesn't have a setter you can set it's value to whatever you want if you use the "value" attribute
		// height.value = 999999.7;
	}
};

int main() {
	
	Human daniel;
	
	cout << "Trying to assign value to read only attribute \"isAlien\" that doesn't have a setter" << endl;
	daniel.isAlien = false; // ERROR
	
	cout << endl;
	
	cout << "Age: " << daniel.age << ", " << daniel.age2 << ' ' << ", ID: " << daniel.id << endl;
	
	cout << "Height: " << daniel.height << endl;
	cout << boolalpha << "Is alien?: " << daniel.isAlien << endl;
	
	int age = daniel.age + 10;
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
	
	cout << "Size of types\t->\t" << "int: " << sizeof(int) << "\tReadOnly_alt<int>: " << sizeof(ReadOnly_alt<int>)
	<< "\tReadOnly<int>: " << sizeof(ReadOnly<int>) << '\n' << endl;
	
	cout << "Size of array types: \n" << "ReadOnly<vector<int>>: " << sizeof(daniel.numbers) << '\n'
	<< "ReadOnly<unique_ptr<int[]>: " << sizeof(daniel.numbers2) << '\n'
	<< "ReadOnly_alt<unique_ptr<int[]>: " << sizeof(daniel.numbers3) << endl;

    return 0;
}
