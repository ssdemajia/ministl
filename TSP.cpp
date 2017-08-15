#include "inc.h"
#include <deque>
//处理TSP问题
vector<vector<double>> cal(vector<int> &x, vector<int> &y) {
    vector<vector<double>> result;
    for (int i = 0; i < x.size(); i++) {
        vector<double> temp;
        for(int j = 0; j < x.size(); j++) {
            double t = sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
            temp.push_back(t);
        }
        result.push_back(temp);
    }
    return result;
}
struct Edge{
    Edge(int x, int y, int base, vector<vector<double>> &cost):
    _x(x),_y(y),_base(base)
    {//x为弧的起点， y为弧的终点
        _c = cost[base][x] + cost[base][y] - cost[x][y];
    }
    bool operator < (const Edge &b){//通过比较节约值，来排列弧
        if (_c < b._c) return true;
        return false;
    }
    int _base;//基点
    int _x;//起点
    int _y;//终点
    double _c;//节约值
};

//用于生成已排序的边节约值表，base是基点， cost是点到点的距离表
vector<Edge> createCastEdge(int base, vector<vector<double>> &cost){
    vector<Edge> result; 
    for (int i = 0; i < cost.size(); i++) {
        for(int j = i+1; j < cost[i].size(); j++){
            if (i==base||j==base) continue;//跳过基点
            result.push_back(Edge(i,j,base,cost));
        }
    }
    sort(result.begin(), result.end());
    return result;
}
bool Insert(deque<int> path, Edge &temp) {

}
deque<int> TSP(vector<Edge> &edge, vector<vector<double>> &cost) {
    int n = cost.size();
    vector<deque<int>> result;
    for(int i = 1; i < n; i++) {
        deque<int> temp = {i};
        result.push_back(temp);
    }

    while(result.size()!= 1) {
        Edge temp = edge[edge.size()-1];//取出最大的节约值
        edge.erase(edge.end()-1);//将这个节约值删除 
        for (int i = 0; i < result.size(); i++) {
            if (result[i].front() == temp._y) {
                for (int j = 0; j < result.size(); j++) {
                    if (i!=j) {
                        if (result[j].back() == temp._x) {
                            while(!result[i].empty()) {
                                result[j].push_back(result[i].front());
                                result[i].pop_front();
                            }
                            result.erase(result.begin()+i);    
                        }
                    }
                }
            }
            else if (result[i].back() == temp._y) {
                for (int j = 0; j < result.size(); j++) {
                    if (i!=j) {
                        if (result[j].front() == temp._x) {
                            while(!result[j].empty()) {
                                result[i].push_back(result[j].front());
                                result[j].pop_front();
                            }
                            result.erase(result.begin()+j);
                        }
                    }
                }
            }
        }
    }
    //result.push_front(0);
    return result[0];
}
ostream & operator<<(ostream & os, const Edge & e) {
    os<<"("<<e._x<<","<<e._y<<") c:"<<e._c << " ";
    return os;
}
int main() {
    vector<int> x = {0,5,8,7,10,15,16,18,18,20};
    vector<int> y = {0,20,12,4,15,4,18,8,15,17};
    vector<vector<double>> cost = cal(x,y);
    for (int i = 0; i < cost.size(); i++) {
        for(int j = 0; j < cost[i].size(); j++) {
           cout << left<<setw(12) << cost[i][j];//<< "    ";
        }
        cout << endl;
        cout << endl;
    }
    vector<Edge> edges = createCastEdge(0, cost);
    for (auto i : edges) {
        cout << i;
    }
    cout << endl;
    deque<int> result = TSP(edges, cost);
    for (auto i : result) {
        cout << i << " "<<endl;
    }
    return 0;
}