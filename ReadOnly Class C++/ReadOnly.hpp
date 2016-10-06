#ifndef ReadOnly_hpp
#define ReadOnly_hpp

#include <ostream>
#include <typeinfo>

#define template_anyType template <typename anyType>

/// Class to make read only variables. Their values can be change only in the classes that uses ReadOnly variables, but not externally
template <typename Type>
class ReadOnly {
	
	/* Friend classes (VERY IMPORTANT) */
	friend class Human;
	/* ... */
	
	Type value;
	
	ReadOnly & operator=(const Type& variable) {
		this->value = variable;
		return *this;
	}
	
public:
	
	ReadOnly() {}
	ReadOnly(const Type& variable) {
		this->value = variable;
	}
	
	// Cast ReadOnly variable to any type
	template_anyType
	operator anyType() const {
		return value;
	}
	
	// Operators overloading
	template_anyType anyType operator+(const anyType& variable) const { return value + variable; }
	template_anyType anyType operator-(const anyType& variable) const { return value - variable; }
	template_anyType anyType operator*(const anyType& variable) const { return value * variable; }
	template_anyType anyType operator/(const anyType& variable) const { return value / variable; }
	template_anyType anyType operator%(const anyType& variable) const { return value % variable; }
	
	template_anyType bool operator==(const anyType& variable) const { return value == variable; }
	template_anyType bool operator!=(const anyType& variable) const { return value != variable; }
	template_anyType bool operator< (const anyType& variable) const { return value < variable;  }
	template_anyType bool operator<=(const anyType& variable) const { return value <= variable; }
	template_anyType bool operator> (const anyType& variable) const { return value > variable;  }
	template_anyType bool operator>=(const anyType& variable) const { return value >= variable; }
	
	bool operator==(const char* variable) const { return value == variable; }
	bool operator!=(const char* variable) const { return value != variable; }
	bool operator< (const char* variable) const { return value < variable;  }
	bool operator<=(const char* variable) const { return value <= variable; }
	bool operator> (const char* variable) const { return value > variable;  }
	bool operator>=(const char* variable) const { return value >= variable; }
	
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
	
	// Display ReadOnly variables with cout (ostream)
	template <typename T>
	friend std::ostream & operator<<(std::ostream& os, const ReadOnly<T>& readOnlyVar) {
		return os << readOnlyVar.value;
	}
};


#endif /* ReadOnly_hpp */
