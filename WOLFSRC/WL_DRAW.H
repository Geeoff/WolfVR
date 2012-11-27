/*
=============================================================================

						 WL_DRAW DEFINITIONS

=============================================================================
*/
#pragma once
#include "WL_GLOBAL.H"

extern	unsigned screenloc[3];
extern	unsigned freelatch;

extern	long 	lasttimecount;
extern	long 	frameon;
extern	boolean	fizzlein;

extern	unsigned	wallheight[MAXVIEWWIDTH];

extern	fixed	tileglobal;
extern	fixed	focallength;
extern	fixed	mindist;

//
// math tables
//
extern	int			pixelangle[MAXVIEWWIDTH];
extern	long		finetangent[FINEANGLES/4];
extern	fixed 		sintable[],*costable;

//
// derived constants
//
extern	fixed 	scale;
extern	long	heightnumerator,mindist;

//
// refresh variables
//
extern	fixed	viewx,viewy;			// the focal point
extern	int		viewangle;
extern	fixed	viewsin,viewcos;

extern	long		postsource;
extern	unsigned	postx;
extern	unsigned	postwidth;


extern	int		horizwall[],vertwall[];

extern	unsigned	pwallpos;


fixed	FixedByFrac (fixed a, fixed b);
void	TransformActor (objtype *ob);
void	BuildTables (void);
void	ClearScreen (void);
int		CalcRotate (objtype *ob);
void	DrawScaleds (void);
void	CalcTics (void);
void	FixOfs (void);
void	ThreeDRefresh (void);
void  FarScalePost (void);