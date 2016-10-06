#ifndef Human_hpp
#define Human_hpp

using namespace std;

class Human {
	
public:
	ReadOnly<int> age;
	ReadOnly<string> name;
	ReadOnly<float> height;
	
	Human() { }
	Human(const int& newAge, const string& newName, const float& newHeight) {
		setAge(newAge);
		setName(newName);
		setHeight(newHeight);
	}
	
	void setAge(const int& newAge) {
		
		const int MAX_AGE = 120;
		
		if (newAge < MAX_AGE)
			age = newAge;
		else
			fprintf(stderr, "\nAge is greater than the maximun age (120)\n\n");
	}
	
	void setName(const string& newName) {
		
		const uint16_t MAX_LENGTH = 30;
		
		if (newName.length() < MAX_LENGTH)
			name = newName;
		else
			fprintf(stderr, "\nName is longer than 30 characters\n\n");
	}
	
	void setHeight(const float& newHeight) {
		
		const float MAX_HEIGHT = 250;
		
		if (newHeight < MAX_HEIGHT && newHeight > 0)
			height = newHeight;
		else
			fprintf(stderr, "\nHeight value is invalid. Valid range: 0.0 - 250.0\n\n");
	}
	
	// ...
	
	friend string to_string(const Human& human) {
		
		return "Age: " + std::to_string(uint16_t(human.age)) +
			   " \nName: " + human.name +
			   " \nHeight: " + std::to_string(float(human.height));
	}
};

#endif /* Human_hpp */
