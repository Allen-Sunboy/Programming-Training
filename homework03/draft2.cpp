#include <iostream>
#include <ctime>
using namespace std;

const int MAXN = 300;

int a[MAXN][MAXN][MAXN];
int b[MAXN][MAXN][MAXN];
int c[MAXN][MAXN][MAXN];

int N;

int main()
{
    while(cin >> N)
    {
        cout << "ijk: ";
        clock_t start1 = clock();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k < N; k++)
                    c[i][j][k] = a[i][j][k] + b[i][j][k];

        clock_t end1 = clock();
        auto dur1 = end1 - start1;
        cout << dur1 << endl;
    }

    return 0;
}