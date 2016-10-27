# Var-ReadOnly

[![Build Status](https://travis-ci.org/illescasDaniel/ReadOnly.svg?branch=master)](https://travis-ci.org/illescasDaniel/ReadOnly)
[![Version](https://img.shields.io/badge/release-v2.1-green.svg)](https://github.com/illescasDaniel/ReadOnly/releases)
[![license](https://img.shields.io/github/license/mashape/apistatus.svg?maxAge=2592000)](https://github.com/illescasDaniel/ReadOnly/blob/master/LICENCE)  

Manage read only members and variables with setters in C++ classes.

There are two available classes: `Var` y and `ReadOnly`.  
The first one includes methods to set values using a setter, with the other you can declare read only attributes.

How to make it work
--------
Add your friend class in the ReadOnly/Var class:  
```C++

template <typename Type, typename Friend = ReadOnlyDefaultFriend>
class ReadOnly {

	/* Friend classes */
	friend class Human; // HERE
	friend Friend;

	/* ... */
};
```

Or use the second optional template parameter:
```C++

struct Foo {
	ReadOnly<int,Foo> number;
	Var<string,Foo> name;
	
	//...
};
```

Basic syntax
--------
```C++
class Human {

	static void setAge(int& age, const int& newAge) {
		if (newAge >= 0 && newAge <= 150) (age = newAge);
		else cerr << "Error, value doesn't satisfy setter condition" << endl;
	}

public:

	Var<int> age {Human::setAge};
	ReadOnly<string> name;

	Human(const string& name, const int& age) {
		this->name = name;
		this->age = age; // Calls the setAge function internally
	}

	void growUP() {
		age++;
	}
};

struct Car {

	// You can optionally pass the class/struct name as a parameter so you don't need to manually friend the class
	ReadOnly<string,Car> brand; 
	ReadOnly<string,Car> plateNumber;

	Car(const string& brand, const string& plateNumber) {
		this->brand = brand;
		this->plateNumber = plateNumber;
	}
};

int main() {

	Car toyota("Toyota", "123456AB");
	cout << toyota.brand << ' ' << toyota.plateNumber << endl;
	// toyota.brand = "another"; // Compilation ERROR

	Human daniel("Daniel", 20);
	cout << daniel.name << ' ' << daniel.age << endl;

	danie.name = "John"; // ERROR
	daniel.age = 100; // OK
	daniel.age = 1000; // ERROR
	daniel.growUP(); // OK

	cout << daniel.age << endl; // Output: 101
}

```

Motivation
--------
The main goal with these classes is to provide a quicker and prettier way of working with getters and setters and have variables which values can't be modified (ReadOnly) or only with specified setters (Var).

This is how it looks now:

```C++
Human daniel("Daniel", 20;  
cout << daniel.age << endl;  
daniel.age = 140; // Calls the setter funtion

daniel.name = "something"; // ERROR if name is a ReadOnly object
cout << daniel.name << endl; // OK
```  

This is how it looked before:

```C++
Human daniel("Daniel", 20; 
cout << daniel.getAge() << endl; 
cout << daniel.setAge(140) << endl;

cout << daniel.name << endl; // ERROR, name is private
cout << daniel.getName() << endl;
``` 

**Note**: by default constructors are private, hence you can only declare variables inside a friend class.  
