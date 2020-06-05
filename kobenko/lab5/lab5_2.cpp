#include <iostream>
#include <map>
#include <vector>
//#define d

struct Peak {
    std::map<char,int> next;                
    std::map<char,int> states;                  
    bool flag;                              
    int parentPeak;                             
    char parentPeakSymb;                        
    int Slink;                               
    std::vector<int> listPatterns;          
};

void split(std::string& , char , std::vector<int>& , std::vector<Peak>& , std::vector<std::string>& );
void output(std::string , std::vector<std::string>& , std::vector<int>& );
void AC_joker(std::string& , std::string& , std::vector<Peak>& , std::vector<std::string>& , std::vector<int>& , std::vector<int>& );
int getSufLink(int , std::vector<Peak>& );
int jump(int , char , std::vector<Peak>& );
void NewStr(std::string , std::vector<std::string>& , std::vector<Peak>& );


int main(){
    std::string inputStr, pattern;
    std::vector<Peak> peaks;           
    std::vector<std::string> patterns;      
    std::vector<int> res;                     
    std::vector<int> patternsIndex;
    Peak head;
    head.parentPeak = head.Slink = -1;
    head.flag = false;
    peaks.push_back(head);
    char joker;
    std::cin >> inputStr;
    std::cin >> pattern;
    std::cin >> joker;
    split(pattern, joker, patternsIndex, peaks, patterns);
    AC_joker(inputStr, pattern, peaks, patterns, patternsIndex, res);
    output(pattern, patterns, res);
    return 0;
}

void NewStr(std::string s, std::vector<std::string>& patterns, std::vector<Peak>& peaks){
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
            std::cout << "Добавляем новую вершину из " << count << " (" << symb <<") \n";
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
    peaks[count].listPatterns.push_back(patterns.size() - 1);               
}

int jump(int count, char symb, std::vector<Peak>& peaks){                                                   
    #ifdef d
    std::cout << "Текущий символ: " << symb << "\n";
    #endif
    if (peaks[count].states.find(symb) == peaks[count].states.end()){                                                                      
        if (peaks[count].next.find(symb) != peaks[count].next.end()){
            peaks[count].states[symb] = peaks[count].next[symb];
        }
        else{
            peaks[count].states[symb] = count==0 ? 0 : jump(getSufLink(count, peaks), symb, peaks);         
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

int getSufLink(int count, std::vector<Peak>& peaks){                                                   
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
            peaks[count].Slink = jump (getSufLink(peaks[count].parentPeak, peaks), peaks[count].parentPeakSymb, peaks);
        }
    }
    #ifdef d
    std::cout << "Получаем ссылку на состояние: " << peaks[count].Slink <<" \n";
    #endif
    return peaks[count].Slink;
}

void AC_joker(std::string& inputStr, std::string& pattern, std::vector<Peak>& peaks, std::vector<std::string>& patterns, std::vector<int>& patternsIndex, std::vector<int>& res){
    int state = 0;
    res.resize(inputStr.size());                                                          
    for(int i = 0; i < inputStr.size();i++){
        state = jump(state, inputStr[i], peaks);                                                 
        #ifdef d
        std::cout << "Состояние: " << state <<" \n";
        #endif
        for(size_t tmp = state; tmp != 0; tmp = getSufLink(tmp, peaks)){                                                                          
            if(peaks[tmp].flag){
                #ifdef d
                std::cout << "Шаблон найден "  << std::endl;
                #endif
                for(auto Li : peaks[tmp].listPatterns){                                                                 
                    int counter = i + 1 - patterns[Li].size()- patternsIndex[Li];
                    if(counter >=0 && counter <= inputStr.size() - pattern.size()){
                        #ifdef d
                        std::cout << "Совпадение на индексе: " << counter << std::endl;
                        #endif
                        res[counter]++;
                    }
                }
            }
        }
    }
}

void output(std::string pattern, std::vector<std::string>& patterns, std::vector<int>& res){
    #ifdef d
    std::cout << "Ответ:" << std::endl;
    #endif
    for(size_t i = 0; i < res.size(); i++){
            if(res[i] == patterns.size())
            std::cout << i + 1 << "\n";
    }
}

void split(std::string& pattern, char joker, std::vector<int>& patternsIndex, std::vector<Peak>& peaks, std::vector<std::string>& patterns){
    size_t currentPos, prevPos;
    for(size_t i = 0; i < pattern.size() && currentPos != std::string::npos;){
        std::string str_buf;
        while(pattern[i] == joker) i++;                             
        prevPos = i;
        currentPos = pattern.find(joker, i);                        
        if(currentPos == std::string::npos)                         
            str_buf = pattern.substr(i, pattern.size() - i);
        else
            str_buf = pattern.substr( prevPos,currentPos - prevPos);
        if(!str_buf.empty()){
            patternsIndex.push_back(prevPos);                       
            NewStr(str_buf, patterns, peaks);
        }
        i = currentPos;
    }
}