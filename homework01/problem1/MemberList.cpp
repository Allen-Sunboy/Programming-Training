#include "MemberList.h"
#include "Member.h"

MemberList::MemberList(Member *List, int Num) {
    num = Num;
    for (int i = 0; i < num; i++) {
        list.insert({List[i].getname(), List[i].getage()});
    }
}