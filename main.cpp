// Author: Ari Bolton (8/28/14)

#include <iostream>
#include <fstream>
#include <string>
#include "Stock.h"
#include <cctype>

using namespace std;

void runner(Stock & st);
void printVals(Stock & st);
void addStock(string & inp);

int main() {
	string inp;
	int num = 10;
	Stock MSFT(string("MSFT"));

	while(num > 0) {

	    	cout << "Choose an option" << endl
		     << "0. Exit" << endl
		     << "1. Track a new stock" << endl
		     << ">> ";

		cin >> num;
		cin.get();

		switch(num) {
		    	case 0:
				break;
			case 1:
				addStock(inp);
				break;
			default:
				break;
		}			

	}
	
	//runner(MSFT);
	//printVals(MSFT);

	return 0;
}

void runner(Stock & st) {


	float cl, hi, lo, op;
	int vo, dummy, i;
	char d = 'b';
	char dm[15];
	string str;
	ifstream in("../rawtxtfiles/data_8_28_14/MSFT.txt");

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

} // runner

void printVals(Stock & st) {

   	vector<Day> & vec = *st.data;

	for(int i = 0; i < vec.size() ; i++)
	    cout << vec[i].close << " " << vec[i].high << " " << vec[i].low
		 << " " << vec[i].open << " " << vec[i].vol << endl;
} // printVals


void addStock(string & inp) {
    	bool isValid = true;

	cout << "Enter a stock: ";
	getline(cin, inp);

	for(int i = 0; i < inp.length(); i++) {
		if(!isalpha(inp[i])) {
			isValid = false;
			cout << "Invalid characters inputted\n\n"; 
			return;
		}
	}

	for(int i = 0; i < inp.length(); i++)
	    inp[i] = toupper(inp[i]);

	if(isValid)
	    cout << inp << " added\n\n";
}
