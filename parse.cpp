#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

class Stock {
    public:
	float algInc[35][10];
	float mktInc[35][10];
	float diff[35][10];

	string sym;
};

void outputStockData(Stock stock);

int main() {
    int i, k, m;
    float j;
    string line;
    Stock ** stocks = new Stock*[2907];
    Stock * avg = new Stock, * avg_per_op = new Stock;

    avg->sym = "AVG";
    avg_per_op->sym = "AVG_PER_OP";
    

    for(i = 0; i < 2907; i++)
	stocks[i] = new Stock();

    for(i = 5; i < 40; i++) {
	//cout << i << endl;
	for(j = 1.5; j < 2.5; j += 0.1) {
	    ostringstream inname;
	    float algInc, mktInc, diff;
	    int operations;

	    inname << "./thirdresults/percent_BB_" << i << "_"
		<< setprecision(2) << j << ".txt";

	    ifstream in(inname.str());

	    m = 0;
	    operations = 0;
	    avg->algInc[i - 5][(int)((j * 10) - 15)] = 0;
	    avg->mktInc[i - 5][(int)((j * 10) - 15)] = 0;
	    avg->diff[i - 5][(int)((j * 10) - 15)] = 0;

	    while(getline(in, line) && m <= 2906) {
		//cout << m << " here" << endl;
		istringstream l((line));
		int ops;
		Stock & current = *(stocks[ m++ ]);

		getline(l, current.sym, ' ');

		l >> algInc >> mktInc >> diff >> ops;

		current.algInc[i - 5][(int)((j * 10) - 15)] = algInc;
		current.mktInc[i - 5][(int)((j * 10) - 15)] = mktInc;
		current.diff[i - 5][(int)((j * 10) - 15)] = diff; 

	        avg->algInc[i - 5][(int)((j * 10) - 15)] += algInc;
	        avg->mktInc[i - 5][(int)((j * 10) - 15)] += mktInc;
	        avg->diff[i - 5][(int)((j * 10) - 15)] += diff;

		operations += ops;
	    }
	    //cout << "here2" << endl;
	    float totInc = avg->algInc[i - 5][(int)((j * 10) - 15)];

	    avg_per_op->algInc[i - 5][(int)((j * 10) - 15)] =  totInc / operations;
	    avg_per_op->mktInc[i - 5][(int)((j * 10) - 15)] = 0;
	    avg_per_op->diff[i - 5][(int)((j * 10) - 15)] = 0;

	    avg->algInc[i - 5][(int)((j * 10) - 15)] /= 2907;
	    avg->mktInc[i - 5][(int)((j * 10) - 15)] /= 2907;
	    avg->diff[i - 5][(int)((j * 10) - 15)] /= 2907;

	    in.close();
	} // inner for
    } // outer for

    for(i = 0; i < 2907; i++) {
	outputStockData(*(stocks[i]));
	delete stocks[i];
    }

    outputStockData(*avg);
    outputStockData(*avg_per_op);

    delete [] stocks;
    delete avg;
    delete avg_per_op;

    return 0;
} // main

void outputStockData(Stock stock) {
	ofstream out;
	ostringstream outname;
	int i;
	float j;

	outname << "./BBalgresults/" << stock.sym << ".txt";

	out.open((outname.str()));

	for(i = 0; i < 35; i++) {
	    for(j = 1.5; j < 2.5; j += 0.1) {
		out << setw(8) << setprecision(4)
		    << stock.algInc[i][(int)((j * 10) - 15)];
	    }
	    out << "\n";
	}

	out << "\n\n";

	for(i = 0; i < 35; i++) {
	    for(j = 1.5; j < 2.5; j += 0.1) {
		out << setw(8) << setprecision(4)
		    << stock.mktInc[i][(int)((j * 10) - 15)];
	    }
	    out << "\n";
	}

	out << "\n\n";

	for(i = 0; i < 35; i++) {
	    for(j = 1.5; j < 2.5; j += 0.1) {
		out << setw(8) << setprecision(4)
		    << stock.diff[i][(int)((j * 10) - 15)];
	    }
	    out << "\n";
	}

	out.close();
} // outputStockData
