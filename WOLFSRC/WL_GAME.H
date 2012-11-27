/*
=============================================================================

						 WL_GAME DEFINITIONS

=============================================================================
*/
#pragma once
#include "WL_GLOBAL.H"


extern	boolean		ingame,fizzlein;
extern	unsigned	latchpics[NUMLATCHPICS];
extern	gametype	gamestate;
extern	int			doornum;

extern	char		demoname[13];

extern	long		spearx,speary;
extern	unsigned	spearangle;
extern	boolean		spearflag;


void 	DrawPlayBorder (void);
void 	ScanInfoPlane (void);
void	SetupGameLevel (void);
void 	NormalScreen (void);
void 	DrawPlayScreen (void);
void 	FizzleOut (void);
void 	GameLoop (void);
void ClearMemory (void);
void PlayDemo (int demonumber);
void RecordDemo (void);
void DrawAllPlayBorder (void);
void	DrawHighScores(void);
void DrawAllPlayBorderSides (void);


// JAB
#define	PlaySoundLocTile(s,tx,ty)	PlaySoundLocGlobal(s,(((long)(tx) << TILESHIFT) + (1L << (TILESHIFT - 1))),(((long)ty << TILESHIFT) + (1L << (TILESHIFT - 1))))
#define	PlaySoundLocActor(s,ob)		PlaySoundLocGlobal(s,(ob)->x,(ob)->y)
void	PlaySoundLocGlobal(word s,fixed gx,fixed gy);
void UpdateSoundLoc(void);