// MIT License
// Author: Daniel Illescas Romero (2016)

#ifndef ReadOnly_hpp
#define ReadOnly_hpp

#include <iostream>

// OPERATORS macros
#define operator(...); template <typename anyType> auto operator __VA_ARGS__ (const anyType& var) const { return (value __VA_ARGS__ var); }
#define friendOperator(...); template <typename anyType> friend auto operator __VA_ARGS__ (const anyType& var, const ReadOnly& var2) { return (var __VA_ARGS__ var2.value); }
#define operators(...); operator(__VA_ARGS__) friendOperator(__VA_ARGS__)

// String to other types macro
#define func(...); friend auto __VA_ARGS__ (const ReadOnly& var) { return __VA_ARGS__ (var.value); }

using namespace std;

/// Class to make read only variables with an optional setter to change their values
template <typename Type>
class ReadOnly {

	/* FRIEND CLASSES (Important) */
	friend class Human;
	/* ... */
	
	// By default, you can't change the value of the read only variables
	static bool defaultSetterCondition(const Type& variable) {
		return false;
	}
	
	/* VARIABLES */
	
	// A setter function for the read only variable
	typedef bool (* setFunction)(const Type& variable);
	
	setFunction setterCondition = ReadOnly::defaultSetterCondition;
	bool hasASetter = false;
	Type value;
	
	/* CONSTRUCTORS */
	
	// You may enable the default constructor if you want -> ReadOnly() { }
	
	ReadOnly(const Type& variable) {
		this->value = variable; // Call the operator=
	}
	
	/// Specify a settter function and a default value
	ReadOnly(setFunction setterCondition, const Type& variable) {
		
		hasASetter = true;
		this->setterCondition = setterCondition;
		
		if (setterCondition(variable) == true) {
			this->value = variable;
		}
		else {
			cerr << "Error: default value doesn't match setter condition" << endl;
		}
	}
	
public:
	
	/// Cast ReadOnly variable to any type
	template <typename anyType>
	operator anyType() const {
		return value;
	}
	
	/// Display ReadOnly variables with cout (ostream)
	friend ostream & operator<<(ostream& os, const ReadOnly& readOnlyVar) {
		return os << readOnlyVar.value;
	}
	
	// String to other type conversion
	func(stoi) func(stol) func(stof) func(stod) func(stoll) func(stold) func(stoul) func(stoull)
	
	/// Assign new value if it matches the setter condition
	ReadOnly & operator=(const Type& variable) {
		
		if (setterCondition(variable) == true) {
			this->value = variable;
		}
		else if (!hasASetter) {
			cerr << "Error: attempting to write on a read only variable which doesn't have a setter" << endl;
		}
		else {
			cerr << "Error: new value doesn't match setter condition" << endl;
		}
		
		return *this;
	}
	
	// Operators overloading (included friend operators)
	operators(+) operators(-) operators(*) operators(/) operators(==) operators(!=) operators(<) operators(<=) operators(>) operators(>=)
};

#endif /* ReadOnly_hpp */
