#include <iostream>
#include <limits>
#define NOMINMAX
#include <windows.h>

#include "BitList.h"

using namespace std;

void printBitListError(BitListError, bool = true);

const uint8_t choiceCount = 5;
const char* cioces[choiceCount] = {
	"��������/��������� ��������",
	"�������� ��� ��������",
	"��������� ��� ��������",
	"���������� ��������� ���� ��������",
	"������ ���������� �������� ������",
};

int main() {
	setlocale(LC_ALL, "Rus");

	for (;;) {
		int32_t lampCount = 0;
		bool restart = false;
		bool showLimitedList = true;

		system("cls");
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
		system("cls");
		printf("������� �����: %u, ��� %u ���\n", lampList.getCellSize(), lampList.getBitSize());

		for (;;) {
			int32_t userChoice = 0;
			bool userInputError = false;

			if (showLimitedList) {
				printf("���:\n");
				cout << lampList << endl;
			}
			else
				showLimitedList = true;

			do {
				printf("\n");
				for (uint8_t i = 0; i < choiceCount; i++)
					cout << i + 1 << ") " << cioces[i] << endl;
				printf("��������: ");
				cin >> userChoice;
				if (cin.fail() || userChoice < 1 || userChoice > choiceCount) {
					userInputError = true;
					printf("������� ����� �� 1 �� %u!\n", choiceCount);
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				else
					userInputError = false;
			} while (userInputError);

			switch (userChoice) {
			case 1: {
				int32_t lampIndex = -1;
				int32_t newLampState = -1;

				do {
					printf("������� ����� ��������(1-%u) � ����� ��������(0 - ��������, 1 - ���������): ", lampList.getBitSize());
					cin >> lampIndex >> newLampState;
					if (cin.fail()) {
						userInputError = true;
						printf("������������ ���� �����\n");
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					/*else if (!lampList.isValidIndex(lampIndex - 1)) {
						userInputError = true;
						printf("�������� ����� �������� (��������� �� 1 �� %u)\n", lampList.getBitSize());
					}
					else if (!lampList.isValidBitValue(newLampState)) {
						userInputError = true;
						printf("�������� ��������� �������� (��������� 0 � 1)\n");
					}*/
					else
						userInputError = false;
				} while (userInputError);

				system("cls");
				try {
					lampList.set(lampIndex - 1, newLampState);
					printf("����� ��� ������� %d %s\n", lampIndex, lampList[lampIndex - 1] ? "��������" : "���������");
				}
				catch (BitListError e) {
					cout << "������: ";
					printBitListError(e);
				}
				break;
			}
			case 2: {
				lampList.setToAll(1);
				system("cls");
				printf("��� �������� ��������\n");
				break;
			}
			case 3: {
				lampList.setToAll(0);
				system("cls");
				printf("��� �������� ���������\n");
				break;
			}
			case 4: {
				system("cls");
				printf("������ ������ ��������� ����:\n");
				lampList.printFullBitList();
				showLimitedList = false;
				break;
			}
			case 5:{
				restart = true;
				break;
			}
			}
			if (restart)
				break;
		}
	}
	return 0;
}

void printBitListError(BitListError e, bool newLine) {
	switch (e) {
	case BitListError::ZeroSize:
		cout << "���������� ��� �� ����� ���� �������";
		break;
	case BitListError::NegativeSize:
		cout << "���������� ��� �� ����� ���� �������������";
		break;
	case BitListError::NegativeIndex:
		cout << "������ �� ����� ���� �������������";
		break;
	case BitListError::IndexOutOfRange:
		cout << "������������ ������";
		break;
	case BitListError::ErrorBitValue:
		cout << "������������ �������� ���� (���������: 0, 1)";
		break;
	}
	if (newLine)
		cout << endl;
}