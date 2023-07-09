#include <iostream>
#include <string>
#include <vector>
using namespace std;

const long long INF = 100000000000000003; // INF
long long D; // 目标值
long long MinResult = INF; //大于D的最小值 初始化为INF

vector<long long> List; // n个数字
string ope; //由+和*组成的运算符串

bool exist; //是否能得到结果

//根据给定的运算符串，算出结果
void calc(string &tmp) 
{
    int len = tmp.length();
    long long x = List[0];
    for(int i = 0; i < len; i++)
    {
        if(tmp[i] == '+')
        {
            x += List[i + 1];
        }
        if(tmp[i] == '*')
        {
            x *= List[i + 1];
        }
        if(x >= MinResult)
        {
            return;
        }
    }
    if(x == D)
    {
        ope = tmp;
        exist = 1;
    }
    if(x > D && x < MinResult)
    {
        MinResult = x;
    }
    return;
}

// 形成运算符串tmp并调用calc(tmp)，n个数字之间要用到(n-1)个运算符，则存在2的(n-1)次方个不同的运算符串，枚举
void form(int n)
{
    for(long long i = 0; i < (1 << (n - 1)); i++)
    {
        long long j = i;
        string tmp;
        while(j >= 1)
        {
            tmp.append(j % 2 ? "*" : "+");
            j >>= 1;
        }
        while(int(tmp.length()) < n - 1)
        {
            tmp.append("+");
        }
        calc(tmp);
    }

}

int main()
{
    int n; //数字个数
    cin >> n;
    cin >> D;
    for(int i = 0; i < n; i++)
    {
        long long x;
        cin >> x;
        List.push_back(x);
    }
    form(n);
    if(exist)
    {
        for(int i = 0; i < n; i++)
        {
            cout << List[i];
            if(i < n - 1)
            {      
                cout << ope[i];
            }
        }
    }
    else
    {
        cout << "No" << endl;
        if(MinResult > D && MinResult < INF)
        {
            cout << MinResult << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
    return 0;
}