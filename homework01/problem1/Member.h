#pragma once
#include <string>


class Member
{
    private:
    std::string name;
    int age;

    public:
    Member(std::string Name, int Age): name(Name), age(Age){}
    Member(): name("?"), age(0){}
    friend std::ostream &operator<<(std::ostream &out, const Member &member);
    std::string getname();
    int getage();
    
};