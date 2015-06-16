// Author: Ari Bolton

#include <iostream>
#include <fstream>
#include <string>

//enum {Today, Yesterday, PrevWeek, PrevMonth};

using namespace std;

int main(int argc, char ** argv) {

  string name(argv[1]);

  ifstream nums(name + "nums.txt"), names(name + "names.txt");
  ofstream output(name + "final.txt");
  string numline, nameline, dummy = "";
  int i, j, dumnum;

  getline(nums, numline);

  while(getline(names, nameline)) {

    output << nameline << "    ";

    for(i = 0; i < 4; i++) {
	getline(nums, numline);

	if(numline[0] == '>') {
	    output << 0 << "    ";
	    continue;
	}

	for(j = 0; j < numline.length() && isdigit(numline[j]); j++)
		dummy += numline[j];

	dumnum = stoi(dummy);

	j += 2;

	if(numline[j] == 'S' )
	    dumnum *= -1;

	output << dumnum << "    ";
	dummy = "";

    }

    output << endl;


  }


  return 0;

}
