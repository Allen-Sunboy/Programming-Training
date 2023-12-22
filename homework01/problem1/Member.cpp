#include "Member.h"
#include <iostream>

std::ostream &operator<<(std::ostream &out, const Member &member) {
    out << member.name << ", " << member.age;
    return out;
}

std::string Member::getname() { return name; }

int Member::getage() { return age; }