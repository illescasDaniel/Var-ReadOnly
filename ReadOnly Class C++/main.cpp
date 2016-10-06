#include <iostream>
#include "ReadOnly.hpp"
#include "Human.hpp" // Class example

using namespace std;

int main(int argc, const char * argv[]) {
	
	Human daniel;
	cout << daniel.age << endl;
	
	daniel.setAge(40);
	
	cout << daniel.age << endl;
	
	cout << daniel.name << endl;
	
	daniel.setName("Daniel");
	cout << daniel.name << '\n' << endl;
	
	Human daniel2(20, "Daniel", 170);
	cout << to_string(daniel2) << endl;
	
	daniel2.setHeight(400);
	
	cout << daniel2.height << endl;
	
	cout << daniel2.age + 10.6 << endl;
	
	cout << boolalpha << (daniel2.age == 10.6) << endl;
	cout << (daniel2.age < 21) << endl;
	
	
	cout << (10.1 + daniel.age + 20.9) << endl;
	
	cout << (10.7 == daniel.age) << endl;
	
	int age = daniel.age; // operator anyType() const {...}
	cout << age << endl;

    return 0;
}
