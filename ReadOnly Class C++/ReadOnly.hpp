// MIT License
// Author: Daniel Illescas Romero (2016)

#ifndef ReadOnly_hpp
#define ReadOnly_hpp

#include <iostream>

// Operators assignment macro
#define operatorAssignment(_op_, _op2_); template <typename anyType> auto operator _op_ (const anyType& var) { return (*this = *this _op2_ var); }

/// Class to make read only variables with an optional setter to change their values
template <typename Type>
class ReadOnly {

	/* FRIEND CLASSES (Important) */
	friend class Human;
	
	/* VARIABLES */
	
	// A setter function for the read only variable
	typedef void (* setFunction)(Type& value, const Type& newValue);
	setFunction setter = [](Type&, const Type&) { std::cerr << "Error: read only variable has no setter defined" << std::endl; };
	Type value {}; // Initialize it to its default value (if is int: 0, string: "", etc)
	
	/* CONSTRUCTORS */
	
	ReadOnly() { }
	
	/// Specify a settter function and a default value
	ReadOnly(setFunction setter, const Type& variable) : setter(setter) {
		setter(value, variable);
	}
	
	/// Specify a settter function
	ReadOnly(setFunction setter) : setter(setter) {
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
	friend std::ostream & operator<<(std::ostream& os, const ReadOnly& readOnlyVar) {
		return os << readOnlyVar.value;
	}
	
	/// Assign new value if it matches the setter condition
	template <typename anyType>
	ReadOnly & operator=(const anyType& variable) {
		setter(value, variable);
		return *this;
	}
	
	// Operators overloading
	operatorAssignment(+=, +) operatorAssignment(-=,-) operatorAssignment(*=,*) operatorAssignment(/=,/) operatorAssignment(%=,%)
	
	Type operator++() { return (*this = *this + 1); }
	Type operator--() { return (*this = *this - 1); }
	Type operator++(int) { return (this->operator++() - 1); }
	Type operator--(int) { return (this->operator--() + 1); }
	auto operator[](const int& index) { return value[index]; } // For vectors
};

#endif /* ReadOnly_hpp */
