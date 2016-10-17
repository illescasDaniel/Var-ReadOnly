// MIT License
// Author: Daniel Illescas Romero (2016)

#ifndef ReadOnly_hpp
#define ReadOnly_hpp

#include <iostream>

using namespace std;

// OPERATORS macro
#define operatorAssignment(_op_, _op2_); template <typename anyType> auto operator _op_ (const anyType& var) { return (*this = *this _op2_ var); }

/// Class to make read only variables with an optional setter to change their values
template <typename Type>
class ReadOnly {

	/* FRIEND CLASSES (Important) */
	friend class Human;
	
	/* VARIABLES */
	
	// A setter function for the read only variable
	typedef bool (* setFunction)(const Type& variable);
	
	// By default, you can't change the value of the read only variables
	setFunction setterCondition = [](const Type& var){ return false; };
	bool hasASetter = false;
	Type value {}; // Initialize it to its default value (if is int: 0, string: "", etc)
	
	/* CONSTRUCTORS */
	
	ReadOnly() { }
	
	template <typename anyType>
	ReadOnly(const anyType& variable) {
		this->value = variable;
	}
	
	/// Specify a settter function and a default value
	ReadOnly(setFunction setterCondition, const Type& variable) {
		
		hasASetter = true;
		this->setterCondition = setterCondition;
		
		if (setterCondition(variable) == true) {
			this->value = variable;
		}
		else {
			cerr << "Error: default value (" << variable << ") doesn't satisfy setter condition" << endl;
		}
	}
	
	/// Specify a settter function
	ReadOnly(setFunction setterCondition) {
		hasASetter = true;
		this->setterCondition = setterCondition;
	}
	
public:
	
	/// Cast ReadOnly variable
	operator Type() const {
		return value;
	}
	
	/// Display ReadOnly variables with cout (ostream)
	friend ostream & operator<<(ostream& os, const ReadOnly& readOnlyVar) {
		return os << readOnlyVar.value;
	}
	
	/// Assign new value if it matches the setter condition
	template <typename anyType>
	ReadOnly & operator=(const anyType& variable) {
		
		if (setterCondition(variable) == true) {
			this->value = variable;
		}
		else if (!hasASetter) {
			cerr << "Error: attempting to write on a read only variable that doesn't have a setter" << endl;
		}
		else {
			cerr << "Error: new value (" << variable << ") doesn't satisfy setter condition" << endl;
		}
		
		return *this;
	}
	
	// Operators overloading
	operatorAssignment(+=, +) operatorAssignment(-=,-) operatorAssignment(*=,*) operatorAssignment(/=,/) operatorAssignment(%=,%)
	
	Type operator++() { return (*this = *this + 1); }
	Type operator--() { return (*this = *this - 1); }
	Type operator++(int foo) { return (this->operator++() + 1); }
	Type operator--(int foo) { return (this->operator--() + 1); }
	auto operator[](const int& index) { return value[index]; }
};

#endif /* ReadOnly_hpp */
