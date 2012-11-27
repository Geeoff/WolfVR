/*
=============================================================================

						 WL_ACT1 DEFINITIONS

=============================================================================
*/
#pragma once
#include "WL_GLOBAL.H"


extern	doorobj_t	doorobjlist[MAXDOORS],*lastdoorobj;
extern	int			doornum;

extern	unsigned	doorposition[MAXDOORS],pwallstate;

extern	byte		areaconnect[NUMAREAS][NUMAREAS];

extern	boolean		areabyplayer[NUMAREAS];

extern unsigned	pwallstate;
extern unsigned	pwallpos;			// amount a pushable wall has been moved (0-63)
extern unsigned	pwallx,pwally;
extern int			pwalldir;


void InitDoorList (void);
void InitStaticList (void);
void SpawnStatic (int tilex, int tiley, int type);
void SpawnDoor (int tilex, int tiley, boolean vertical, int lock);
void MoveDoors (void);
void MovePWalls (void);
void OpenDoor (int door);
void PlaceItemType (int itemtype, int tilex, int tiley);
void PushWall (int checkx, int checky, int dir);
void OperateDoor (int door);
void InitAreas (void);