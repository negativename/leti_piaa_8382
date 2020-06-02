#include <iostream>
#include <cmath> 
#include <stack> 

//#define DEBUG 

using namespace std;
// структура описывающая квадрат 
struct Square{ 
    int x; 
    int y; 
    int length; 
}; 

// функция возвращает наименьший делитель не равный нулю, если число непростое, иначе возвращает 1 
int mlt(int N){ 
    if(N%2 == 0) 
        return 2; 
    if(N%3 == 0) 
        return 3; 
    if(N%5 == 0) 
        return 5; 
    return 1; 
} 

// функция для вывода массива 
void out(int **arr,int N){ 
    for(int m = 0; m < N; m++){ 
        for(int l = 0; l < N; l++) 
            cout << arr[m][l]<< ' ';
        cout << endl; 
    } 
    cout << endl; 
} 

// функция инициализации квадрата в массиве в соответствии с параметрами х, у и length_square 
void fill_square(int **arr, int x, int y, int length_square){ 
    for(int i = 0; i < length_square; i++) 
        for(int j = 0; j < length_square; j++) 
            arr[x+i][y+j] = length_square; 
} 

// функция копировния стека 
void stack_copy(stack <Square> * sqrs, stack <Square> * sqrs_copy){ 
    while(!sqrs->empty()){ 
        sqrs_copy->push(sqrs->top()); 
        sqrs->pop(); 
    } 
} 
// функция нахождения пустой клетки в массиве arr. Переводит значения x и y в соответствии с ее координатами. 
// Возвращает 1, когда нет пустых клеток, и 0 в обратном. 
int empty_cell(int **arr, int &x, int &y, int N){ 
    for(x = 0; x < N; x++) 
        for(y = 0;y < N; y++) 
            if(arr[x][y]  ==  0) 
                return 0; 
    if(x == N) 
        return 1; 
    else 
        return 0; 
} 

// функция опустошения стека 
void empty_stack(stack <Square> *sqrs){ 
    while(!sqrs->empty()) 
        sqrs->pop(); 
} 

// функция нахождения максимальной длины квадрата, которого можно вписать в массив 
int max_length(int **arr, int &x, int &y, int N){ 
    int distance_to_the_border  =  (N-x > N-y) ? (N-y-!arr[0][0]) : (N - x - !arr[0][0]); 
    int length_square = 2; 
    for(; length_square <= distance_to_the_border; length_square++){ 
        for(int i = 0; i < length_square; i++){ 
            if(arr[x + length_square - 1][y + i] || arr[x + i][y + length_square - 1]) 
                return length_square - 1; 
        } 
    } 
    return length_square - 1; 
} 

// рекурсивная функция для перебора возможных значений расстановки квадратов 
int min_sqrs(int limit, stack <Square> *sqrs,int **arr, int N, int count_rec){ 
    if(limit < count_rec) 
        return -1; 
    #ifdef DEBUG 
    out(arr, N); 
    #endif 
    int x, y; 
    if(empty_cell(arr, x, y, N)){    
        cout << "Rec number is " << count_rec << endl;
        return 0;
    }
    stack <Square> sqrs_tmp; 
    stack <Square> sqrs_max; 
    int max = max_length(arr, x, y, N); 
    int length_square, k_min = limit + 1, k, need_length = 1; 
    for(length_square = 1; length_square <= max; length_square++){ 
        fill_square(arr, x, y, length_square); 
        k = min_sqrs(limit, &sqrs_tmp, arr, N, count_rec+1)+1; 
#ifdef DEBUG 
cout << "CURRENT K : " << k << ", K_MIN : " << k_min << endl; 
out(arr, N);
#endif 
        if(k < k_min && k != 0){ 
            k_min = k;
            need_length = length_square; 
            while(!sqrs_max.empty()){ 
                sqrs_max.pop(); 
            } 
        stack_copy(&sqrs_tmp, &sqrs_max); 
        } 
        else 
            empty_stack(&sqrs_tmp); 
        for(int i = 0; i < length_square; i++) 
            for(int j = 0; j < length_square; j++) 
                arr[x+i][y+j] = 0; 
        } 
    while(!sqrs->empty()) 
        sqrs->pop(); 
    stack_copy(&sqrs_max, sqrs); 
    sqrs->push({x, y, need_length});
    return k_min; 
}  

int main(){ 
    int N, min_k;
    cin  >>  N; 
    if(!(N>=2 && N<=40)){ // проверка на корректность данных 
        cout << "ERROR" << endl; 
        return 0; 
    } 
    stack <Square> sqrs; 
    int mul = mlt(N); 
    int limit = 6.37 * sqrt(sqrt((mul == 1) ? N : mul));
    int **arr; 
    if(mul!=1){ 
        arr = new int *[mul]; 
        for(int i = 0; i < mul;i++) 
            arr[i] = new int[mul](); 
        min_k = min_sqrs(limit, &sqrs, arr, mul, 0); 
    } 
    else { 
        arr = new int *[N];
        for(int i = 0; i < N; i++) 
            arr[i] = new int[N](); 
        int half = N - N/2;
        fill_square(arr, 0, 0, half); 
        fill_square(arr, half, 0, half - 1); 
        fill_square(arr, 0, half, half - 1); 
        min_k = min_sqrs(limit - 3, &sqrs, arr, N, 0) + 3;
        sqrs.push({half, 0, half - 1}); 
        sqrs.push({0, half, half - 1}); 
        sqrs.push({0, 0, half}); 
    } 
    cout << min_k << endl; 
    Square tmp; 
    int scale = (mul != 1) ? N/mul : 1;
    while(!sqrs.empty()){ 
        tmp  =  sqrs.top(); 
        cout << tmp.x * scale + 1 << " " << tmp.y*scale +1 << " " << tmp.length*scale << endl; 
        sqrs.pop(); 
    }    
    if(mul!=1) // отчистка массива 
        for(int i = 0; i < mul; i++) 
            delete [] arr[i]; 
    else 
        for(int i = 0; i < N; i++) 
            delete [] arr[i];
        delete [] arr; 
    return 0; 
} 