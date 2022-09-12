#pragma once
#include <iostream>
#include <bitset>

#include "Errors.h"

class BitList {
	uint8_t* cellList;
	uint32_t cellSize;
	uint32_t bitSize;

public:
	BitList(int32_t);
	BitList(const BitList&);
	~BitList();

	uint8_t& operator[](const int32_t&);

	friend std::ostream& operator<<(std::ostream& os, const BitList& obj);

	uint32_t getCellSize() const;
	uint32_t getBitSize() const;
};

