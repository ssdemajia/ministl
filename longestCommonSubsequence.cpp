#include "leetcode/inc.h"
//算法导论中最长公共子序列
using vv = vector<vector<int> > ;
using vvs = vector<vector<string> >;
using v = std::vector<int>;
int lcs_length2(string &x, string &y)//用额外空间O(min(m,n))
{
    if (y.size() > x.size()) return lcs_length2(y,x);
    int m = x.size();
    int n = y.size();

    std::vector<int> c(n+1, 0);

    std::cout << "m:"<<m<<",n:"<<n << '\n';
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (x[i-1] == y[j-1])
            {
                c[j] = c[j-1]+1;
            }
            else if (c[j] < c[j-1])
            {
                c[j] = c[j-1];
            }
        }
    }
    return c[m-1];
}
// int lcs_length(string &x, string &y, vv &c, vvs &b)
// {
//     int m = x.size();
//     int n = y.size();
//     std::cout << "m:"<<m<<",n:"<<n << '\n';
//     for (int i = 0; i <= m; i++)
//     {
//         c[i][0] = 0;
//     }
//     for (int i = 0; i <= n; i++)
//     {
//         c[0][i] = 0;
//     }
//     for (int i = 1; i <= m; i++)
//     {
//         for (int j = 1; j <= n; j++)
//         {
//             if (x[i-1] == y[j-1])
//             {
//                 b[i][j] = "\u21d6";
//                 c[i][j] = c[i-1][j-1] + 1;
//             }
//             else if (c[i][j-1] > c[i-1][j])
//             {
//                 b[i][j] = "\u21e0";
//                 c[i][j] = c[i][j-1];
//             }
//             else
//             {
//                 b[i][j] = "\u21e1";
//                 c[i][j] = c[i-1][j];
//             }
//         }
//     }
//     return c[m][n];
// }
void printLCS(vvs &b, string &x, int i, int j)
{
    //cout << 1 << " ";
    if (i == 0 || j== 0) return;
    if (b[i][j] == "\u21d6")
    {
        printLCS(b, x, i-1, j-1);
        //std::cout << x[i-1] << " i,j:"<<i<<","<<j << '\n';
        cout << x[i-1] << " ";
    }
    else if (b[i][j] == "\u21e1")//
    {
        printLCS(b,x, i-1, j);
    }
    else
    {
        printLCS(b, x, i, j-1);
    }
}
int main(int argc, char const *argv[]) {
    string x = "ABCBDAB";
    string y = "BDCABA";

    //vv c(x.size()+1, std::vector<int>(y.size()+1, 0));
    //vvs b(x.size()+1, std::vector<string>(y.size()+1, "w"));
    //lcs_length(x,y,c,b);
    //displayVec2d(c);
    //displayVec2d(b);
    //printLCS(b, x, x.size(), y.size());
    cout << lcs_length2(x,y)<<endl;
    return 0;
}
