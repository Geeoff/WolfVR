/*
=============================================================================

						 WL_SCALE DEFINITIONS

=============================================================================
*/
#pragma once
#include "WL_GLOBAL.H"


#define COMPSCALECODESTART	(65*4)		// offset to start of code in comp scaler

typedef struct
{
	unsigned	codeofs[65];
	unsigned	width[65];
	byte		code[];
}	t_compscale;

typedef struct
{
	unsigned	leftpix,rightpix;
	unsigned	dataofs[64];
// table data after dataofs[rightpix-leftpix+1]
}	t_compshape;


extern	t_compscale *scaledirectory[MAXSCALEHEIGHT+1];
extern	long			fullscalefarcall[MAXSCALEHEIGHT+1];

extern	byte		bitmasks1[8][8];
extern	byte		bitmasks2[8][8];
extern	unsigned	wordmasks[8][8];

extern	byte		mapmasks1[4][8];
extern	byte		mapmasks2[4][8];
extern	byte		mapmasks3[4][8];

extern	int			maxscale,maxscaleshl2;

extern	boolean	insetupscaling;

void SetupScaling (int maxscaleheight);
void ScaleShape (int xcenter, int shapenum, unsigned height);
void SimpleScaleShape (int xcenter, int shapenum, unsigned height);