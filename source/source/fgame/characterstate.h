//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/characterstate.h                   $
// $Revision:: 29                                                             $
//     $Date:: 7/25/00 11:32p                                                 $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/characterstate.h                        $
// 
// 29    7/25/00 11:32p Aldie
// Made some changes to the memory system and fixed a memory allocation bug in
// Z_TagMalloc.  Also changed a lot of classes to subclass from Class.
// 
// 28    7/21/00 1:14a Markd
// fixed fakeplayer again
// 
// 27    7/13/00 9:18p Markd
// added behind_nopitch camera type
// 
// 26    7/05/00 3:22p Markd
// Added movecontrol_gotcoolobject
// 
// 25    6/28/00 3:56p Markd
// added additional camera views
// 
// 24    6/28/00 3:12p Steven
// Added CacheStatemap.
// 
// 23    6/17/00 3:48p Aldie
// 
// 22    6/10/00 1:50p Steven
// Added statemap caching.
// 
// 21    6/08/00 9:55a Markd
// added camera_type behind_fixed
// 
// 20    6/04/00 6:52p Markd
// Added camera support to TouchAnim's cleaned up player camera interface
// 
// 19    4/29/00 11:28a Markd
// removed old rope code, cleaned up rope interface
// 
// 18    4/07/00 2:05p Markd
// added MOVETYPE_PIPEHANG
// 
// 17    3/31/00 3:18p Markd
// Added Movetype USEOBJECT
// 
// 16    2/25/00 7:27p Markd
// Added useanim_numloop support and fixed useanim_orientation
// 
// 15    2/24/00 4:16p Jimdose
// added MOVECONTROL_CROUCH
// 
// 14    2/24/00 3:25p Jimdose
// made parsing of cameratype and movetype to be table based
// added check for valid class when parsing behavior.
// 
// 13    2/22/00 1:56p Jimdose
// added MOVECONTROL_PUSH
// 
// 12    2/17/00 12:00p Aldie
// Added command processing to state system with the addition of entrycommands
// and exitcommands.
// 
// 11    2/14/00 5:37p Jimdose
// added MOVECONTROL_LEGS
// 
// 10    2/08/00 11:34a Steven
// Added picking up of Shgliek.
// 
// 9     2/08/00 12:17a Jimdose
// made rope grabbing controlled by state system
// 
// 8     1/28/00 6:21p Jimdose
// added rope movecontrol types
// 
// 7     1/22/00 4:05p Jimdose
// added MOVECONTROL_PIPECRAWL and  MOVECONTROL_STEPUP
// 
// 6     1/17/00 10:20p Jimdose
// Rewrote state system initialization.  Made conditionals defined with array.
// Made Evaluate functions early exit
// 
// 5     1/15/00 4:13p Markd
// Changed MOVETYPE_ABSOLUTE to have collision and no user input of the angles
// 
// 4     12/14/18 2:43p Jimdose
// added monkeybar movetype
// 
// 3     12/10/99 6:10p Jimdose
// added MOVECONTROL_WALLHUG
// 
// 2     9/20/99 6:58p Steven
// Cleanup
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 15    9/02/99 3:26p Steven
// Reset next times when changing states.
// 
// 14    8/31/99 5:48p Jimdose
// fixed bug with frame number conditions
// 
// 13    8/30/99 11:06a Steven
// Fixed a bug with the new timing stuff.
// 
// 12    8/28/99 5:23p Steven
// Added a wait time between each conditional check (defaults to 0).
// 
// 11    8/17/99 4:51p Jimdose
// got rid of default parameter on getParm
// added error checking to getParm
// 
// 10    8/16/99 10:31a Steven
// Added a time command to the state machine for AI use and moved
// ConditionalParameter back into Conditional.
// 
// 9     8/11/99 7:27p Jimdose
// added MOVECONTROL_HANGING
// 
// 8     8/10/99 4:23p Aldie
// Added parmlist to conditional parameters
// 
// 7     8/10/99 2:45p Steven
// Added parms to state checks and behavior commands from state machine.
// 
// 6     8/10/99 10:48a Jimdose
// added MOVECONTROL_ABSOLUTE
// 
// 5     8/06/99 6:53p Jimdose
// added ConditionalAnimationFrame
// 
// 4     8/05/99 9:16a Steven
// New AI stuff.
// 
// 3     7/06/99 8:33p Jimdose
// removed unused player code
// added state machine for player animation
// 
// 2     7/01/99 12:25a Jimdose
// debugged code
// 
// 1     6/30/99 7:25p Jimdose
// Created file
//
// DESCRIPTION:
// 

