#ifndef __ROPE_H__
#define __ROPE_H__

#include "g_local.h"
#include "entity.h"
#include "sentient.h"
#include "scriptslave.h"

class Player;

class Rope : public ScriptSlave
   {
   private:
      Vector   rope_top;
      Vector   rope_bottom;
      float    rope_length;
      float    rope_last_grab_time;

      Player   *rider;
      float    rider_pos;
      float    rider_offset;

      Vector   angular_velocity;
      Vector   angular_displacement; 

      str      shaderName;

      Vector   CalculatePosition( float position );
      Vector   CalculateRiderPosition( Vector position );
      bool     CanMove( Vector start, Vector location );
      void     Move( Vector location );
      void     Update( Vector midpos );

      void     RopeThink( Event * ev );
      void     Touch( Event * ev );
      void     Setup( Event * ev );
      void     SetShader( str name );
      void     SetShader( Event * ev );
	   virtual void Archive(Archiver &arc);

   public:
	   CLASS_PROTOTYPE(Rope);
		   
	   Rope();

      void     Grab( Player *player, float offset );
	   void     Release( Player *player );
      bool     CanClimb( float distance );
      void     Climb( float distance );

   };

inline void Rope::Archive (Archiver &arc)
   {
   ScriptSlave::Archive( arc );

   arc.ArchiveVector( &rope_top );
   arc.ArchiveVector( &rope_bottom );
   arc.ArchiveFloat( &rope_length );
   arc.ArchiveFloat( &rope_last_grab_time );
   arc.ArchiveObjectPointer( ( Class ** )&rider );
   arc.ArchiveFloat( &rider_pos );
   arc.ArchiveFloat( &rider_offset );
   arc.ArchiveVector( &angular_velocity);
   arc.ArchiveVector( &angular_displacement );
   arc.ArchiveString( &shaderName );
   if ( arc.Loading() )
      {
      SetShader( shaderName );
      }
   }

// rope flags constants
#define ROPE_NONE			   0
#define ROPE_TBELOW			2
#define ROPE_ATTACHED		4
#define ROPE_ABELOW			8
#define ROPE_STRAIGHTEN		16
// rope spawnflags
#define ROPE_START_STILL	1
// rope piece spawnflags
#define PIECE_WIGGLE		   1
#define PIECE_ATTWIGGLE		2

class   RopePiece;
class   RopeBase;

typedef SafePtr<RopePiece> RopePiecePtr;
typedef SafePtr<RopeBase>  RopeBasePtr;

class RopePiece : public ScriptSlave
   {
   public:
	   RopeBasePtr       rope_base;
	   RopePiecePtr      prev_piece;
	   RopePiecePtr      next_piece;
	   int               piecenum;
	   int               rope;
	   int               wigglemove;
	   float             wiggletime;
	   float             wiggle_debounce_time;
	   EntityPtr         attachent;
      Animate           *attachmodel;
      str               target2;
	   Vector            moveorg;

	   CLASS_PROTOTYPE(RopePiece);
		   
	   RopePiece();
	   void Setup(Event *ev);
	   void Detach(void);
	   void PieceTriggered(Event *ev);
	   void Wiggle(void);
      void SetWiggleTime( Event *ev );
      void SetWiggleMove( Event *ev );
      void Target2( Event *ev );
      void AttachModelToRope( Event *ev );
      virtual void setOrigin( Vector org );
	   virtual void Archive(Archiver &arc);
   };

class RopeBase : public RopePiece
{
public:
	int		piecelength;      // distance between RopePieces
	str		piecemodel;       // model to use for the pieces
	int		pieceframe;       // frame to set the pieces to
	int		pieceskin;        // skin number to use for the pieces
	float	   ropedampener;     // movement dampener for free rope
	float	   dotlimit;         // dot product limit for amount of rope bending
	Vector	ropedir;          // direction to push a rope for limiting bend
	float	   strength;         // how strongly a stiff rope goes to position
   str      shaderName;

	CLASS_PROTOTYPE(RopeBase);
		
	RopeBase();
	void           Setup(Event *ev);
	void           Activate(Event *ev);
   void           SetStrength( Event *ev );
   void           SetPieceLength( Event *ev );
   void           SetRopeDampener( Event *ev );
   void           SetStiffness( Event *ev );
   void           SetShader( str name );
   void           SetShader( Event *ev );

	void           RestrictFreeRope(RopePiece *curr_piece);
	void           SetTouchVelocity(Vector fullvel, RopePiece *touched_piece, int set_z);
	void           FixAttachedRope(RopePiece *curr_base, RopePiece *curr_piece);
	void           RestrictGrabbedRope(RopePiece *fix_base, RopePiece *grabbed_piece);
	void           StraightenRope(RopePiece *fix_base, RopePiece *grabbed_piece);

	virtual void Archive(Archiver &arc);
};

inline void RopePiece::Archive (Archiver &arc)
   {
   ScriptSlave::Archive( arc );

	arc.ArchiveSafePointer( &rope_base );
	arc.ArchiveSafePointer( &prev_piece );
	arc.ArchiveSafePointer( &next_piece );
	arc.ArchiveInteger( &piecenum );
	arc.ArchiveInteger( &rope );
	arc.ArchiveInteger( &wigglemove );
	arc.ArchiveFloat( &wiggletime );
	arc.ArchiveFloat( &wiggle_debounce_time );
	arc.ArchiveSafePointer( &attachent );
	arc.ArchiveObjectPointer( ( Class ** )&attachmodel );
   arc.ArchiveString( &target2 );
	arc.ArchiveVector( &moveorg );
   }

inline void RopeBase::Archive (Archiver &arc)
   {
	RopePiece::Archive( arc );

	arc.ArchiveInteger(&piecelength);
	arc.ArchiveString(&piecemodel);
	arc.ArchiveInteger(&pieceframe);
	arc.ArchiveInteger(&pieceskin);
	arc.ArchiveFloat(&ropedampener);
	arc.ArchiveFloat(&dotlimit);
	arc.ArchiveVector(&ropedir);
	arc.ArchiveFloat(&strength);
   arc.ArchiveString(&shaderName);
   }

void G_Physics_Rope(RopePiece *ent);


#endif /* rope.h */
