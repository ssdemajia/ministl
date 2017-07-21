#include <vector>
#include <iostream>
#include <cfloat>
using namespace std;
//用于线性规划的程序，使用单纯形法
using vv = vector<vector<double> >;
void display2d(vv &v)//显示单纯形表
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
void display1d(vector<double> &v)//显示结果
{
    for(size_t i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
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
vector<double> createValues(int n)//创建价值系数
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
    //cout << "v size:" <<v[0].size() << endl;
    for(size_t i = 0; i < v[0].size()-1; i++)
    {
         double temp = 0;
         for (size_t j = 0; j < base.size(); j++)//计算zj
         {
            temp+=v[j][i] * values[base[j]];
         }
         checkNum.push_back(values[i] - temp);
    }
    //cout << "end calCheckNum" << endl;
    return checkNum;
}
bool isAnswer(vector<double> &checkNum)//通过检验数来判断是否是最优解
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
    int minI = 0;
    for(size_t i = 0; i < base.size(); i++)
    {
        double temp = v[i][v[0].size()-1]/v[i][maxCheckNumIndex];
        //cout<<"temp: "<<temp <<" index:" << base[i]<<endl;
        if (temp < min)
        {
            //minIndex = base[i];
            //minI = i;
            minIndex = i;
            min = temp;
        }
    }
    return minIndex;
}
void calNewBase(vv &v, int maxCheckNumIndex, int maxTheta)
{
    //cout << "maxTheta: "<< maxTheta << " maxCheckNum:" << maxCheckNumIndex
//<<endl;
    double divid = v[maxTheta][maxCheckNumIndex];//主元素的值要保存起来
    for (size_t i = 0; i < v[0].size(); i++)
    {
        v[maxTheta][i] /= divid;
    }
    //display2d(v);
    //cout << "mid calNewBase" << endl;
    for (size_t i = 0; i < v.size(); i++)
    {
        if (i == maxTheta) continue;
        double divie = v[i][maxCheckNumIndex];//其他行的主元素那一列的元素也需要保存起来
        //cout << "divie :" << divie<<endl;
        for (size_t j = 0; j < v[0].size(); j++)
        {
            v[i][j] -= v[maxTheta][j]*divie;
        }
    }
    //display2d(v);
}
vector<double> calculate(vv &v, vector<double> &values, vector<int> &base)
{
    int m = v.size();
    int n = v[0].size();
    int i = 0;
    while (true)
    {
        //display2d(v);
        cout << i++ << endl;
        vector<double> checkNum = calCheckNum(v, values, base);//检验数
        //cout << "checknumm--------------------------"<<endl;
        //display1d(checkNum);
        //std::cout << "after calCheckNum" << '\n';
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
        //pair<int,int> maxThetaAndIndex = calTheta(v, base, maxCheckNumIndex);
        int index = calTheta(v, base, maxCheckNumIndex);
        //std::cout << "after calTheta" << '\n';
        base[index] = maxCheckNumIndex;
        calNewBase(v, maxCheckNumIndex, index);
        //std::cout << "after calNewBase" << '\n';
        display2d(v);
    }
}

int main()
{
    // int m = 0, n = 0;
    // cout << "输入m，n\n";
    // cin >> m >> n;
    // cout << "输入初始矩阵:\n";
    //
    // vv v = create(m, n);
    //   cout << "输入价值系数:\n";
    //vector<double> values = createValues(n);
    vector<double> values{1,1,0,0,0};
    vector<vector<double> >v{
        {4,-1,1,0,0,8},
        {2,1,0,1,0,10},
        {-5,2,0,0,1,2}
                            };
    vector<int> base{2,3,4};
    vector<double> result = calculate(v, values, base);
    display1d(result);
}
