#pragma once
#include "Member.h"
#include <map>

class MemberList
{
    private:
    int num;
    std::map<std::string, int> list;

    public:
    MemberList(Member *List, int Num);
    int &operator[](std::string name)
    {
        return list[name];
    }

};