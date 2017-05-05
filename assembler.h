#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <map>
#include <string>
#include <utility>

#include "common_types.h"

class Assembler
{
public:
	Assembler(string filename);
	
	const ram_t& mcode() const;
	
	bool good() const;
	operator bool() const;
	
private:
	map<string, byte> labels;
	ram_t _mcode;
	bool _fail;
	
	byte stringtomcode(string);
	pair<string, byte> parse_var(string line);
	void fail(string reason);
};

#endif // ASSEMBLER_H
