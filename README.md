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
	    INC    A += 1 (Alias for ADI 1)
	0xA SBI    A -= X
	    DEC    A -= 1 (Alias for DEC 1)
	0xE OUT
	0xF HLT

Features:
* Single-line comments
* Labels
* Raw data
* Data and arguments can be in decimal, hex, or octal
* File output
* Variables

Example input file:

	// int i = 15;
	// do { i -= 2; } while (i >= 0);
	$I_INIT = 15
	$i
	INIT:
		LDA $I_INIT // i = I_INIT;
		STA $i
	LOOP:
		LDA $i      // i -= 2;
		SBI 0x2
		STA $i
		OUT
		JGT LOOP    // if (i > 0) goto LOOP
		JZ  LOOP    // else if (i == 0) goto LOOP
		HLT         // else HALT

