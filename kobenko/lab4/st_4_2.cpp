#include <iostream>
#include <string>
#include <vector>

#define d

void prFunc(std::string& p, std::vector<int>& pf) {
	pf.resize(p.length());
	pf[0] = 0;
	int  count = p.length() / 3, counter = 0, res;
	while (count < (int)p.length()) {
		if (p[count] == p[counter]) {
			#ifndef d
			std::cout << "[" << count << "] и [" << counter << "] - это " << p[count] << ".Индексы увеличены на 1\n";
			#endif
			pf[count] = counter + 1;
			#ifndef d
			std::cout << "ПФ для " << p[count] << "[" << count << "] - " << pf[count] << ".\n";
			#endif
			if (pf[count] == (p.length() / 3)) {
				#ifndef d
				std::cout << pf[count] << " - начало строки, дальше зацикливается с началом в:\n";
				#endif
				res = count - 2 * ((p.length()) / 3) + 1;
				std::cout << res << std::endl;
				return;
			}
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
	std::cout << "-1";
}



int main() {
	std::vector<int> pf;
	std::string p, t;
	std::cin >> p; 
	std::cin >> t; 
	if (p.length() != t.length()) {
		#ifndef d
		std::cout << "Длины строк разные\n";
		#endif
		std::cout << "-1";
		return 0;
	}
	#ifndef d
	std::cout << "Длины строк одинаковы.\n";
	#endif
	if (p == t) {
		#ifndef d
		std::cout << "Строки одинаковые\n";
		#endif
		std::cout << "0";
		return 0;
	}
	#ifndef d
	std::cout << "Создание строки, содержащеий 1-ую и две 2-ых строки\n";
	#endif
	t = t + p + p;
	#ifndef d
	std::cout << "Получилась строка: " << t << "\n";
	std::cout << "Поиск ПФ\n";
	#endif
	prFunc(t, pf);
	return 0;
}