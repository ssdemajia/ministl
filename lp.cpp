#include <vector>
#include <iostream>
#include <cfloat>
using namespace std;

using vv = vector<vector<double> >;
void display(vv &v)
{
    for(size_t i = 0; i < v.size(); i++)
    {
        for(size_t j = 0; j < v[i].size(); j++)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}
vv create(int m, int n)//生成单纯形表
{
    vv v;
    for (size_t i = 0; i < m; i++)
    {
        vector<double> temp;
        for (size_t j = 0; j < n; j++)
        {
            double num;
            cin >> num;
            temp.push_back(num);
        }
        v.push_back(temp);
    }
    return v;
}
vector<double> createValues(int n)
{
    vector<double> values;
    for(size_t i = 0; i < n; i++)
    {
        double temp = 0;
        cin >> temp;
        values.push_back(temp);
    }
    return values;
}
vector<double> calCheckNum(vv &v, vector<double> &values, vector<int> &base)
{
    vector<double> checkNum;
    for(size_t i = 0; i < v[0].size()-1; i++)
    {
         double temp = 0;
         for (size_t j = 0; j < v.size(); j++)//计算zj
         {
            temp+=v[i][j] * values[base[j]];
         }
         checkNum.push_back(values[i] - temp);
    }
    return checkNum;
}
bool isAnswer(vector<double> &checkNum)
{
    for(size_t i = 0; i < checkNum.size(); i++)
    {
        if (checkNum[i] > 0)
        {
            return false;
        }
    }
    return true;
}
vector<double> createAnswer(vv &v, vector<int> &base)
{
    vector<double> result(v[0].size()-1, 0);
    for (size_t i = 0; i < base.size(); i++)
    {
        double temp = 0;
        int index = base[i];
        double b = 0;
        for (size_t i = 0; i < v.size(); i++)
        {
            if (v[i][index] == 1){
                b = v[i][v[0].size()-1];
            }
        }
        result[index] = b;
    }
    return result;
}
int calTheta(vv &v, vector<int> &base, int maxCheckNumIndex)
{
    vector<double> theta;
    int minIndex = 0;
    double min = FLT_MAX;
    for(size_t i = 0; i < base.size(); i++)
    {
        double temp = v[i][v[0].size()-1]/v[i][maxCheckNumIndex];
        if (temp < min)
        {
            minIndex = base[i];
            min = temp;
        }
    }
    return minIndex;

}
vector<double> calculate(vv &v, vector<double> &values, vector<int> &base)
{
    int m = v.size();
    int n = v[0].size();
    while (true)
    {
        vector<double> checkNum = calCheckNum(v, values, base);//检验数
        if (isAnswer(checkNum))
        {
            return createAnswer(v, base);
        }
        int maxCheckNumIndex = 0;//检验数最大的变量索引
        double max = 0;
        for (size_t i = 0; i < checkNum.size(); i++)
        {
            if (checkNum[i] > max)
            {
                max = checkNum[i];
                maxCheckNumIndex = i;
            }
        }
    }
}

int main()
{
    int m = 0, n = 0;
    cout << "输入m，n\n";
    cin >> m >> n;
    cout << "输入初始矩阵:\n";
    
    vv v = create(m, n);
      cout << "输入价值系数:\n";
    vector<int> values = createValues(n);
    display(v);
} 