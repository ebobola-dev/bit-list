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

		BitList lampList(lampCount);
		printf("������� �����: %u, ��� %u ���(�)\n", lampList.getCellSize(), lampList.getBitSize());
		printf("���:\n");
		cout << lampList << endl;

		for (int i = 0; i < 10; i++) {
			int index = 0;
			int value = 0;
			printf("������� ����� ���� � ����� ��������: ");
			cin >> index >> value;
			lampList.set(index, value);
			cout << lampList << endl;
			printf("������� ������: ");
			cin >> index;
			printf("�������� ���� �� ������� %d: %u\n", index, lampList[index]);
		}
	}
	return 0;
}
