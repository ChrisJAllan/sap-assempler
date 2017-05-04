This is an assembler for an SAP-1 computer with several added instructions.

The instruction set is:

	0x0 LDA    A = RAM[X]
	0x1 ADD    A += RAM[X]
	0x2 SUB    A -= RAM[X]
	0x3 STA    RAM[X] = A
	0x4 NOP
	0x5 JMP    goto X
	0x6 JGT    if (A > 0) goto X
	0x7 JZ     if (A == 0) goto X
	0x8 LDI    A = X
	0x9 ADI    A += X
	0xA SBI    A -= X
	0xE OUT
	0xF HLT

Features:
* Single-line comments
* Labels
* Raw data
* Data and arguments can be in decimal, hex, or octal

TODO:
* Variables
* File output 

Example input file:

	// int f = 15;
	// do { f -= 2; } while (f >= 0);
	(INIT)
		LDA (F_INIT) // f = F_INIT;
		STA 0xF
	(LOOP)
		LDA 0xF      // f -= 2;
		SBI 0x2
		STA 0xF
		OUT
		JGT (LOOP)   // if (f > 0) goto (LOOP)
		JZ  (LOOP)   // else if (f == 0) goto (LOOP)
		HLT          // else HALT
	(F_INIT)
		15
