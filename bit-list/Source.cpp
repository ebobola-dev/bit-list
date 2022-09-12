#include <iostream>
#include <limits>

#include "BitList.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	for (;;) {

		int32_t lampCount = 0;
		while (lampCount < 1) {
			cout << "\nВведите количетство ламп: ";
			cin >> lampCount;
			if (cin.fail() || lampCount < 1) {
				cout << "неккоректный ввод, необходимо число большее нуля" << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

		printf("Всего ламп: %d\n\n", lampCount);

		BitList bitList(lampCount);
	}
	return 0;
}
