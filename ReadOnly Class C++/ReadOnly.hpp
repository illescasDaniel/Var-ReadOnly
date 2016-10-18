// MIT License
// Author: Daniel Illescas Romero (2016)

#ifndef ReadOnly_hpp
#define ReadOnly_hpp

#include <iostream>

// Operators assignment macro
#define operatorAssignment(_op_, _op2_); template <typename anyType> inline auto operator _op_ (const anyType& var) { return (*this = *this _op2_ var); }

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
	
	inline ReadOnly() { }
	
	/// Specify a settter function and a default value
	inline ReadOnly(setFunction setter, const Type& variable) : setter(setter) {
		setter(value, variable);
	}
	
	/// Specify a settter function
	inline ReadOnly(setFunction setter) : setter(setter) {
		setter(value, value);
	}
	
	/// Cast a variable to Type
	template <typename anyType>
	inline ReadOnly(const anyType& variable) {
		this->value = variable;
	}
	
public:
	
	/// Cast ReadOnly variable
	inline operator Type() const {
		return value;
	}
	
	/// Display ReadOnly variables with cout (ostream)
	inline friend std::ostream & operator<<(std::ostream& os, const ReadOnly& readOnlyVar) {
		return os << readOnlyVar.value;
	}
	
	/// Assign new value if it matches the setter condition
	template <typename anyType>
	inline ReadOnly & operator=(const anyType& variable) {
		setter(value, variable);
		return *this;
	}
	
	// Operators overloading
	operatorAssignment(+=,+) operatorAssignment(-=,-) operatorAssignment(*=,*) operatorAssignment(/=,/) operatorAssignment(%=,%)
	
	inline Type operator++() { return (*this = *this + 1); }
	inline Type operator--() { return (*this = *this - 1); }
	inline Type operator++(int) { return (this->operator++() - 1); }
	inline Type operator--(int) { return (this->operator--() + 1); }
	inline auto operator[](const int& index) const { return value[index]; } // For vectors
};

#endif /* ReadOnly_hpp */
