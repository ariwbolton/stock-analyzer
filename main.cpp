// Author: Ari Bolton (8/28/14)

#include <iostream>
#include <fstream>
#include <string>
#include "Stock.h"

using namespace std;

int main() {
	float cl, hi, lo, op;
	int vo, dummy, i;
	char d = 'b';
	char dm[15];
	string str;
	ifstream in("../rawtxtfiles/data_8_28_14/MSFT.txt");

	Stock MSFT(string("MSFT"));
	vector<Day> & vec = *MSFT.data;

	for(i = 0; i < 7; i++)
	   getline(in, str); 

	d = in.peek();
	cout << d << endl;
	while(d != EOF)
	{
		if(d == 'a') { // must remove timestamp

		    in.getline(dm, 100, ',');

		    in >> cl >> d >> hi >> d >> lo >> d
		       >> op >> d >> vo >> d >> dummy >> '\n';
		} else if((int)d > 47 && (int)d < 58) { // must remove number

		    in.getline(dm, 100, ',');

		    in >> cl >> d >> hi >> d >> lo >> d
		       >> op >> d >> vo >> d >> dummy;

		} else { // must remove line
		    in.getline(dm, 100);
		}

		MSFT.data->push_back(Day(cl, hi, lo, op, vo));

		d = in.peek();
		if(d == '\n')
		{
		    in.get(d);
		    d = in.peek();
		}
	}

#if 1
	for(i = 0; i < vec.size() ; i++)
	    cout << vec[i].close << " " << vec[i].high << " " << vec[i].low
		 << " " << vec[i].open << " " << vec[i].vol << endl;
#endif


	return 0;
}
