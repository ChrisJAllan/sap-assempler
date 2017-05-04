/**
 * Assembler for SAP 1.5
 */

#include <iomanip>
#include <iostream>
#include <string>

#include <boost/format.hpp>

#include "assembler.h"

using namespace std;

void print_use();

int main(int argc, char *argv[])
{
	if (argc < 2) {
		print_use();
		return -1;
	}
	
	string arg { argv[1] };
	
	Assembler a { arg };
	
	if (a.good()) {
		cout << hex << showbase;
		int i = 0;
		for (byte b : a.mcode()) {
			cout << boost::format("0x%02x") % i << " " << boost::format("0x%02x") % (int) b << endl;
			i++;
		}
	}
	
	
	return 0;
}

void print_use()
{
	
}

