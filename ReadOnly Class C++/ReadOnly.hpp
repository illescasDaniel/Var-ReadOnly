// MIT License
// Author: Daniel Illescas Romero (2016)

#ifndef ReadOnly_hpp
#define ReadOnly_hpp

#include <iostream>

#define template_anyType template <typename anyType>

using namespace std;

/// Class to make read only variables with an optional setter to change their values
template <typename Type>
class ReadOnly {

	/** FRIEND CLASSES (Important) **/
	friend class Human;
	/* ... */
	
	// By default, you can't change the value of the read only variables
	static bool defaultSetterCondition(const Type& variable) {
		return false;
	}
	
	/** VARIABLES **/
	
	// A setter function for the read only variable
	typedef bool (* setFunction)(const Type& variable);
	setFunction setterCondition = ReadOnly::defaultSetterCondition;

	bool hasASetter = false;
	
	Type value;
	
	/** CONSTRUCTORS **/
	
	// You may enable the default constructor if you want -> ReadOnly() { }
	
	ReadOnly(const Type& variable) {
		this->value = variable; // Calls the operator=
	}
	
	// Specify a settter function and a default value
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
	
	// Cast ReadOnly variable to any type
	template_anyType
	operator anyType() const {
		return value;
	}
	
	// Display ReadOnly variables with cout (ostream)
	template <typename T>
	friend ostream & operator<<(ostream& os, const ReadOnly<T>& readOnlyVar) {
		return os << readOnlyVar.value;
	}
	
	/** Operators overloading **/
	
	// Assign new value if it matches the setter condition
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
	
	template_anyType anyType operator+(const anyType& var) const { return value + var; }
	template_anyType anyType operator-(const anyType& var) const { return value - var; }
	template_anyType anyType operator*(const anyType& var) const { return value * var; }
	template_anyType anyType operator/(const anyType& var) const { return value / var; }
	template_anyType anyType operator%(const anyType& var) const { return value % var; }
	
	template_anyType bool operator==(const anyType& var) const { return value == var; }
	template_anyType bool operator!=(const anyType& var) const { return value != var; }
	template_anyType bool operator< (const anyType& var) const { return value < var;  }
	template_anyType bool operator<=(const anyType& var) const { return value <= var; }
	template_anyType bool operator> (const anyType& var) const { return value > var;  }
	template_anyType bool operator>=(const anyType& var) const { return value >= var; }
	
	// friend operators overloading
	template_anyType friend anyType operator+(const anyType& var, const ReadOnly<Type>& var2) { return var + var2.value; }
	template_anyType friend anyType operator-(const anyType& var, const ReadOnly<Type>& var2) { return var - var2.value; }
	template_anyType friend anyType operator*(const anyType& var, const ReadOnly<Type>& var2) { return var * var2.value; }
	template_anyType friend anyType operator/(const anyType& var, const ReadOnly<Type>& var2) { return var / var2.value; }
	template_anyType friend anyType operator%(const anyType& var, const ReadOnly<Type>& var2) { return var % var2.value; }
	
	template_anyType friend bool operator==(const anyType& var, const ReadOnly<Type>& var2) { return var == var2.value; }
	template_anyType friend bool operator!=(const anyType& var, const ReadOnly<Type>& var2) { return var != var2.value; }
	template_anyType friend bool operator< (const anyType& var, const ReadOnly<Type>& var2) { return var < var2.value;  }
	template_anyType friend bool operator<=(const anyType& var, const ReadOnly<Type>& var2) { return var <= var2.value; }
	template_anyType friend bool operator> (const anyType& var, const ReadOnly<Type>& var2) { return var > var2.value;  }
	template_anyType friend bool operator>=(const anyType& var, const ReadOnly<Type>& var2) { return var >= var2.value; }
};

#endif /* ReadOnly_hpp */
