// MIT License
// Author: Daniel Illescas Romero (2016)

#ifndef ReadOnly_hpp
#define ReadOnly_hpp

#include <ostream>

/**
 Class to manage read only attributes
 */
template <typename Type>
class ReadOnly {

	Type value {};
	
	// Friend classes (important)
	friend class Human;
	
	inline ReadOnly() {}
	
	template <typename anyType>
	inline ReadOnly(const anyType& newValue) {
		value = newValue;
	}
	
	inline friend std::ostream & operator<<(std::ostream& os, const ReadOnly& variable) {
		return os << variable.value;
	}
	
public:
	inline operator Type() const {
		return value;
	}
};

#endif /* ReadOnly_hpp */
