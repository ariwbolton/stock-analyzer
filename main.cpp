// Author: Ari Bolton (8/28/14)

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Stock.h"
#include <cctype>

#define NUM_STOCKS 2908

using namespace std;

void getData(Stock & st);
void printVals(Stock & st);
Stock* addStock(string & inp, string allSymbols[ NUM_STOCKS ], vector<Stock*> & tStocks);
void init(string syms[ NUM_STOCKS ]);
void runner(int & num, string & inp, string allSymbols[], vector<Stock*> & tStocks);
bool isTracked(string & inp, vector<Stock*> & tStocks);
Stock* getStock(string sym, vector<Stock*> & tStocks);
bool untrackStock(string sym, vector<Stock*> & tStocks);

int main() {
	string inp, allSymbols[ NUM_STOCKS ];
	vector<Stock*> tStocks;
	int num = 10, i, k;
	float j;
	string str("FB");
	init(allSymbols);

	while(num > 10) 
		runner(num, inp, allSymbols, tStocks);

	for(k = 0; k < NUM_STOCKS; k++) {
	    cerr << k << endl;
	    for(i = 5; i < 40; i++) {
		for(j = 1.5; j < 2.5; j += 0.1) {
		    addStock(allSymbols[ k ], allSymbols, tStocks)->computeBB(i,j);
		    untrackStock(allSymbols[ k ], tStocks);
		}
	    }
	}


	for(int i = 0; i < tStocks.size(); i++)
	    delete tStocks[i];

	return 0;
}

void getData(Stock & st) {

	float cl, hi, lo, op;
	int vo, dummy, i;
	char d = 'b';
	char dm[15];
	string str, nm = "../rawtxtfiles/data_8_28_14/" + st.name + ".txt";
	ifstream in(nm);

	vector<Day> & vec = *st.data;

	for(i = 0; i < 7; i++)
	   getline(in, str); 

	d = in.peek();
	while(d != EOF)
	{
		if(d == 'a') { // must remove timestamp

		    in.getline(dm, 100, ',');

		    in >> cl >> d >> hi >> d >> lo >> d
		       >> op >> d >> vo >> d >> dummy;
		} else if((int)d > 47 && (int)d < 58) { // must remove number

		    in.getline(dm, 100, ',');

		    in >> cl >> d >> hi >> d >> lo >> d
		       >> op >> d >> vo >> d >> dummy;

		} else { // must remove line
		    in.getline(dm, 100);
		}

		vec.push_back(Day(cl, hi, lo, op, vo));

		d = in.peek();
		if(d == '\n')
		{
		    in.get(d);
		    d = in.peek();
		}
	} // while
	in.close();

} // getData

void printVals(Stock & st) {

   	vector<Day> & vec = *st.data;

	for(int i = 0; i < vec.size() ; i++)
	    cout << vec[i].close << " " << vec[i].high << " " << vec[i].low
		 << " " << vec[i].open << " " << vec[i].vol << endl;
} // printVals


Stock* addStock(string & inp, string allSymbols[ NUM_STOCKS ], vector<Stock*> & tStocks) {
    	bool isValid = true;
	int i;
	Stock * st = NULL;
	
	/*
	cout << "Enter a stock: ";
	getline(cin, inp);
*/
	for(i = 0; i < inp.length(); i++) {
		if(!isalpha(inp[i])) {
			isValid = false;
			cout << "Invalid characters inputted\n\n"; 
			return st;
		}
	}

	for(i = 0; i < inp.length(); i++)
	    inp[i] = toupper(inp[i]);

	for(i = 0; i < NUM_STOCKS && allSymbols[i] != inp; i++);

	if(isValid && i < NUM_STOCKS) {
	    st = new Stock(inp);    
	    tStocks.push_back(st);
	    getData(*(tStocks[tStocks.size() - 1]));
	    cout << inp << " added\n\n";
	    return st;
	} else {
	    cout << inp << " not found\n\n";
	    return st;
	}

	return st;
}

void init(string syms[ NUM_STOCKS ]) {
	ifstream inp("nlisted.txt");
	string l;
	int i = 0;

	while(getline(inp, l))
	    syms[i++] = l;

	inp.close();
}

void runner(int & num, string & inp, string allSymbols[], vector<Stock*> & tStocks) {
	int i;

	cout << "Choose an option" << endl
	     << "0. Exit" << endl
	     << "1. Track a new stock" << endl
	     << "2. Print a stock's value for the last year" << endl
	     << "3. Compute Bollinger Bands" << endl
	     << ">> ";

	cin >> num;
	cin.get();

	switch(num) {
	    	case 0:
			break;
		case 1:
			addStock(inp, allSymbols, tStocks);
			break;
		case 2:
			cout << "\nEnter a stock: ";
			getline(cin, inp);

			if(isTracked(inp, tStocks)) {
			    cout << endl;
			    for(i = 0; tStocks[i]->name != inp; i++);
			    printVals(*(tStocks[i]));
			    cout << endl;
			} else {
			    cout << "Stock is untracked\n";
			}
			break;
		case 3:
			cout << "\nEnter a stock: ";
			getline(cin, inp);

			if(isTracked(inp, tStocks))
			    (getStock(inp, tStocks))->computeBB(20,2);
			else
			    cout << "Stock is untracked\n";
			break;
			    
		default:
			break;
	}			

} // runner

bool isTracked(string & inp, vector<Stock*> & tStocks) {
    int i;

    for(i = 0; i < inp.length(); i++)
	inp[i] = toupper(inp[i]);

    for(i = 0; i < tStocks.size() && tStocks[i]->name != inp; i++);

    if(i < tStocks.size()) {
	return true;
    } else {
	return false;
    }

} //isTracked

bool isValidSymbol(string inp) {

    return false;
} //isValidSymbol

Stock* getStock(string sym, vector<Stock*> & tStocks) {
    int i;

    for(i = 0; i < tStocks.size() && tStocks[i]->name != sym; i++);

    if(i == tStocks.size())
	return NULL;
    else
	return tStocks[i];

    return NULL;
}

bool untrackStock(string sym, vector<Stock*> & tStocks) {
    int i;

    for(i = 0; tStocks[i]->name != sym && i < tStocks.size(); i++);

    delete tStocks[i];

    tStocks.erase(tStocks.begin() + i);

    return true;
}
