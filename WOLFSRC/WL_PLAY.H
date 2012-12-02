/*
=============================================================================

						 WL_PLAY DEFINITIONS

=============================================================================
*/
#pragma once
#include "WL_GLOBAL.H"

#ifdef SPEAR
extern	long		funnyticount;		// FOR FUNNY BJ FACE
#endif

extern	exit_t		playstate;

extern	boolean		madenoise;

extern	objtype 	objlist[MAXACTORS],*newObj,*obj,*player,*lastobj,
					*objfreelist,*killerobj;
extern	statobj_t	statobjlist[MAXSTATS],*laststatobj;
extern	doorobj_t	doorobjlist[MAXDOORS],*lastdoorobj;

extern	unsigned	farmapylookup[MAPSIZE];
extern	byte		*nearmapylookup[MAPSIZE];

extern	byte		tilemap[MAPSIZE][MAPSIZE];	// wall values only
extern	byte		spotvis[MAPSIZE][MAPSIZE];
extern	objtype		*actorat[MAPSIZE][MAPSIZE];

#define UPDATESIZE			(UPDATEWIDE*UPDATEHIGH)
extern	byte		update[UPDATESIZE];

extern	boolean		singlestep,godmode,noclip;
extern	int			extravbls;

//
// control info
//
extern	boolean		mouseenabled,joystickenabled,joypadenabled,joystickprogressive;
extern	int			joystickport;
extern	int			dirscan[4];
extern	int			buttonscan[NUMBUTTONS];
extern	int			buttonmouse[4];
extern	int			buttonjoy[4];

extern	boolean		buttonheld[NUMBUTTONS];

extern	int			viewsize;

//
// curent user input
//
extern	int			controlx,controly;		// range from -100 to 100
extern	boolean		buttonstate[NUMBUTTONS];

extern	boolean		demorecord,demoplayback;
extern	char		*demoptr, *lastdemoptr;
extern	memptr		demobuffer;



void	InitRedShifts (void);
void 	FinishPaletteShifts (void);

void	CenterWindow(word w,word h);
void 	InitActorList (void);
void 	GetNewActor (void);
void 	RemoveObj (objtype *gone);
void 	PollControls (void);
void 	StopMusic(void);
void 	StartMusic(void);
void	PlayLoop (void);
void StartDamageFlash (int damage);
void StartBonusFlash (void);
