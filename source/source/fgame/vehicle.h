//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/vehicle.h                          $
// $Revision:: 4                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 6/14/00 2:17p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/vehicle.h                               $
// 
// 4     6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 3     5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 2     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 1     9/10/99 10:55a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// DESCRIPTION:
// Script controlled vehicles.
// 

#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include "g_local.h"
#include "entity.h"
#include "sentient.h"
#include "scriptslave.h"

extern Event EV_Vehicle_Enter;
extern Event EV_Vehicle_Exit;
extern Event EV_Vehicle_Drivable;
extern Event EV_Vehicle_UnDrivable;
extern Event EV_Vehicle_Lock;
extern Event EV_Vehicle_UnLock;
extern Event EV_Vehicle_SeatAnglesOffset;
extern Event EV_Vehicle_SeatOffset;
extern Event EV_Vehicle_DriverAnimation;
extern Event EV_Vehicle_SetWeapon;
extern Event EV_Vehicle_ShowWeapon;
extern Event EV_Vehicle_SetSpeed;
extern Event EV_Vehicle_SetTurnRate;

class VehicleBase : public ScriptModel
	{
	public:
		VehicleBase *vlink;
		Vector		 offset;

      CLASS_PROTOTYPE( VehicleBase );

		VehicleBase();
      virtual void Archive(	Archiver &arc );
	};

inline void VehicleBase::Archive
	(
	Archiver &arc
	)
   {
   ScriptModel::Archive( arc );

   arc.ArchiveObjectPointer( ( Class ** )&vlink );
   arc.ArchiveVector( &offset );
   }


/*QUAKED script_wheelsback (0 .5 .8) ?
*/
class BackWheels : public VehicleBase
	{
	public:
      CLASS_PROTOTYPE( BackWheels );
	};

/*QUAKED script_wheelsfront (0 .5 .8) ?
*/
class FrontWheels : public VehicleBase
	{
	public:
      CLASS_PROTOTYPE( FrontWheels );
	};


class Vehicle : public VehicleBase
	{
	protected:
		SentientPtr			driver;
		SentientPtr			lastdriver;
		float					maxturnrate;
		float					currentspeed;
		float					turnangle;
		float					turnimpulse;
		float					moveimpulse;
		float					jumpimpulse;
		float					speed;
      float             conesize;
      float             maxtracedist;
      str               weaponName;
      str               driveranim;
      Vector            last_origin;
      Vector            seatangles;
      Vector            seatoffset;
      Vector            driveroffset;
      Vector            Corners[4];

      qboolean          drivable;
      qboolean          locked;
      qboolean          hasweapon;
      qboolean          showweapon;
      qboolean          steerinplace;
      qboolean          jumpable;

      virtual void      WorldEffects( void );
      virtual void      CheckWater( void );
		virtual void		DriverUse( Event *ev );
		virtual void		VehicleStart( Event *ev );
		virtual void		VehicleTouched( Event *ev );
		virtual void		VehicleBlocked( Event *ev );
		virtual void		Postthink( void );
		virtual void		Drivable( Event *ev );
		virtual void		UnDrivable( Event *ev );
		virtual void		Jumpable( Event *ev );
		virtual void		SeatAnglesOffset( Event *ev );
		virtual void		SeatOffset( Event *ev );
      virtual void      SetDriverAngles( Vector angles );
		virtual void		Lock( Event *ev );
		virtual void		UnLock( Event *ev );
		virtual void		SetWeapon( Event *ev );
		virtual void		ShowWeaponEvent( Event *ev );
		virtual void		DriverAnimation( Event *ev );
		virtual void		SetSpeed( Event *ev );
		virtual void		SetTurnRate( Event *ev );
		virtual void		SteerInPlace( Event *ev );

	public:

      CLASS_PROTOTYPE( Vehicle );

								Vehicle();

		virtual qboolean	Drive( usercmd_t *ucmd );
		virtual qboolean	HasWeapon( void );
		virtual qboolean	ShowWeapon( void );
      Sentient				*Driver( void );
		virtual qboolean	IsDrivable( void );
      virtual void      Archive(	Archiver &arc );
	};

inline void Vehicle::Archive
	(
	Archiver &arc
	)
   {
   VehicleBase::Archive( arc );

   arc.ArchiveSafePointer( &driver );
   arc.ArchiveSafePointer( &lastdriver );
   arc.ArchiveFloat( &maxturnrate );
   arc.ArchiveFloat( &currentspeed );
   arc.ArchiveFloat( &turnangle );
   arc.ArchiveFloat( &turnimpulse );
   arc.ArchiveFloat( &moveimpulse );
   arc.ArchiveFloat( &jumpimpulse );
   arc.ArchiveFloat( &speed );
   arc.ArchiveFloat( &conesize );
   arc.ArchiveFloat( &maxtracedist );
   arc.ArchiveString( &weaponName );
   arc.ArchiveString( &driveranim );
   arc.ArchiveVector( &last_origin );
   arc.ArchiveVector( &seatangles );
   arc.ArchiveVector( &seatoffset );
   arc.ArchiveVector( &driveroffset );

   arc.ArchiveVector( &Corners[ 0 ] );
   arc.ArchiveVector( &Corners[ 1 ] );
   arc.ArchiveVector( &Corners[ 2 ] );
   arc.ArchiveVector( &Corners[ 3 ] );

   arc.ArchiveBoolean( &drivable );
   arc.ArchiveBoolean( &locked );
   arc.ArchiveBoolean( &hasweapon );
   arc.ArchiveBoolean( &showweapon );
   arc.ArchiveBoolean( &steerinplace );
   arc.ArchiveBoolean( &jumpable );
   }

class DrivableVehicle : public Vehicle
	{
	public:

      CLASS_PROTOTYPE( DrivableVehicle );

								DrivableVehicle();

		virtual void		Killed( Event *ev );
	};

typedef SafePtr<Vehicle> VehiclePtr;

#endif /* vehicle.h */
