#include <iostream>
#include <vector>
#include <map>
#include <utility>

typedef char Uchar;
typedef long double Udouble;

using namespace std;

int minPathfunc(vector <pair <Uchar, Udouble> >& Vpaths){      
    pair <Uchar, Udouble> min = Vpaths[0];
    int index = 0;
    for (int i = 1; i < Vpaths.size(); i++){
        if (Vpaths[i].second < min.second){
            min = Vpaths[i];
            index = i;
        }
    }
    return index;
}

void resFunc(vector <pair <Uchar, Uchar> >& Vpeeks, Uchar begin, Uchar end){

    vector <Uchar> path;
    Uchar tmp = end;
    while(tmp != begin){
        for (pair <Uchar, Uchar> curPath : Vpeeks){
            if (tmp == curPath.first){
                path.insert(path.begin(), tmp);
                tmp = curPath.second;
                break;
            }
        }
    }
    path.insert(path.begin(), tmp);
    for (Uchar elem : path)
        cout << elem;
    cout << endl;
}

void path_from_S_to_P(vector <pair <Uchar, Udouble> >& Vpaths){
    cout << "Пути из начальной вершины:";
    for (pair <Uchar, Udouble> pair : Vpaths){
        cout << "в (" << pair.first << ") за (" << pair.second << "), ";
    }
    cout << endl;
}

class Graph{
    map <Uchar, vector <pair <Uchar, Udouble>>> graph;
public:
    Graph(){
    }
    void algGr(Uchar begin, Uchar end) {            
        string Upath;                        
        vector <pair <Uchar, Udouble> > Vpath_f;       
        pair <Uchar, Udouble>  cur = pair <Uchar, Udouble> (begin, 0);     
        vector <pair <Uchar, Uchar> > Vpeeks;        
        int i = 0;

        while (true) {
            cout << "---------- " <<  endl;
            cout << "Текущая вершина: " << cur.first << endl;
            if (cur.first == end) {                         
                break;
            }
            Upath.push_back(cur.first);           
            vector <pair <Uchar, Udouble> > Vpaths;      
            for (pair <Uchar, Udouble> neighbor : graph[cur.first]) {                  
                if (Upath.find(neighbor.first) == string::npos) {     
                    Vpaths.push_back(neighbor);                            
                }
            }
            if (Vpaths.size() != 0) {      
                Vpath_f.push_back(cur);       
                pair <Uchar, Udouble> prevCur = cur;
                cur = Vpaths[minPathfunc(Vpaths)];  
                Vpeeks.push_back(pair <Uchar, Uchar> (cur.first, prevCur.first)); 
            }
            else {       
                cur = Vpath_f[Vpath_f.size() - 1];
                Vpath_f.pop_back();
                continue;
            }
            path_from_S_to_P(Vpaths);
            }
            resFunc(Vpeeks, begin, end);
        }
    void init(){
        Uchar sp, ep;
        Udouble length;
        while(cin >> sp && sp != '!' && cin >> ep && cin >> length){
            graph[sp].push_back (pair <Uchar, Udouble> (ep, length));
            cout << sp << " " << ep << " " << length << endl;
        }
    }
};

int main() {
    Uchar sp, ep;                     
    cin >> sp >> ep;
    cout << sp << " " << ep << endl;
    Graph graph;
    graph.init();
    graph.algGr(sp, ep);
    return 0;
}