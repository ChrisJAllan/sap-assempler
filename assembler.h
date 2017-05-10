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
	
	byte stringtomcode(string, size_t ln);
	pair<string, byte> parse_var(string line, size_t ln);
	void fail(string reason, size_t ln);
};

#endif // ASSEMBLER_H
