#pragma once
#include <iostream>

#include "Errors.h"

class BitList {
	uint8_t* cellList;
	uint32_t cellSize;
	uint32_t bitSize;

	uint32_t _getCellSizeFromBitSize(uint32_t);
	std::ostream& _printBitList(std::ostream& os, bool = false) const;

public:
	BitList(int32_t);
	BitList(const BitList&);
	~BitList();

	BitList& operator=(const BitList&);
	uint8_t operator[](const int32_t&) const;

	friend std::ostream& operator<<(std::ostream& os, const BitList& obj);

	uint32_t getCellSize() const;
	uint32_t getBitSize() const;
	uint32_t getCellOfBit(int32_t) const;

	void set(int32_t, int8_t);
	void setToAll(int8_t);
	void printFullBitList() const;
	bool isValidIndex(int32_t) const;
	bool isValidBitValue(int32_t) const;
};

