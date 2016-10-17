// MIT License
// Author: Daniel Illescas Romero (2016)

#ifndef ReadOnly_hpp
#define ReadOnly_hpp

#include <iostream>

using namespace std;

// OPERATORS macro
#define operatorAssignment(_op_, _op2_); template <typename anyType> auto operator _op_ (const anyType& var) { return (*this = *this _op2_ var); }

// Default error message
#define display_defaultError(_variable_) cerr << "Error: value (" << _variable_ << ") of variable (" #_variable_ ") doesn't satisfy setter condition" << endl

/// Class to make read only variables with an optional setter to change their values
template <typename Type>
class ReadOnly {

	/* FRIEND CLASSES (Important) */
	friend class Human;
	
	/* VARIABLES */
	
	// A setter function for the read only variable
	typedef void (* setFunction)(Type& value, const Type& newValue);
	setFunction setter;
	bool hasSetter = false;
	Type value {}; // Initialize it to its default value (if is int: 0, string: "", etc)
	
	/* CONSTRUCTORS */
	
	ReadOnly() { }
	
	/// Specify a settter function and a default value
	ReadOnly(setFunction setter, const Type& variable) : hasSetter(true), setter(setter) {
		setter(value, variable);
	}
	
	/// Specify a settter function
	ReadOnly(setFunction setter) : hasSetter(true), setter(setter) {
		setter(value, value);
	}
	
	/// Cast a variable to Type
	template <typename anyType>
	ReadOnly(const anyType& variable) {
		this->value = variable;
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
		
		if (hasSetter) setter(value, variable);
		else cerr << "Error: read only variable doesn't have a setter" << endl;
		
		return *this;
	}
	
	// Operators overloading
	operatorAssignment(+=, +) operatorAssignment(-=,-) operatorAssignment(*=,*) operatorAssignment(/=,/) operatorAssignment(%=,%)
	
	Type operator++() { return (*this = *this + 1); }
	Type operator--() { return (*this = *this - 1); }
	Type operator++(int foo) { return (this->operator++() + 1); }
	Type operator--(int foo) { return (this->operator--() + 1); }
	auto operator[](const int& index) { return value[index]; } // For vectors
};

#endif /* ReadOnly_hpp */
