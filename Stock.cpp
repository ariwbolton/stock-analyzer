#include "Stock.h"
#include "Day.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>

Stock::Stock() {
	// no content
}

Stock::Stock(std::string inp) : name(inp) {
    data = new std::vector<Day>();
}

Stock::~Stock() {
    delete data;
}

void Stock::computeBB(int days, float vcoeff) {
    int i, j, operations = 0;
    float std, cSMA = 0, pSMA, money = 0, shares = 100, op = 1, cl = 1;
    std::vector<Day> & vec = *data;

    std::cout << "\nBollinger Bands for " << name << std::endl;
    std::cout << std::setw(10) << "Low" << std::setw(10) << "Close";
    std::cout << std::setw(10) << "Mid" << std::setw(10) << "High";
    std::cout << std::setw(10) << "StdDev" << std::endl;

    for(i = days - 1; i < vec.size() && vec.size() > days; i++) {
	if(i == days - 1) {
	    for(j = 0; j < days; j++) {
		cSMA += vec[j].close;
	    }

	    cSMA /= (float)days;
	    op = vec[i].close;
	} else {
	    pSMA = cSMA;
	    cSMA = (vec[i].close-vec[i-days].close)/days+(vec[i - 1].SMA);  
	}

	vec[i].SMA = cSMA;

	std = 0;

	for(j = i - days; j <= i; j++) {
	    std += pow((vec[j].close - cSMA), 2);
	}

	std /= days;
	std = pow(std, (double)0.5);
	
	vec[i].mSTD = std;

	vec[i].uBB = cSMA + (vcoeff * std);
	vec[i].lBB = cSMA - (vcoeff * std);

    std::cout << std::setw(10) << vec[i].lBB << std::setw(10) << vec[i].close;
    std::cout << std::setw(10) << vec[i].SMA << std::setw(10) << vec[i].uBB;
    std::cout << std::setw(10) << vec[i].mSTD;

	if(vec[i].uBB < vec[i].close) {
	    std::cout << "   <- Sell";
	
	    if(shares > 1) {
		money = shares * vec[i].close;
		shares = 0;
		operations++;
	    }
	    std::cout << " " << std::setw(10) << money;
	} else if(vec[i].lBB > vec[i].close) {
	    std::cout << "   <-  Buy";	

	    if(shares < 1) {
		shares = money / vec[i].close;
		money = 0;
		operations++;
	    }
	    std::cout << " " << std::setw(10) << shares * vec[i].close;
	}

	std::cout << std::endl;
	if(i == vec.size() - 1)
	    cl = vec[i].close;

    }

    if(shares < 1 && vec.size() > days)
	shares = money / vec[days - 1].close;

    std::cout << "This algorithm earned " << std::setprecision(4) << (shares - 100)
	      << "%\n";
    
    std::ostringstream n;
    n << "percent_BB_" << days << "_" << std::setprecision(2) << vcoeff << ".txt";
    std::ofstream out(n.str(), std::ios::app);
    float perc = 100 * (cl - op) / op;
    float inc = shares - 100;

    out << name << " " << std::setw(10) << inc << " " << std::setw(10) << perc 
	<< " " << std::setw(10) << inc - perc << " " << std::setw(10)
	<< operations << "\n";
    out.close();

}
