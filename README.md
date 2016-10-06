# ReadOnly
Manage read only members in C++ classes.

How to make it work
------
Add your friend class in the ReadOnly class.  
```C++
	class ReadOnly {

		/* Friend classes */
		friend class Foo;
	
		/* ... */
	};
```

Syntax
------
```C++
	#include "ReadOnly.hpp"
	
	class Foo {
	
	public:
		ReadOnly<string> name;
		ReadOnly<int> number = 10; // or: ReadOnly<int> number(10);

		Foo() {}
		Foo(const string& newName) { name = newName; } // Foo must be a friend class of ReadOnly

		// Optional setter
		void setName(const string& newName) { /* ... */ }
	};

	Foo object("John");

	cout << object.name << ' ' << object.number << endl;

	// ERROR -> object.name = "Daniel";

	string objectName = object.name;
	string myName = "Daniel";

	object.setName(myName);

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
