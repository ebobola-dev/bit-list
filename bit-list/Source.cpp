#include <iostream>
#include <limits>

#include "BitList.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	for (;;) {

		int32_t lampCount = 0;
		while (lampCount < 1) {
			cout << "\n¬ведите количетство ламп: ";
			cin >> lampCount;
			if (cin.fail() || lampCount < 1) {
				cout << "неккоректный ввод, необходимо число большее нул€" << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

		BitList lampList(lampCount);
		printf("—оздано €чеек: %u, дл€ %u бит(а)\n", lampList.getCellSize(), lampList.getBitSize());
		printf("¬ид:\n");
		cout << lampList << endl;

		for (int i = 0; i < 10; i++) {
			int index = 0;
			int value = 0;
			printf("¬ведите номер бита и новое значение: ");
			cin >> index >> value;
			lampList.set(index, value);
			cout << lampList << endl;
			printf("¬ведите индекс: ");
			cin >> index;
			printf("«начение бита по индексу %d: %u\n", index, lampList[index]);
		}
	}
	return 0;
}
