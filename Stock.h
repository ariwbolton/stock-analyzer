#ifndef STOCK_H
#define STOCK_H

#include <vector>
#include <string>
#include "Day.h"

class Stock {
    public:
	std::vector<Day>* data;

	std::string name;

	Stock();
	Stock(std::string inp);
	~Stock();
};


#endif

