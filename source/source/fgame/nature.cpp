#include "nature.h"

/*****************************************************************************/
/*QUAKED func_emitter (0 0.25 0.5) ?

"emitter" - Name of emitter to use.
******************************************************************************/
Event EV_Emitter_EmitterName
	( 
	"emitter",
	EV_DEFAULT,
   "s",
   "name",
   "Emitter to use"
	);

CLASS_DECLARATION( Entity, Emitter, "func_emitter" )
   {
      { &EV_Emitter_EmitterName,    EmitterName },
   };

Emitter::Emitter
   (
   )

   {
   edict->s.eType = ET_EMITTER;
   }

void Emitter::setEmitter
   (
   str name
   )

   {
   emitterName = name;
   edict->s.tag_num = gi.imageindex( emitterName );
   }

void Emitter::EmitterName
   (
   Event *ev
   )

   {
   setEmitter( ev->GetString( 1 ) );
   }

/*****************************************************************************/
/*QUAKED func_rain (0 0.25 0.5) ?

This creates a raining effect in the brush

"emitter" - Name of emitter to use for the rain.
******************************************************************************/

CLASS_DECLARATION( Entity, Rain, "func_rain" )
	{
      { NULL, NULL }
	};


Rain::Rain
   (
   )

   {
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   setSolidType( SOLID_NOT );
   edict->s.eType = ET_RAIN;
   setRainName( "defaultrain" );
   }

void Rain::setRainName
   (
   str name
   )

   {
   rainName = name;
   edict->s.tag_num = gi.imageindex( rainName );
   }


/*****************************************************************************/
/*       Plant Puffdaddy                                                     */
/*****************************************************************************/

Event EV_PuffDaddy_Idle
	( 
	"idle",
	EV_DEFAULT,
   NULL,
   NULL,
   "Animates the puff daddy."
	);

CLASS_DECLARATION( Animate, PuffDaddy, "plant_puffdaddy" )
	{
      { &EV_Touch,               Touch },
      { &EV_PuffDaddy_Idle,      Idle },
      { NULL, NULL }
	};

void PuffDaddy::Idle
   (
   Event *ev 
   )

   {
   RandomAnimate( "idle" );
   }

void PuffDaddy::Touch   
   (
   Event *ev
   )

   {
   Entity *other;

   other = ev->GetEntity( 1 );

   if ( !other->inheritsFrom( "Sentient" ) )
      return;

   RandomAnimate( "touch", EV_PuffDaddy_Idle );
   //SetFrame( 0 );
   
   SurfaceCommand( "puffdaddy", "+nodraw" );
   setSolidType( SOLID_NOT );
   }

PuffDaddy::PuffDaddy
   (
   )

   {
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
 	setSolidType( SOLID_TRIGGER );
   edict->s.eType = ET_MODELANIM;
   setModel( "plant_puffdaddy.tik" );
   PostEvent( EV_Show, 0 );
   //showModel();
   }
