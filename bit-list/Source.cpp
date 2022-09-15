#include <iostream>
#include <limits>
#define NOMINMAX
#include <windows.h>

#include "BitList.h"

using namespace std;

void printBitListError(BitListError, bool = true);

const uint8_t choiceCount = 5;
const char* cioces[choiceCount] = {
	"Включить/отключить лампочку",
	"Включить все лампочки",
	"Отключить все лампочки",
	"Посмотреть состояние всех лампочек",
	"Ввести количество лампочек заново",
};

int main() {
	setlocale(LC_ALL, "Rus");

	for (;;) {
		int32_t lampCount = 0;
		bool restart = false;
		bool showLimitedList = true;

		system("cls");
		while (lampCount < 1) {
			cout << "\nВведите количетство ламп: ";
			cin >> lampCount;
			if (cin.fail() || lampCount < 1) {
				cout << "неккоректный ввод, необходимо число большее нуля" << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

		BitList lampList(lampCount);
		system("cls");
		printf("Создано ячеек: %u, для %u бит\n", lampList.getCellSize(), lampList.getBitSize());

		for (;;) {
			int32_t userChoice = 0;
			bool userInputError = false;

			if (showLimitedList) {
				printf("Вид:\n");
				cout << lampList << endl;
			}
			else
				showLimitedList = true;

			do {
				printf("\n");
				for (uint8_t i = 0; i < choiceCount; i++)
					cout << i + 1 << ") " << cioces[i] << endl;
				printf("Выберите: ");
				cin >> userChoice;
				if (cin.fail() || userChoice < 1 || userChoice > choiceCount) {
					userInputError = true;
					printf("Введите число от 1 до %u!\n", choiceCount);
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
					printf("Введите номер лампочки(1-%u) и новое значение(0 - включить, 1 - выключить): ", lampList.getBitSize());
					cin >> lampIndex >> newLampState;
					if (cin.fail()) {
						userInputError = true;
						printf("Неккоректный ввод чисел\n");
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					/*else if (!lampList.isValidIndex(lampIndex - 1)) {
						userInputError = true;
						printf("Неверный номер лампочки (допустимо от 1 до %u)\n", lampList.getBitSize());
					}
					else if (!lampList.isValidBitValue(newLampState)) {
						userInputError = true;
						printf("Неверное состояние лампочки (допустимо 0 и 1)\n");
					}*/
					else
						userInputError = false;
				} while (userInputError);

				system("cls");
				try {
					lampList.set(lampIndex - 1, newLampState);
					printf("Лампа под номером %d %s\n", lampIndex, lampList[lampIndex - 1] ? "включена" : "выключена");
				}
				catch (BitListError e) {
					cout << "ОШИБКА: ";
					printBitListError(e);
				}
				break;
			}
			case 2: {
				lampList.setToAll(1);
				system("cls");
				printf("Все лампочки включены\n");
				break;
			}
			case 3: {
				lampList.setToAll(0);
				system("cls");
				printf("Все лампочки выключены\n");
				break;
			}
			case 4: {
				system("cls");
				printf("Полный список состояний ламп:\n");
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
		cout << "Количество бит не может быть нулевым";
		break;
	case BitListError::NegativeSize:
		cout << "Количество бит не может быть отрицательным";
		break;
	case BitListError::NegativeIndex:
		cout << "Индекс не может быть отрицательным";
		break;
	case BitListError::IndexOutOfRange:
		cout << "Недопустимый индекс";
		break;
	case BitListError::ErrorBitValue:
		cout << "Недопустимое значение бита (допустимо: 0, 1)";
		break;
	}
	if (newLine)
		cout << endl;
}