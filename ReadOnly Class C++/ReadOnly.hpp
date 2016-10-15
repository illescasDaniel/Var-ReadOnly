// MIT License
// Author: Daniel Illescas Romero (2016)

#ifndef ReadOnly_hpp
#define ReadOnly_hpp

#include <iostream>

using namespace std;

// OPERATORS macros
#define operator_(_op_); template <typename anyType> auto operator _op_ (const anyType& var) const { return (value _op_ var); }
#define friendOperator(_op_); template <typename anyType> friend auto operator _op_ (const anyType& var, const ReadOnly& var2) { return (var _op_ var2.value); }
#define operatorAssignment(_op_, _op2_); template <typename anyType> auto operator _op_ (const anyType& var) { return (*this = *this _op2_ var); }
#define operators(_op_); operator_(_op_) friendOperator(_op_)

// String to other types macro
#define func(stringTo); friend auto stringTo(const ReadOnly& var) { return stringTo(var.value); }

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
			cerr << "Warning: default value (" << variable << ") doesn't satisfy setter condition" << endl;
		}
	}
	
	/// Specify a settter function
	ReadOnly(setFunction setterCondition) {
		hasASetter = true;
		this->setterCondition = setterCondition;
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
	
	// String related functions
	func(stoi) func(stol) func(stof) func(stod) func(stoll) func(stold) func(stoul) func(stoull)
	func(to_string) func(toupper) func(tolower)
	
	/// Assign new value if it matches the setter condition
	template <typename anyType>
	ReadOnly & operator=(const anyType& variable) {
		
		if (setterCondition(variable) == true) {
			this->value = variable;
		}
		else if (!hasASetter) {
			cerr << "Error: attempting to write on a read only variable which doesn't have a setter" << endl;
		}
		else {
			cerr << "Error: new value (" << variable << ") doesn't satisfy setter condition" << endl;
		}
		
		return *this;
	}
	
	// Operators overloading (included friend operators)
	operators(+) operators(-) operators(*) operators(/) operators(%) operators(==) operators(!=) operators(<) operators(<=) operators(>) operators(>=)
	operatorAssignment(+=, +) operatorAssignment(-=,-) operatorAssignment(*=,*) operatorAssignment(/=,/) operatorAssignment(%=,%)
	
	Type operator++() { return (*this = *this + 1); }
	Type operator--() { return (*this = *this - 1); }
	Type operator++(int foo) { return (this->operator++() - 1); }
	Type operator--(int foo) { return (this->operator--() - 1); }
	auto operator[](const int& index) { return value[index]; }
};

#endif /* ReadOnly_hpp */
