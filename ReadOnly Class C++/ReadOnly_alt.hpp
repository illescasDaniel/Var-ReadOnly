// MIT License
// Author: Daniel Illescas Romero (2016)

#ifndef ReadOnly_alt_hpp
#define ReadOnly_alt_hpp

#include <ostream>

/**
 Alternative ReadOnly class which is lighter and more efficiente in memory (and performance?)
 
 If you only use this class you can change it's name to just "ReadOnly"
 */
template <typename Type>
class ReadOnly_alt {

	Type value {};
	
	// Friend classes (add your classes here!)
	friend class Human;
	
	inline ReadOnly_alt() {}
	
	template <typename anyType>
	inline ReadOnly_alt(const anyType& newValue) {
		value = newValue;
	}
	
	inline friend std::ostream & operator<<(std::ostream& os, const ReadOnly_alt& variable) {
		return os << variable.value;
	}
	
public:
	inline operator Type() {
		return value;
	}
};

#endif /* ReadOnly_hpp */
