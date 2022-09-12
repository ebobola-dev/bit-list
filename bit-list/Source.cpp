#include <iostream>
#include <limits>

#include "BitList.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	for (;;) {

		int32_t lampCount = 0;
		while (lampCount < 1) {
			cout << "\n������� ����������� ����: ";
			cin >> lampCount;
			if (cin.fail() || lampCount < 1) {
				cout << "������������ ����, ���������� ����� ������� ����" << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

		printf("����� ����: %d\n\n", lampCount);

		BitList bitList(lampCount);
	}
	return 0;
}
