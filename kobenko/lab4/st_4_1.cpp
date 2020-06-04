#include <iostream>
#include <string>
#include <vector>

#define d

int main() {
	int i = 0, j = 0, res_counter = 0, isFound = 0, count = 1, counter = 0;
	std::string p, t;
	std::vector<int> pf, res;
	std::cin >> p; 
	std::cin >> t; 
	pf.resize(p.length());
	pf[0] = 0;
	#ifndef d
	std::cout << "Поиск ПФ" << std::endl;
	#endif
	while (count < (int)p.length()) {
		if (p[count] == p[counter]) {
			#ifndef d
			std::cout << "[" << count << "] и [" << counter << "] - это " << p[count] << ".Индексы увеличены на 1\n";
			#endif
			pf[count] = counter + 1;
			#ifndef d
			std::cout << "ПФ для " << p[count] << "[" << count << "] - " << pf[count] << ".\n";
			#endif
			count++;
			counter++;
		}
		else {
			#ifndef d
			std::cout << "[" << count << "], [" << counter << "] не совпали " << p[count] << ", " << p[counter] << ".\n";
			std::cout << "ПФ для " << p[count] << "-[" << count << "]" << " - 0.\n";
			#endif
			if (counter == 0) {
				pf[count] = 0;
				count++;
			}
			else {
				#ifndef d
				std::cout << "Индекс counter теперь равен значению ПФ " << pf[counter - 1] << ".\n";
				#endif
				counter = pf[counter - 1];
			}
		}
	}
	#ifndef d
	std::cout << "\nНачало алгоритма\n";
	#endif
	while (j != t.length()) {
		if (t[j] == p[i]) {
			#ifndef d
			std::cout << "В [" << i << "], [" << j << "] - " << t[j] << ".\n";
			#endif
			j++;
			i++;
			if (i == p.length()) {
				#ifndef d
				std::cout << "[" << i << "] - равен длине искомой строки " << i;
				#endif
				isFound = 1;
				res.push_back(j - p.length());
				res_counter++;
			}
			#ifndef d
			std::cout << "\nИндексы увеличены на 1: j = " << j << ", i = " << i << ".\n";
			#endif
		}
		else {
			#ifndef d
			std::cout << "[" << i << "], [" << j << "] не равны " << t[j] << ", " << p[i] << ".\n";
			#endif
			if (i == 0) {
				j++;
			}
			else {
				i = pf[i - 1];
			}
			#ifndef d
			std::cout << "Индексы: j = " << j << ", i = " << i << ".\n";
			#endif
		}
	}
	if (!isFound) {
		#ifndef d
		std::cout << "Совпадений не найдено!\n";
		#endif
	}
	if(res.empty()){
		std::cout << "-1";
		return 0;
	}
	for (int k = 0; k < res.size(); k++){
		if (k != 0)
			std::cout << "," << res[k];
		else std::cout << res[k];
	}
	std::cout << std::endl;
}


