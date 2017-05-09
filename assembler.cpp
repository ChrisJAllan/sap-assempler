#include "assembler.h"

#include <fstream>
#include <iostream>
#include <utility>

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
    {"INC", 0x91},
    {"SBI", 0xA0},
    {"DEC", 0xA1},
    {"OUT", 0xE0},
    {"HLT", 0xF0}
};

Assembler::Assembler(string filename)
    : _fail(false)
{
	vector<string> assembly;
	
	ifstream file(filename);
	
	size_t var_count = 0;
	
	_mcode.fill(stringtomcode("NOP"));
	
	if (file.fail()) {
		fail("File '" + filename + "' not found.");
	}
	
	// Load all assembly and labels
	while (!file.eof() && !file.fail()) {
		// Remove comments and whitespace
		string line;
		getline(file, line);
		
		line = line.substr(0, line.find("//"));
		boost::trim(line);
		
		if (line.empty()) {
			continue;
		}
		
		// Labels
		if (line.front() == '(' && line.back() == ')') {
			labels.insert(make_pair(line.substr(1, line.size() - 2), assembly.size()));
			continue;
		}
		if (line.back() == ':') {
			labels.insert(make_pair(line.substr(0, line.size() - 1), assembly.size()));
			continue;
		}
		
		// Variables
		if (line.front() == '$') {
			size_t var_pos = 16 - (++var_count);
			auto var = parse_var(line);
			
			labels.insert(make_pair(var.first, var_pos));
			_mcode[var_pos] = var.second;
			
			continue;
		}
		
		assembly.push_back(line);
	}
	
	if (assembly.size() + var_count > 16) {
		fail("Program too long: " + to_string(assembly.size()) + " bytes.");
	}
	
	for (size_t i = 0; i < assembly.size(); ++i) {
		_mcode[i] = stringtomcode(assembly[i]);
	}
}

auto Assembler::mcode() const -> const ram_t&
{ return _mcode; }

bool Assembler::good() const
{ return !_fail; }

Assembler::operator bool() const
{ return !_fail; }

byte Assembler::stringtomcode(string str)
{
	byte mcode, arg;
	boost::char_separator<char> func(" ");
	boost::tokenizer<boost::char_separator<char>> tok(str, func);
	auto next = tok.begin();
	
	// Raw data
	if (isdigit(next->front())) {
		mcode = static_cast<byte>(stoi(*next, 0, 0));
	}
	// Opcode
	else if (OPCODES.count(*next) == 0) {
		fail("Opcode " + *next + " not found.");
		return 0;
	}
	else {
		mcode = OPCODES.at(*next);
	}
	
	++next;
	
	// No arg
	if (next == tok.end()) {
		return mcode;
	}
	
	// Numeric arg
	if (isdigit(next->front())) {
		arg = 0x0F & static_cast<byte>(stoi(*next, 0, 0));
	}
	// Label or variable arg
	 else {
		if (labels.count(*next) == 0) {
			fail("Label " + *next + " not found.");
			return 0;
		}
		
		arg = 0x0F & labels.at(*next);
	}
	
	mcode |= arg;
	return mcode;
}

void Assembler::fail(string reason)
{
	_fail = true;
	cerr << reason << endl;
}

auto Assembler::parse_var(string line) -> pair<string, byte>
{
	boost::char_separator<char> func(" ");
	boost::tokenizer<boost::char_separator<char>> tok(line, func);
	string name;
	byte val = 0;
	
	auto next = tok.begin();
	
	name = next->substr(1, string::npos);
	
	if (++next != tok.end() && ++next != tok.end()) {
		if (!isdigit(next->front())) {
			fail("Invlid value for variable: " + *next);
			return make_pair("", 0);
		}
		val = static_cast<byte>(stoi(*next, 0, 0));
	}
	
	return make_pair(name, val);
}

