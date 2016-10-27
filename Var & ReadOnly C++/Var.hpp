// MIT License
// Author: Daniel Illescas Romero (2016)

#pragma once

#include <iostream>

// Operators assignment macro
#define operatorAssignment(_op_, _op2_); template <typename anyType> inline auto operator _op_ (const anyType& Var) { return (*this = *this _op2_ Var); }

class VarDefaultFriend{};

/// Class to make Variables with an optional setter to change their values
template <typename Type, typename Friend = VarDefaultFriend>
class Var {

	/* FRIEND CLASSES (Important) */
	friend Friend; // Generic friend class or struct passed as parameter
	friend class Human;
	
	/* VARIABLES */
	
	// A setter function for the variable
	typedef void (* setFunction)(Type& value, const Type& newValue);
	setFunction setter = [](Type&, const Type&) { std::cerr << "Error: Variable has no setter defined" << std::endl; };
	Type value {}; // Initialize it to its default value (if is int: 0, string: "", etc)
	
	/* CONSTRUCTORS */
	
	inline Var() { }
		
	template <typename anyType>
	inline Var(const anyType& Variable) {
		this->value = Variable;
	}
	
	/// Specify a settter function and a default value
	inline Var(setFunction setter, const Type& Variable) : setter(setter) {
		setter(value, Variable);
	}
	
	/// Specify a settter function
	inline Var(setFunction setter) : setter(setter) {
		setter(value, value);
	}
	
public:
	
	/// Cast Var Variable
	inline operator Type() const {
		return value;
	}
	
	/// Display Var Variables with cout (ostream)
	inline friend std::ostream & operator<<(std::ostream& os, const Var& VarVar) {
		return os << VarVar.value;
	}
	
	/// Assign new value if it matches the setter condition
	template <typename anyType>
	inline Var & operator=(const anyType& Variable) {
		setter(value, Variable);
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

#undef operatorAssignment
