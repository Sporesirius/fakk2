//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/scriptvariable.h                   $
// $Revision:: 5                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 5/27/00 2:56p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/scriptvariable.h                        $
// 
// 5     5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 4     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 3     1/10/00 6:17p Jimdose
// more code cleanup
// 
// 2     1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 4     8/27/99 3:31p Markd
// put in "targetof" variable command
//
// DESCRIPTION:
// Dynamic variable list for scripts.
// 

#ifndef __SCRIPTVARIABLE_H__
#define __SCRIPTVARIABLE_H__

#include "g_local.h"
#include "container.h"
#include "listener.h"

extern Event EV_Var_Append;
extern Event EV_Var_AppendInt;
extern Event EV_Var_AppendFloat;
extern Event EV_Var_String;
extern Event EV_Var_TargetOf;
extern Event EV_Var_Equals;
extern Event EV_Var_PlusEquals;
extern Event EV_Var_MinusEquals;
extern Event EV_Var_TimesEquals;
extern Event EV_Var_DivideEquals;
extern Event EV_Var_IfEqual;
extern Event EV_Var_IfNotEqual;
extern Event EV_Var_IfGreater;
extern Event EV_Var_IfGreaterEqual;
extern Event EV_Var_IfLess;
extern Event EV_Var_IfLessEqual;
extern Event EV_Var_IfStrEqual;
extern Event EV_Var_IfStrNotEqual;
extern Event EV_Var_IfThreadActive;
extern Event EV_Var_IfThreadNotActive;
extern Event EV_Var_GetCvar;
extern Event EV_Var_Vector;
extern Event EV_Var_VectorIfEqual;
extern Event EV_Var_VectorIfNotEqual;
extern Event EV_Var_VectorAdd;
extern Event EV_Var_VectorSubtract;
extern Event EV_Var_VectorScale;
extern Event EV_Var_VectorNormalize;
extern Event EV_Var_VectorGetX;
extern Event EV_Var_VectorGetY;
extern Event EV_Var_VectorGetZ;
extern Event EV_Var_VectorSetX;
extern Event EV_Var_VectorSetY;
extern Event EV_Var_VectorSetZ;
extern Event EV_Var_VectorDotProduct;
extern Event EV_Var_VectorCrossProduct;
extern Event EV_Var_VectorLength;
extern Event EV_Var_AnglesToForward;
extern Event EV_Var_AnglesToRight;
extern Event EV_Var_AnglesToUp;

