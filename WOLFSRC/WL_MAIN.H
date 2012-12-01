/*
=============================================================================

						 WL_MAIN DEFINITIONS

=============================================================================
*/
#pragma once
#include "WL_GLOBAL.H"

extern	boolean		MS_CheckParm (char *string);

extern	char		str[80],str2[20];
extern	int			tedlevelnum;
extern	boolean		tedlevel;
extern	boolean		nospr;
extern	boolean		IsA386;

extern	byte 	*scalermemory;

extern	fixed		focallength;
extern	unsigned	viewangles;
extern	unsigned	screenofs;
extern	int		    viewwidth;
extern	int			viewheight;
extern	int			centerx;
extern	int			shootdelta;

extern	int			dirangle[9];

extern	boolean         startgame,loadedgame;
//boolean					virtualreality;
extern	int		mouseadjustment;
//
// math tables
//
extern	int			pixelangle[MAXVIEWWIDTH];
extern	long		finetangent[FINEANGLES/4];
extern	fixed 		sintable[],*costable;

//
// derived constants
//
extern	fixed 	scale,maxslope;
extern	long	heightnumerator;
extern	int		minheightdiv;

extern	char	configname[13];



void		HelpScreens (void);
void		OrderingInfo (void);
void		TEDDeath(void);
void		Quit (char *error);
void 		CalcProjection (long focal);
boolean		SetViewSize (unsigned width, unsigned height);
void		NewGame (int difficulty,int episode);
void 		NewViewSize (int width);
boolean 	LoadTheGame(int file,int x,int y);
boolean		SaveTheGame(int file,int x,int y);
void 		ShowViewSize (int width);
void		ShutdownId (void);

// Wolf VR functions:

void		InitWolf( );
void		ShutdownWolf( );

void		UpdateWolf( );
boolean		WolfIsDone( );
const char* GetWolfErrorString( );
