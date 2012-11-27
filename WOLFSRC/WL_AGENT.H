/*
=============================================================================

						 WL_AGENT DEFINITIONS

=============================================================================
*/
#pragma once
#include "WL_GLOBAL.H"

//
// player state info
//
extern	boolean		running;
extern	long		thrustspeed;
extern	unsigned	plux,pluy;		// player coordinates scaled to unsigned

extern	int			anglefrac;
extern	int			facecount;

void	SpawnPlayer (int tilex, int tiley, int dir);
void 	DrawFace (void);
void	DrawHealth (void);
void	TakeDamage (int points,objtype *attacker);
void	HealSelf (int points);
void	DrawLevel (void);
void	DrawLives (void);
void	GiveExtraMan (void);
void	DrawScore (void);
void	GivePoints (long points);
void	DrawWeapon (void);
void	DrawKeys (void);
void	GiveWeapon (int weapon);
void	DrawAmmo (void);
void	GiveAmmo (int ammo);
void	GiveKey (int key);
void	GetBonus (statobj_t *check);

void	Thrust (int angle, long speed);