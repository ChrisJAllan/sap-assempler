#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <array>
#include <map>
#include <string>

#include "common_types.h"

class Assembler
{
public:
	Assembler(string filename);
	
	const array<byte, 16>& mcode() const;
	
	bool good() const;
	operator bool() const;
	
private:
	map<string, byte> labels;
	array<byte, 16> _mcode;
	bool _fail;
	
	byte stringtomcode(string);
	void fail(string reason);
};

#endif // ASSEMBLER_H
