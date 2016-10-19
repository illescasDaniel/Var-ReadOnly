# ReadOnly

[![Build Status](https://travis-ci.org/illescasDaniel/ReadOnly.svg?branch=master)](https://travis-ci.org/illescasDaniel/ReadOnly)
[![Version](https://img.shields.io/badge/release-v1.5.1-green.svg)](https://github.com/illescasDaniel/ReadOnly/releases)
[![license](https://img.shields.io/github/license/mashape/apistatus.svg?maxAge=2592000)](https://github.com/illescasDaniel/ReadOnly/blob/master/LICENCE)  

Manage read only members in C++ classes.

There are two available classes: `ReadOnly` y and `ReadOnly_alt`.  
The first one includes methods to set values using a setter (optional), the other doesn't but it's' more efficient (*).

How to make it work
--------
Add your friend class in the ReadOnly/ ReadOnly_alt class.  
```C++
class ReadOnly {

	/** Friend classes **/
	friend class Foo;

	/* ... */
};
```

Basic syntax (ReadOnly)
--------
```C++
#include "ReadOnly.hpp"

class Foo {

	static void setName(string& name, const string& newName) {
		if (newName.length() <= 20) (name = newName);
		else cerr << "Error: new value doesn't satisfy setter condition" << endl;
	}

public:

	// Initialize variable specifying a setter function
	ReadOnly<string> name {Foo::setName}; 

	// This variable has a default value of 10, and can't be changed externally 
	// You could change its value internally accessing its value property (number.value)
	ReadOnly<int> number = 10; 

	Foo() {}

	// This will assign the new value only if is matches the setter condition
	Foo(const string& name) { 
		this->name = name; 
	}
};

Foo object("John");

cout << object.name << ' ' << object.number << endl; // Output: John 10

object.name = "Daniel"; // OK  
object.name = "aaaaaaaaaaaaaaaaaaaab" // ERROR

string objectName = object.name;  
string myName = "Daniel Illecas";  
object.name = myName;  

object.number = 20; // ERROR, variable is read only and doesn't have a setter

```

Basic sytax (ReadOnly_alt)
--------
```C++
#include "ReadOnly_alt.hpp"

struct Human {

	// Read only attribute (doesn't have a setter function)
	ReadOnly_alt<int> age;
	ReadOnly_alt<string> name; 

	Human(const int& age, const string& name) { 
		this->age = age;
		this->name = name; 
	}

	// You could make an external setter function here, but you might want to use ReadOnly instead...
};

Human daniel(20, "Daniel");

cout << daniel.name << ' ' << daniel.age << endl; // OK

daniel.name = "John"; // ERROR!
daniel.age = 21;	  // ERROR!

```

Motivation
--------
In OOP when you use classes you have attributes and methods. 
The problem is that on some languages, as C++, if you want someone to access your variables, they
have to use (most of the times) getters, so instead of something like: 

```C++
Human daniel;  
cout << daniel.age << endl;  
```  

You would have to do this: 

```C++
Human daniel;  
cout << daniel.getAge() << endl; 
```

Instead of accessing the attribute of the object, its property, you need to call a function, **which doesn't make sense in OOP**.  

With the ReadOnly class you can declare a variable which value will only change (externally) if a setter function is specified and if the value satisfy the setter.  

**Note**: by default constructors are private, hence you can only declare variables inside a friend class.  

(*) __Type Sizes__ -> `int`: 4 bytes, `ReadOnly_alt<int>`: 4, `ReadOnly<int>`: 16
