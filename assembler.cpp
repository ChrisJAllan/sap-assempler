#include "assembler.h"

#include <fstream>
#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

const map<string, byte> OPCODES = {
    {"LDA", 0x00},
    {"ADD", 0x10},
    {"SUB", 0x20},
    {"STA", 0x30},
    {"NOP", 0x40},
    {"JMP", 0x50},
    {"JGT", 0x60},
    {"JZ",  0x70},
    {"LDI", 0x80},
    {"ADI", 0x90},
    {"SBI", 0xA0},
    {"OUT", 0xE0},
    {"HLT", 0xF0}
};

Assembler::Assembler(string filename)
    : _fail(false)
{
	vector<string> assembly;
	
	ifstream file { filename };
	
	if (file.fail()) {
		fail("Problem loading file " + filename);
	}
	
	// Load all assembly and labels
	while (!file.eof()) {
		// Remove comments and whitespace
		string line;
		getline(file, line);
		
		line = line.substr(0, line.find("//"));
		boost::trim(line);
		
		if (line.empty()) {
			continue;
		}
		
		if (line.front() == '(' && line.back() == ')') {
			labels.insert(make_pair(line, assembly.size()));
			continue;
		}
		
		assembly.push_back(line);
	}
	
	for (string line : assembly) {
		_mcode.push_back(stringtomcode(line));
	}
}

auto Assembler::mcode() const -> const vector<byte>&
{ return _mcode; }

bool Assembler::good() const
{ return !_fail; }

Assembler::operator bool() const
{ return !_fail; }

byte Assembler::stringtomcode(string str)
{
	byte mcode, arg;
	boost::char_separator<char> func { " " };
	boost::tokenizer<boost::char_separator<char>> tok(str, func);
	auto next = tok.begin();
	
	if (OPCODES.count(*next) == 0) {
		fail("Opcode " + *next + " not found.");
		return 0;
	}
	
	mcode = OPCODES.at(*next);
	
	// No arg
	if (++next == tok.end()) {
		return mcode;
	}
	
	// Label arg
	if (next->front() == '(' && next->back() == ')') {
		arg = 0x0F & labels.at(*next);
	}
	// Numeric arg
	else {
		arg = 0x0F & stoi(*next, 0, 0);
	}
	
	mcode |= arg;
	return mcode;
}

void Assembler::fail(string reason)
{
	_fail = true;
	cerr << reason << endl;
}

