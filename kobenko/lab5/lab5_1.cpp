#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

//#define d

struct Peak {
    std::map<char,int> next;                
    std::map<char,int> states;                  
    bool flag;                              
    int parentPeak;                             
    char parentPeakSymb;                        
    int Slink;                               
    int patternNumber;                      
};

void NewStr (const std::string& , std::vector<std::string>& , std::vector<Peak>& );
int jump(int , char , std::vector<Peak>& );
int getSufLink (int , std::vector<Peak>& );
void ahoCorasick(std::string& , std::vector<Peak>& , std::vector<std::pair<int,int>>& , std::vector<std::string>& );
void output(std::vector<std::pair<int,int>>& , std::vector<Peak>& , std::vector<std::string>& );
bool comp(std::pair<int, int>& , std::pair<int, int>& );


int main() {
    std::vector<Peak> peaks;           
    std::vector<std::string> patterns;      
    std::vector<std::pair<int,int>> res; 
    std::string inputStr, pattern;
    Peak head;
    head.parentPeak = head.Slink = -1;
    head.flag = false;
    peaks.push_back(head);
    int n = 0;
    std::cin >> inputStr;
    std::cin >> n;
    for(int i = 0; i < n ;i++){
        std::cin >> pattern;
        NewStr(pattern, patterns, peaks);
    }
    ahoCorasick(inputStr, peaks, res, patterns);
    output(res, peaks, patterns);

    return 0;
}

bool comp(std::pair<int, int>& a, std::pair<int, int>& b){
    if (a.second == b.second)
        return a.first < b.first;
    return a.second < b.second;
}

void NewStr (const std::string& s, std::vector<std::string>& patterns, std::vector<Peak>& peaks){
    #ifdef d
    std::cout << "Добавляем строку в контейнер: " << s << std::endl;
    #endif
    patterns.push_back(s);
    int count = 0;
    for (auto symb : s) {
        #ifdef d
        std::cout << "Символ: " << symb << " \n";
        #endif
        if (peaks[count].next.find(symb) == peaks[count].next.end()) {           
            #ifdef d
            std::cout << "Добавляем новую вершину из " << count << "(" << symb <<") \n";
            #endif
            Peak buf;
            buf.flag = false;
            buf.Slink = -1;
            buf.parentPeak = count;
            buf.parentPeakSymb = symb;
            peaks.push_back(buf);
            peaks[count].next[symb] = peaks.size() - 1;
        }
        count = peaks[count].next[symb];
    }
    peaks[count].flag = true;                                               
    peaks[count].patternNumber = patterns.size() - 1;                       
}

int jump (int count, char symb, std::vector<Peak>& peaks) {                                                   
    #ifdef d
    std::cout << "Текущий символ: " << symb << "\n";
    #endif
    if (peaks[count].states.find(symb) == peaks[count].states.end()){                                                                      
        if (peaks[count].next.find(symb) != peaks[count].next.end()){
            peaks[count].states[symb] = peaks[count].next[symb];
            }
        else{
            peaks[count].states[symb] = count==0 ? 0 : jump (getSufLink(count, peaks), symb, peaks);         
            #ifdef d
            std::cout << "Переходим по суфф. ссылке " << peaks[count].states[symb] <<" \n";
             #endif
        }
    }
    #ifdef d
    std::cout << "Следующее состояние: " << peaks[count].states[symb] <<" \n";
    #endif
    return peaks[count].states[symb];
}

int getSufLink (int count, std::vector<Peak>& peaks) {                                                   
    if (peaks[count].Slink == -1){
        if (count == 0 || peaks[count].parentPeak == 0){
            #ifdef d
            std::cout << "Добавляем суфф. ссылку на корень: " <<" \n";
            #endif
            peaks[count].Slink = 0;
        }
        else{
            #ifdef d
            std::cout << "Вычисляем суфф. ссылку через родительскую вершину: " <<" \n";
            #endif
            peaks[count].Slink = jump(getSufLink(peaks[count].parentPeak, peaks), peaks[count].parentPeakSymb, peaks);
        }
    }
    #ifdef d
    std::cout << "Получаем ссылку на состояние: " << peaks[count].Slink <<" \n";
    #endif
    return peaks[count].Slink;
}


void ahoCorasick(std::string& inputStr, std::vector<Peak>& peaks, std::vector<std::pair<int,int>>& res, std::vector<std::string>& patterns){
    int state = 0;
    for(int i = 0; i < inputStr.size();i++){
        state = jump(state, inputStr[i], peaks);                                                 
        #ifdef d
        std::cout << "Состояние: " << state <<" \n";
        #endif
        for(size_t tmp = state; tmp != 0; tmp = getSufLink(tmp, peaks)){                                                                          
            if(peaks[tmp].flag){
                std::pair<int,int> buf;                                         
                buf.first = peaks[tmp].patternNumber;                        
                buf.second = i - patterns[buf.first].size();                 
                res.push_back(buf);
                #ifdef d
                std::cout << "Найден шаблон №" << buf.second << ": " << patterns[buf.first] <<" \n";
                #endif
            }
        }
    }
}

void output(std::vector<std::pair<int,int>>& res, std::vector<Peak>& peaks, std::vector<std::string>& patterns){
    #ifdef d
    std::cout << "Ответ: " <<std::endl;
    #endif
    std::sort(res.begin(), res.end(), comp);
    for(auto iter : res){
        std::cout << iter.second + 2 << " " << iter.first + 1 << std::endl;
    }
    #ifdef d
    std::cout << "Количество вершин: " << peaks.size() << std::endl;
    for(size_t i = 0 ; i < res.size() - 1; i++) {
        for(size_t j = i + 1 ; j < res.size(); j++){
            size_t first, second;
            first = patterns[res[i].first].size() - 1 + res[i].second;
            second =  res[j].second;
            if(first >= second){
                std::cout << "Пересечение шаблонов: " << patterns[res[i].first] << " и " << patterns[res[j].first] << ". №" << res[i].first + 1<< ", №" << res[j].first + 1 << " на индексах " << res[i].second + 2 << "," << res[j].second + 2 << "\n";
            }
        }
    }
    #endif
}