class ScriptVariable : public Listener
	{
	private:
		str						name;
		float						value;
		str						string;
		Vector					vec;

		void						setString( const char *newvalue );

	public:
      CLASS_PROTOTYPE( ScriptVariable );

									ScriptVariable();

		qboolean					isVariableCommand( const char *name );

		void						setName( const char *newname );
		const char				*getName( void );

		const char				*stringValue( void );
		void						setStringValue( const char *newvalue );

		int						intValue( void );
		void						setIntValue( int newvalue );

		float						floatValue( void );
		void						setFloatValue( float newvalue );

      void                 setVectorValue( Vector newvector );
		Vector               vectorValue( void );

		void 						Var_Append( Event *ev );
		void 						Var_AppendInt( Event *ev );
		void 						Var_AppendFloat( Event *ev );
		void 						Var_String( Event *ev );
      void                 Var_RandomFloat(Event *ev );
      void                 Var_RandomInteger(Event *ev );
		void 						Var_Equals( Event *ev );
		void 						Var_PlusEquals( Event *ev );
		void 						Var_MinusEquals( Event *ev );
		void 						Var_TimesEquals( Event *ev );
		void 						Var_DivideEquals( Event *ev );
      void 						Var_Div( Event *ev );
      void 						Var_Mod( Event *ev );
		void 						Var_IfEqual( Event *ev );
		void 						Var_IfNotEqual( Event *ev );
		void 						Var_IfGreater( Event *ev );
		void 						Var_IfGreaterEqual( Event *ev );
		void 						Var_IfLess( Event *ev );
		void 						Var_IfLessEqual( Event *ev );
		void 						Var_IfStrEqual( Event *ev );
		void 						Var_IfStrNotEqual( Event *ev );
		void						Var_IfThreadActive( Event *ev );
		void						Var_IfThreadNotActive( Event *ev );
		void						Var_GetCvar( Event *ev );
      void                 Var_Vector( Event *ev );
      void                 Var_Vector_Add( Event *ev );
      void                 Var_Vector_Subtract( Event *ev );
      void                 Var_Vector_Scale( Event *ev );
      void                 Var_Vector_Normalize( Event *ev );
      void                 Var_Vector_GetX( Event *ev );
      void                 Var_Vector_GetY( Event *ev );
      void                 Var_Vector_GetZ( Event *ev );
      void                 Var_Vector_SetX( Event *ev );
      void                 Var_Vector_SetY( Event *ev );
      void                 Var_Vector_SetZ( Event *ev );
      void                 Var_Vector_IfEqual( Event *ev );
      void                 Var_Vector_IfNotEqual( Event *ev );
      void                 Var_Vector_DotProduct( Event *ev );
      void                 Var_Vector_CrossProduct( Event *ev );
      void                 Var_Vector_Length( Event *ev );
      void                 Var_Angles_ToForward( Event *ev );
      void                 Var_Angles_ToLeft( Event *ev );
      void                 Var_Angles_ToUp( Event *ev );
      void                 Var_TargetOf( Event * ev );

      virtual void         Archive(	Archiver &arc );
	};

inline void ScriptVariable::Archive
	(
	Archiver &arc
	)

	{
   Listener::Archive( arc );

	arc.ArchiveString( &name );
	arc.ArchiveFloat( &value  );
	arc.ArchiveString( &string );
	arc.ArchiveVector( &vec );
	}

class ScriptVariableList : public Class
	{
	private:
		Container<ScriptVariable *> list;

	public:
      CLASS_PROTOTYPE( ScriptVariableList );

							ScriptVariableList();
							~ScriptVariableList();

		void				ClearList( void );
		void				AddVariable( ScriptVariable *var );
		ScriptVariable *CreateVariable( const char *name, float value );
		ScriptVariable *CreateVariable( const char *name, int value	);
		ScriptVariable *CreateVariable( const char *name, const char *text );
		ScriptVariable *CreateVariable( const char *name, Entity *ent );
		ScriptVariable *CreateVariable( const char *name, Vector &vec );
		void				RemoveVariable( ScriptVariable *var );
		void				RemoveVariable( const char *name );
		qboolean			VariableExists( const char *name );
		ScriptVariable *GetVariable( const char *name );
		int				NumVariables( void );
		ScriptVariable *GetVariable( int num );
		ScriptVariable *SetVariable( const char *name, float value );
		ScriptVariable *SetVariable( const char *name, int value	);
		ScriptVariable *SetVariable( const char *name, const char *text );
		ScriptVariable *SetVariable( const char *name, Entity *ent );
		ScriptVariable *SetVariable( const char *name, Vector &vec );
      virtual void   Archive(	Archiver &arc );
	};

inline void ScriptVariableList::Archive
	(
	Archiver &arc
	)

	{
   int i;
	int num;
	ScriptVariable *var;

   if ( arc.Saving() )
      {
	   num = NumVariables();
      }
   else
      {
      ClearList();
      }
	arc.ArchiveInteger( &num );
	for( i = 1; i <= num; i++ )
		{
      if ( arc.Saving() )
         {
		   var = GetVariable( i );
         }
      else
         {
         var = new ScriptVariable;
         AddVariable( var );
         }
      arc.ArchiveObject( var );
		}
	}

typedef SafePtr<ScriptVariable> ScriptVariablePtr;

#endif /* scriptvariable.h */
