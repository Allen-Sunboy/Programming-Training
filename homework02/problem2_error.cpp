// !!!
// 递归的算法，但是容易超时，时间效率不高，不采用!!

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

const long long MAXN = 100000000000000003;

long long D; // 目标值

long long MinResult = MAXN; // 大于D的最小值
vector<long long> List; // n个数字
string ope; // 由+和*组成的运算符串


bool exist; 

void calc(vector<long long> &List, string &str)
{
    long long List0 = List[0];
    if (List.size() == 1)  // 递归终点，List只剩一个数，即List[0]
    {
        if (List0 > D)
        {
            if (List0 < MinResult)
            {
                MinResult = List0;
            }
        }
        if (List0 == D) //如果算得结果是D
        {
            ope = str;
            exist = 1;
        }
        return;
    }

    if (List0 > MinResult) //特判，如果算得结果已经超过大于D的最小值，则不再递归，提前返回，这样可减少递归消耗和运行时长
    {
        return;
    }

    string str1 = str + "+";
    string str2 = str + "*";

    long long x0 = List[0];
    long long x1 = List[1];

    long long y1 = x0 + x1; // x0 + x1
    long long y2 = x0 * x1; // x0 * x1
    // 每次取List的前2个数字，分别进行+和*
    
    vector<long long> tmp = List;
    tmp.erase(tmp.begin(), tmp.begin() + 2);
    
    auto tmp1 = tmp;
    auto tmp2 = tmp;
    //构建2个新vector，与List的区别在于，删掉了这前2个数，而在前面补上所算得的结果

    tmp1.insert(tmp1.begin(), y1);
    tmp2.insert(tmp2.begin(), y2);

    calc(tmp1, str1);
    calc(tmp2, str2);
    return;
}

int main()
{
    int n;
    cin >> n;
    cin >> D;
    for (int i = 0; i < n; i++)
    {
        long long in;
        cin >> in;
        List.push_back(in);
    }
    string tmp; //空字符串
    tmp.clear(); //清空

    //test
    clock_t start = clock();

    calc(List, tmp);
    
    //test
    clock_t finish = clock();
    auto duration = (finish - start) / CLOCKS_PER_SEC;
    cout << duration << endl;
    
    if (exist)
    {
        for (int i = 0; i < n; i++)
        {
            cout << List[i];
            if (i < n - 1)
            {      
                cout << ope[i];
            }
        }
    }
    else
    {
        cout << "No" << endl;
        if (MinResult > D && MinResult != MAXN)
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