#ifndef __CHARACTERSTATE_H__
#define __CHARACTERSTATE_H__

#include "g_local.h"
#include "script.h"

enum testcondition_t
   {
   TC_ISTRUE,     // no prefix
   TC_ISFALSE,    // !
   TC_EDGETRUE,   // +
   TC_EDGEFALSE   // -
   };

enum movecontrol_t 
   {
   MOVECONTROL_USER,       // Quake style
   MOVECONTROL_LEGS,       // Quake style, legs state system active
   MOVECONTROL_ANIM,       // move based on animation, with full collision testing
   MOVECONTROL_ABSOLUTE,   // move based on animation, with full collision testing but no turning
   MOVECONTROL_HANGING,    // move based on animation, with full collision testing, hanging
   MOVECONTROL_WALLHUG,    // move based on animation, with full collision testing, hanging
   MOVECONTROL_MONKEYBARS, // move based on animation, with full collision testing, monkey bars
   MOVECONTROL_PIPECRAWL,  // move based on animation, with full collision testing, crawling on pipe
   MOVECONTROL_PIPEHANG,   // move based on animation, with full collision testing, hanging from pipe
   MOVECONTROL_STEPUP,
   MOVECONTROL_ROPE_GRAB,
   MOVECONTROL_ROPE_RELEASE,
   MOVECONTROL_ROPE_MOVE,
	MOVECONTROL_PICKUPENEMY,
   MOVECONTROL_PUSH,
   MOVECONTROL_CLIMBWALL,
   MOVECONTROL_USEANIM,
   MOVECONTROL_CROUCH,
   MOVECONTROL_LOOPUSEANIM,
   MOVECONTROL_USEOBJECT,
   MOVECONTROL_COOLOBJECT,
   MOVECONTROL_FAKEPLAYER
   };

enum cameratype_t 
   {
   CAMERA_TOPDOWN,
   CAMERA_BEHIND,
   CAMERA_FRONT,
   CAMERA_SIDE,
   CAMERA_BEHIND_FIXED,
   CAMERA_SIDE_LEFT,
   CAMERA_SIDE_RIGHT,
   CAMERA_BEHIND_NOPITCH
   };

#define DEFAULT_MOVETYPE   MOVECONTROL_LEGS
#define DEFAULT_CAMERA     CAMERA_BEHIND

class Conditional;

template< class Type >
struct Condition
	{
	const char     *name;
   qboolean       ( Type::*func )( Conditional &condition );
   };

class Conditional : public Class
   {
   private :
      qboolean                   result;
      qboolean                   previous_result;
      bool                       checked;

   public :
		Condition<Class>           condition;
		Container<str>					parmList;

      bool                       getResult( testcondition_t test, Entity &ent );
      const char                 *getName( void );

                                 Conditional( Condition<Class> &condition );
      
		const char						*getParm( int number );
      void                       addParm( str parm );
		int								numParms( void );
		void								clearCheck( void );
   };

inline void Conditional::addParm
   (
   str parm
   )

   {
   parmList.AddObject( parm );
   }

inline const char *Conditional::getParm
   (
   int number
   )

   {
   if ( ( number < 1 ) || ( number > parmList.NumObjects() ) )
      {
      gi.Error( ERR_DROP, "Parm #%d out of range on %s condition\n", number, condition.name );
      }
   return parmList.ObjectAt( number ).c_str();
   }

inline int Conditional::numParms
   (
   void
   )

   {
   return parmList.NumObjects();
   }

inline void Conditional::clearCheck
   (
   void
   )

   {
   checked = false;
   }

inline const char *Conditional::getName
   (
   void
   )

   {
   return condition.name;
   }

inline bool Conditional::getResult
   (
   testcondition_t test, 
   Entity &ent
   )

   {
   if ( condition.func && !checked )
      {
      checked = true;
		previous_result = result;

		result = ( ent.*condition.func )( *this );
      }

   switch( test )
      {
      case TC_ISFALSE :
         return !result;
         break;

      case TC_EDGETRUE :
         return result && !previous_result;
         break;

      case TC_EDGEFALSE :
         return !result && previous_result;
         break;

      case TC_ISTRUE :
      default :
         return result != qfalse;
      }
   }

class State;
class StateMap;

class Expression : public Class
   {
   private :
      struct condition_t
         {
         testcondition_t      test;
         int			         condition_index;
         };

      str                     value;
      Container<condition_t>  conditions;

   public :
                              Expression();
                              Expression( Expression &exp );
                              Expression( Script &script, State &state );

      void		               operator=( Expression &exp );

      bool                    getResult( State &state, Entity &ent, Container<Conditional *> *sent_conditionals );
      const char              *getValue( void );
   };

