#include "leetcode/inc.h"
//算法导论中矩阵链式乘法的最小值
void matrixChainOrder(vector<int> &p, vector<vector<int> >&m, vector<vector<int> >& s)
{
    //cout << "wtf?"<<endl;
    int n = p.size()-1;
    //std::cout << "n:"<<n << '\n';
    for (int i =0; i < n; i++)
    {
        //cout << "i"<<" ";
        m[i][i] = 0;
    }
    //cout <<"lala"<<endl;
    for (int l = 2; l < n ;l++)//长度位2到n-1
    {
        for (int i = 1; i < n - l + 1; i++)//i从1开始
        {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }

    }
}
void printOptimalParens(vector<vector<int> > &s, int i, int j)
{
    if (i == j)
    {
        cout << "A"<<i;
    }
    else
    {
        cout << "(";
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j]+1, j);
        cout << ")";
    }
}
int main()
{
    vector<int> p = {30,35,35,15,15,5,5,10,10,20,20,25};
    vector<vector<int> > m(p.size()-1, vector<int>(p.size()-1, 0));
    vector<vector<int> > s = m;
    matrixChainOrder(p, m, s);
    for (int i = 0; i < s.size(); i++)
    {
        for (int j = 0; j < s[0].size(); j++)
        {
            cout << s[i][j] << " ";
        }
        cout <<endl;
    }
    cout << endl;
    printOptimalParens(s, 0, 6);
    return 0;
}
