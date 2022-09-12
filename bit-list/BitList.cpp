#include "BitList.h"

BitList::BitList(int32_t bitCount) {
	if (bitCount == 0)
		throw BitListError::ZeroSize;
	if (bitCount < 0)
		throw BitListError::NegativeSize;

	bitSize = bitCount;
	cellSize = _getCellSizeFromBitSize(bitCount);

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
	printf("[DEBUG] deleting %u bytes...\n", cellSize);
	delete[] cellList;
}

uint32_t BitList::_getCellSizeFromBitSize(uint32_t bitCount) {
	uint32_t cellSize_ = bitCount >> 3;
	if (bitCount % 8) cellSize_++; //?TODO change
	return cellSize_;
}

BitList& BitList::operator=(const BitList& other) {
	bitSize = other.bitSize;
	cellSize = other.cellSize;

	delete[] cellList;
	cellList = new uint8_t[cellSize]{};

	for (uint32_t i = 0; i < cellSize; i++)
		cellList[i] = other.cellList[i];
	return *this;
}

uint8_t BitList::operator[](const int32_t& bitIndex) const {
	if (bitIndex < 0)
		throw BitListError::NegativeIndex;
	if (bitIndex >= bitSize)
		throw BitListError::IndexOutOfRange;
	uint32_t cellNumber = getCellOfBit(bitIndex);
	uint32_t bitNumber = bitIndex % 8;
	
	uint8_t result = cellList[cellNumber] & (1 << bitNumber);
	return result == 0 ? 0 : 1;
}

std::ostream& operator<<(std::ostream& os, const BitList& obj) {
	for (uint32_t cellNumber = 0; cellNumber < obj.cellSize; cellNumber++) {
		uint8_t cellValue = obj.cellList[cellNumber];
		uint8_t shownBits = 0;
		while (cellValue > 0 || shownBits < 8) {
			if (cellNumber == obj.cellSize - 1 && shownBits >= obj.bitSize % 8 && obj.bitSize % 8 != 0)
				printf("- ");
			 else
				printf("%u ", cellValue % 2);
			cellValue /= 2;
			shownBits++;
		}
		printf("\n");
	}
	return os;
}

uint32_t BitList::getCellSize() const { return cellSize; }

uint32_t BitList::getBitSize() const { return bitSize; }

uint32_t BitList::getCellOfBit(int32_t bitIndex) const {
	if (bitIndex < 0)
		throw BitListError::NegativeIndex;
	if (bitIndex >= bitSize)
		throw BitListError::IndexOutOfRange;
	return bitIndex >> 3;
}

void BitList::set(int32_t bitIndex, int8_t value) {
	if (bitIndex < 0)
		throw BitListError::NegativeIndex;
	if (bitIndex >= bitSize)
		throw BitListError::IndexOutOfRange;
	if (value != 0 && value != 1)
		throw BitListError::ErrorBitValue;
	uint32_t cellNumber = getCellOfBit(bitIndex);
	uint32_t bitNumber = bitIndex % 8;
	if (value)
		cellList[cellNumber] = cellList[cellNumber] | (1 << bitNumber);
	else
		cellList[cellNumber] = cellList[cellNumber] & ~(1 << bitNumber);
}