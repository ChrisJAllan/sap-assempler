#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <map>
#include <string>

#include "common_types.h"

class Assembler
{
public:
	Assembler(string filename);
	
	const bytes& mcode() const;
	
	bool good() const;
	operator bool() const;
	
private:
	map<string, byte> labels;
	bytes _mcode;
	bool _fail;
	
	byte stringtomcode(string);
	void fail(string reason);
};

#endif // ASSEMBLER_H
