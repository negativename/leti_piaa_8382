#include <iostream>
#include <vector>
#include <map>
#include <utility>

typedef long int Uint;
//typedef char Uint;
typedef long double Udouble;

using namespace std;

int heuristicFunction(Uint cur, Uint end){      
    return abs(cur - end);
}

int minPathfunc(vector <pair <Uint, Udouble> >& Vpaths, Uint end){      
    pair <Uint, Udouble> min = Vpaths[0];
    int index = 0;
    for (int i = 1; i < Vpaths.size(); i++){
        if (Vpaths[i].second + heuristicFunction(Vpaths[i].first, end) < min.second + heuristicFunction(min.first, end)){
            min = Vpaths[i];
            index = i;
        }
    }
    return index;
}

int getN(vector <pair <Uint, Udouble> >& Vpaths, Uint neighbor) {      
    for (int i = 0; i < Vpaths.size(); i++) {
        if (Vpaths[i].first == neighbor)
            return i;
    }
    return Vpaths.size()-1;
}

void delP(vector <pair <Uint, Udouble> > &Vpaths, pair <Uint, Udouble> cur) {
    for (int i = 0; i < Vpaths.size(); i++) {
        if (Vpaths[i].first == cur.first) {
            for (i; i < Vpaths.size() - 1; i++) {
                Vpaths[i] = Vpaths[i + 1];
            }
            Vpaths.pop_back();
            return;
        }
    }
}

int neighborfunc(Uint neighbor, vector <pair <Uint, Udouble> >& Vpaths){
    for (int i = 0; i < Vpaths.size(); i++) {
        if (Vpaths[i].first == neighbor) {
            return 1;
        }
    }
    return 0;
}

void resFunc(vector <pair <Uint, Uint> >& Vpeeks, Uint begin, Uint end){

    vector <Uint> path;
    Uint tmp = end;
    while(tmp != begin){
        for (pair <Uint, Uint> curPath : Vpeeks){
            if (tmp == curPath.first){
                path.insert(path.begin(), tmp);
                tmp = curPath.second;
                break;
            }
        }
    }
    path.insert(path.begin(), tmp);
    for (Uint elem : path)
        cout << elem;
    cout << endl;
}

void path_from_S_to_P(vector <pair <Uint, Udouble> >& Vpaths){
    cout << "Пути из начальной вершины: ";
    for (pair <Uint, Udouble> pair : Vpaths){
        cout << "в (" << pair.first << ") за (" << pair.second << "), ";
    }
    cout << endl;
}

class Graph{
    map <Uint, vector<pair <Uint, Udouble> > > graph;

public:
    Graph(){
    }
    void algA(Uint begin, Uint end) {              
        string Upath;                         //Путь пользователя
        vector <pair <Uint, Udouble> > Vpaths;      //Вектор путей
        vector <pair <Uint, Uint> > Vpeeks;        //Вектор вершин
        Vpaths.push_back(pair <Uint, Udouble> (begin, 0));
        for (int i = 0; i <= graph.size(); i++) {
            cout << "---------- " << endl;
            pair <Uint, Udouble> cur = (Vpaths[minPathfunc(Vpaths, end)]);      
            cout << "Текущая вершина: " << cur.first << endl;
            if (cur.first == end) {                                         
                break;
            }
            Upath.push_back(cur.first);                                        

            for (pair <Uint, Udouble> neighbor : graph[cur.first]) {                         
                if (Upath.find(neighbor.first) == string::npos) {              
                    if(!neighborfunc(neighbor.first, Vpaths)) {       
                        Vpaths.push_back(pair <Uint, Udouble> (neighbor.first, cur.second + neighbor.second));  
                        Vpeeks.push_back(pair <Uint, Uint> (neighbor.first, cur.first));
                    }
                    else {                                                             
                        pair <Uint, Udouble> *neighborInVpaths = &(Vpaths[getN(Vpaths, neighbor.first)]); 
                        if (cur.second + neighbor.second < neighborInVpaths->second) {                             
                            for (int i = 0; i < Vpeeks.size(); i++) {                  
                                if (Vpeeks[i].first == neighbor.first)                 
                                    Vpeeks[i].second = cur.first;
                            }
                            neighborInVpaths->second = cur.second + neighbor.second;   
                        }                                                                  
                    }
                }
            }
            delP(Vpaths, cur);
            path_from_S_to_P(Vpaths);
            }
            resFunc(Vpeeks, begin, end);
        }
        void init(){
        Uint sp, ep;
        Udouble length;
        while(cin >> sp /*&& sp != '!'*/ &&  cin >> ep && cin >> length){
            if (length <= 0)
                break;
            graph[sp].push_back (pair <Uint, Udouble> (ep, length));
            cout << sp << " " << ep << " " << length << endl;
        }
    }

};

int main() {
    Uint sp, ep;
    cin >> sp >> ep;
    cout << sp << " " << ep << endl;
    Graph graph;
    graph.init();
    graph.algA(sp, ep);
    return 0;
}