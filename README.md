# ReadOnly

[![Build Status](https://travis-ci.org/illescasDaniel/ReadOnly.svg?branch=master)](https://travis-ci.org/illescasDaniel/ReadOnly)  

Manage read only members in C++ classes.

How to make it work
------
Add your friend class in the ReadOnly class.  
```C++
class ReadOnly {

	/** Friend classes **/
	friend class Foo;

	/* ... */
};
```

Syntax
------
```C++
#include "ReadOnly.hpp"

class Foo {

	static bool setName(const string& value) {
		return (value.length() <= 20);
	}

public:

	// Initialize variable specifying a setter function and a default value
	ReadOnly<string> name{Foo::setName, ""}; 

	// This variable has a default value of 0, and can't be changed externally 
	// You could change its value internally accessing their value property (number.value) 
	ReadOnly<int> number{0}; 

	Foo() {}

	// This will assing the new value only if the specific setter function returns true
	Foo(const string& name) { 
		this->name = newName; 
	}
};

Foo object("John");

cout << object.name << ' ' << object.number << endl; // Output -> John 0

object.name = "Daniel"; // OK  
object.name = "aaaaaaaaaaaaaaaaaaaab" // ERROR

string objectName = object.name;  
string myName = "Daniel Illecas";  
object.name = myName;  

object.number = 10; // ERROR  

```

Motivation
--------
In OOP when you use classes you have attributes and methods. 
Problem is that on some languages, as C++, if you want people to access your variables they
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

Instead of accessing the attribute of the object, its property, you need to call a function, which doesn't make sense in OOP.  

With the ReadOnly class you can declare a variable which value will only change (externally) if a setter function is specified.  

**Note**: by default constructors are private so you can only declare variables inside a friend class.