inline void Expression::operator=
	(
   Expression &exp
   )
   
   {
   int i;

   value = exp.value;

   conditions.FreeObjectList();
   for( i = 1; i <= exp.conditions.NumObjects(); i++ )
      {
      conditions.AddObject( exp.conditions.ObjectAt( i ) );
      }
   }

inline const char *Expression::getValue
   (
   void
   )

   {
   return value.c_str();
   }

class State : public Class
   {
   private :
      Container<int>					condition_indexes;

      StateMap                   &statemap;

      str                        name;

      str                        nextState;
      movecontrol_t              movetype;
      cameratype_t               cameratype;

		str								behaviorName;
		Container<str>					behaviorParmList;

		float								minTime;
		float								maxTime;

      Container<Expression>      legAnims;
      Container<Expression>      torsoAnims;

      Container<Expression>      states;
      Container<str>             entryCommands;
      Container<str>             exitCommands;

      void                       readNextState( Script &script );
      void                       readMoveType( Script &script );
      void                       readCamera( Script &script );
      void                       readLegs( Script &script );
      void                       readTorso( Script &script );
		void                       readBehavior( Script &script );
		void                       readTime( Script &script );
      void                       readStates( Script &script );
      void                       readCommands( Script &script, Container<str> &container );

      void                       ParseAndProcessCommand( str command, Entity *target );

   public :
                                 State( const char *name, Script &script, StateMap &map );

      State                      *Evaluate( Entity &ent, Container<Conditional *> *ent_conditionals );
      int								addCondition( const char *name, Script &script );
      void                       CheckStates( void );

      const char                 *getName( void );

      const char                 *getLegAnim( Entity &ent, Container<Conditional *> *sent_conditionals );
      const char                 *getTorsoAnim( Entity &ent, Container<Conditional *> *sent_conditionals );
		const char                 *getBehaviorName( void );
      State                      *getNextState( void );
      movecontrol_t              getMoveType( void );
      cameratype_t               getCameraType( void );
      qboolean                   setCameraType( str ctype );

		const char						*getBehaviorParm( int number=1 );
      void                       addBehaviorParm( str parm );
		int								numBehaviorParms( void );

		float								getMinTime( void );
		float								getMaxTime( void );
      void                       ProcessEntryCommands( Entity *target );
      void                       ProcessExitCommands( Entity *target );
      void                       GetLegAnims( Container<const char *> *c );
      void                       GetTorsoAnims( Container<const char *> *c );
   };

inline void State::addBehaviorParm
   (
   str parm
   )

   {
   behaviorParmList.AddObject( parm );
   }

inline const char *State::getBehaviorParm
   (
   int number
   )

   {
   return behaviorParmList.ObjectAt( number ).c_str();
   }

inline int State::numBehaviorParms
   (
   void
   )

   {
   return behaviorParmList.NumObjects();
   }

class StateMap : public Class
   {
   private :
      Container<State *>         stateList;
      Condition<Class>           *current_conditions;
      Container<Conditional *>   *current_conditionals;
		str								filename;
      
   public :
                                 StateMap( const char *filename, Condition<Class> *conditions, Container<Conditional *> *conditionals );
                                 ~StateMap();

      Condition<Class>           *getCondition( const char *name );
      int								findConditional( Conditional *condition );
      int	                     addConditional( Conditional *condition );
      Conditional                *getConditional( const char *name );
      void                       GetAllAnims( Container<const char *> *c );
      State                      *FindState( const char *name );
		const char						*Filename();
   };

inline const char *StateMap::Filename
   (
   void
   )

   {
   return filename.c_str();
   }

inline const char *State::getName
   (
   void
   )

   {
   return name.c_str();
   }

inline State *State::getNextState
   (
   void
   )

   {
   return statemap.FindState( nextState.c_str() );
   }

inline movecontrol_t State::getMoveType
   (
   void
   )

   {
   return movetype;
   }

inline cameratype_t State::getCameraType
   (
   void
   )

   {
   return cameratype;
   }

void ClearCachedStatemaps( void );
StateMap *GetStatemap( str filename, Condition<Class> *conditions,  Container<Conditional *> *conditionals, qboolean reload, qboolean cache_only = false );
void CacheStatemap( str filename, Condition<Class> *conditions	);

#endif /* !__CHARACTERSTATE_H__ */
