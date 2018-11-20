#include "person.h"
#include <string>

Person::Person(const std::string &name, int age, Gender gender) : _name(name), _age(age), _gender(gender) {
}

std::string Person::stringtoGender() {
    if( _gender == Gender::MALE) {
        return "male";
    }
    else {
        return "female";
    }
}

void Person::introduce() {
    std::cout << "Hi, I'm " << _name << ", a " << _age << " year old " << stringtoGender() << "." << std::endl;

}

std::string Person::getGoal() {
    std::cout << "My goal is: Live for the moment!" << std::endl;

}


