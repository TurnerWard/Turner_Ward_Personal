#ifndef PARTICLEDECAY_H
#define PARTICLEDECAY_H

// To save memory, the move commands are stores in PROGMEM.
// Each move command consists of two 16bit shorts (one for x, one for y)
// The highest bit (0x8000) of x indicates if the laser should be on
// and needs to be masked by the drawing code.

const unsigned short display_Path1[] PROGMEM = {
0x0, 0x0,
0x8064, 0x21, // The 0x8000 bit represents that the movement towards that position will have the laser on or off.
0x808c, 0x64,
0x80aa, 0xc8,
0x80c8, 0xf0,
0x812c, 0x12c,
0x8190, 0x172,
0x81f4, 0x1ea,
0x829e, 0x217,
0x8316, 0x2bc,
0x8378, 0x320,
0x83ae, 0x3e8
};

#endif
