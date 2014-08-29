#include "Stock.h"
#include "Day.h"
#include <iostream>

Stock::Stock() {
	// no content
}

Stock::Stock(std::string inp) : name(inp) {
    data = new std::vector<Day>();
}

Stock::~Stock() {
    delete data;
}	
