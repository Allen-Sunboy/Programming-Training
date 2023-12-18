#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

const double eps = 0.0001; //误差修正

bool exist; // 是否能算出24

set<string> expression; //算式

//4个数字，List中每个元素是pair，分别为数字double以及其运算式string，比如可能某个元素的first是5，second是"1+4"
vector<pair<double, string>> List;

//获得由这2个数所组合成的8个结果
vector<pair<double, string>> two(vector<pair<double, string>> &tmp, int i, int j) 
{
    if (tmp[i].second != to_string((int)tmp[i].first))
    {
        tmp[i].second = "(" + tmp[i].second + ")";
    }

    if (tmp[j].second != to_string((int)tmp[j].first))
    {
        tmp[j].second = "(" + tmp[j].second + ")";
    }

    vector<pair<double, string>> comb;

    string str1 = tmp[i].second + "+" + tmp[j].second;
    string str2 = tmp[i].second + "-" + tmp[j].second;
    string str3 = tmp[i].second + "*" + tmp[j].second;
    string str4 = tmp[i].second + "/" + tmp[j].second;
    string str5 = tmp[j].second + "+" + tmp[i].second;
    string str6 = tmp[j].second + "-" + tmp[i].second;
    string str7 = tmp[j].second + "*" + tmp[i].second;
    string str8 = tmp[j].second + "/" + tmp[i].second;

    double d1 = tmp[i].first + tmp[j].first;
    double d2 = tmp[i].first - tmp[j].first;
    double d3 = tmp[i].first * tmp[j].first;
    double d4 = tmp[i].first / tmp[j].first;
    double d5 = tmp[j].first + tmp[i].first;
    double d6 = tmp[j].first - tmp[i].first;
    double d7 = tmp[j].first * tmp[i].first;
    double d8 = tmp[j].first / tmp[i].first;

    comb.push_back({d1, str1});
    comb.push_back({d2, str2});
    comb.push_back({d3, str3});
    comb.push_back({d4, str4});
    comb.push_back({d5, str5});
    comb.push_back({d6, str6});
    comb.push_back({d7, str7});
    comb.push_back({d8, str8});

    return comb;
}


//递归
void calc(vector<pair<double, string>> &List, int n, double sum)
{
    if (n == 1) //递归终点
    {
        if (sum == 24 || sum - eps == 24 || sum + eps == 24 )
        {
            exist = 1;
            expression.insert(List[0].second);
            return;
        }
        return;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            auto tmp = List;
            auto comb = two(tmp, i, j);

            tmp.erase(tmp.begin()+j);
            tmp.erase(tmp.begin()+i);

            for (int k = 0; k < 8; k++)
            {
                auto tmp2 = tmp;
                tmp2.insert(tmp2.begin(), comb[k]);
                calc(tmp2, n-1, tmp2[0].first);
            }
        }
    }
    return;
}

int main()
{
    for (int i = 0; i < 4; i++)
    {
        double x;
        cin >> x;
        List.push_back({x, to_string((int)x)});
    }

    calc(List, 4, 0);

    if (exist)
    {
        for (auto i: expression)
        {
            cout << i << endl;
        }
    }
    else
    {
        cout << "no" << endl;
    }

    return 0;
}