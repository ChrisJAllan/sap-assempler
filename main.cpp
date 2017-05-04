/**
 * Assembler for a modified SAP-1 computer.
 */

#include <iomanip>
#include <iostream>
#include <string>

#include <boost/format.hpp>

#include "assembler.h"

using namespace std;

void print_use(string);
void print_data(const vector<byte>&);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		print_use(argv[0]);
		return -1;
	}
	
	string arg { argv[1] };
	
	Assembler a { arg };
	
	if (a.good()) {
		print_data(a.mcode());
	}
	
	return 0;
}

void print_use(string n)
{
	cout << "Usage: " << n << " <filename>" << endl;
}

void print_data(const vector<byte> &data)
{
	int i = 0;
	for (byte b : data) {
		cout << boost::format("0x%02x") % i << " " << boost::format("0x%02x") % (int) b << endl;
		i++;
	}
}

