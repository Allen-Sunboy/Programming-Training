#include <iostream>
#include <ctime>
using namespace std;

const int MAXN = 300;

int a[MAXN][MAXN][MAXN];
int b[MAXN][MAXN][MAXN];
int c[MAXN][MAXN][MAXN];

int N;

void test_ijk()
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

void test_ikj()
{
    cout << "ikj: ";
    clock_t start2 = clock();
    for (int i = 0; i < N; i++)
	    for (int k = 0; k < N; k++)
		    for (int j = 0; j < N; j++)
			    c[i][j][k] = a[i][j][k] + b[i][j][k];

    clock_t end2 = clock();
    auto dur2 = end2 - start2;
    cout << dur2 << endl;
}

void test_jik()
{
    cout << "jik: ";
    clock_t start3 = clock();
    for (int j = 0; j < N; j++)
	    for (int i = 0; i < N; i++)
		    for (int k = 0; k < N; k++)
			    c[i][j][k] = a[i][j][k] + b[i][j][k];

    clock_t end3 = clock();
    auto dur3 = end3 - start3;
    cout << dur3 << endl;

}

void test_jki()
{
    cout << "jki: ";
    clock_t start4 = clock();
    for (int j = 0; j < N; j++)
	    for (int k = 0; k < N; k++)
		    for (int i = 0; i < N; i++)
			    c[i][j][k] = a[i][j][k] + b[i][j][k];

    clock_t end4 = clock();
    auto dur4 = end4 - start4;
    cout << dur4 << endl;

}

void test_kij()
{
    cout << "kij: ";
    clock_t start5 = clock();
    for (int k = 0; k < N; k++)
	    for (int i = 0; i < N; i++)
		    for (int j = 0; j < N; j++)
			    c[i][j][k] = a[i][j][k] + b[i][j][k];
    clock_t end5 = clock();
    auto dur5 = end5 - start5;
    cout << dur5 << endl;
}

void test_kji()
{
    cout << "kji: ";
    clock_t start6 = clock();
    for (int k = 0; k < N; k++)
	    for (int j = 0; j < N; j++)
		    for (int i = 0; i < N; i++)
			    c[i][j][k] = a[i][j][k] + b[i][j][k];

    clock_t end6 = clock();
    auto dur6 = end6 - start6;
    cout << dur6 << endl;

}

int main()
{
    while (cin >> N)
    {
        cout << "N = " << N << endl;
        cout << "---test start---" << endl;

        test_ijk();
        test_ijk();

        test_ikj();
        test_ikj();

        test_jik();
        test_jik();

        test_jki();
        test_jki();

        test_kij();
        test_kij();

        test_kji();
        test_kji();

        cout << "---test over---" << endl;
    }
    return 0;
}