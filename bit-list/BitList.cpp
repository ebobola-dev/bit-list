#include "BitList.h"

BitList::BitList(int32_t bitCount) {
	if (bitCount == 0)
		throw BitListError::ZeroSize;
	if (bitCount < 0)
		throw BitListError::NegativeSize;

	bitSize = bitCount;
	cellSize = bitCount >> 3;
	if (bitCount % 8) cellSize++; //?TODO change

	cellList = new uint8_t[cellSize]{};
}

BitList::BitList(const BitList& other) {
	bitSize = other.bitSize;
	cellSize = other.cellSize;

	delete[] cellList;
	cellList = new uint8_t[cellSize] {};
	
	for (uint32_t i = 0; i < cellSize; i++)
		cellList[i] = other.cellList[i];
}

BitList::~BitList() {
	delete[] cellList;
}

uint8_t& BitList::operator[](const int32_t& index) {
	if (index < 0)
		throw BitListError::NegativeIndex;
	if (index >= bitSize)
		throw BitListError::IndexOutOfRange;
	return cellList[index]; //? TODO
}

std::ostream& operator<<(std::ostream& os, const BitList& obj) {
	for (uint32_t iCell = 0; iCell < obj.cellSize; iCell++)
		os << std::bitset<8>(obj.cellList[iCell]) << std::endl;
	return os;
}

uint32_t BitList::getCellSize() const { return cellSize; }

uint32_t BitList::getBitSize() const { return bitSize; }