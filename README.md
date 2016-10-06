# ReadOnly
Manage read only members in classes

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
