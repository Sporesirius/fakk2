//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/scriptvariable.cpp                 $
// $Revision:: 9                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 6/27/00 2:38p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/scriptvariable.cpp                      $
// 
// 9     6/27/00 2:38p Markd
// expanded documentation for "vector" command
// 
// 8     3/13/00 7:24p Jimdose
// change normalize to return the length
// 
// 7     1/22/00 12:44p Jimdose
// made FuzzyEqual test the variable itself and not require an extra passed in
// parameter
// 
// 6     1/21/00 7:32p Markd
// Put in fuzzy equal support into script variables
// 
// 5     1/10/00 6:17p Jimdose
// more code cleanup
// 
// 4     1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 3     10/11/99 3:10p Steven
// Event documentation cleanup.
// 
// 2     10/07/99 3:01p Steven
// Event formatting.
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 5     8/27/99 3:31p Markd
// put in "targetof" variable command
//
// DESCRIPTION:
// Dynamic variable list for scripts.
// 

#include "g_local.h"
#include "class.h"
#include "scriptvariable.h"
#include "scriptmaster.h"

#define VAR_FLOAT_EPSILON 0.0001

Event EV_Var_Append
	( 
	"append",
	EV_DEFAULT,
	"s",
	"string_to_append",
	"Appends the specified string to the current string."
	);
Event EV_Var_AppendInt
	( 
	"appendint",
	EV_DEFAULT,
	"i",
	"integer_to_append",
	"Appends the specified integer to the current string."
	);
Event EV_Var_AppendFloat
	( 
	"appendfloat",
	EV_DEFAULT,
	"f",
	"float_to_append",
	"Appends the specified float to the current string."
	);
Event EV_Var_String
	( 
	"string",
	EV_DEFAULT,
	"s",
	"new_string",
	"Sets the value of the string to the specified one."
	);
Event EV_Var_RandomFloat
	( 
	"randomfloat",
	EV_DEFAULT,
	"f",
	"max_float",
	"Sets the float to a random number."
	);
Event EV_Var_RandomInteger
	( 
	"randomint",
	EV_DEFAULT,
	"i",
	"max_int",
	"Sets the integer to a random number."
	);
Event EV_Var_TargetOf
	( 
	"targetof",
	EV_DEFAULT,
	"e",
	"ent",
	"Sets string to the specified entities target."
	);
Event EV_Var_Equals
	( 
	"=",
	EV_DEFAULT,
	"f",
	"num",
	"Sets the float to the specified number."
	);
Event EV_Var_PlusEquals
	( 
	"+=",
	EV_DEFAULT,
	"f",
	"num",
	"Adds the specified number to the current float."
	);
Event EV_Var_MinusEquals
	( 
	"-=",
	EV_DEFAULT,
	"f",
	"num",
	"Subtract the specified number to the current float."
	);
Event EV_Var_TimesEquals
	( 
	"*=",
	EV_DEFAULT,
	"f",
	"num",
	"Multiplies the current float by the specified number."
	);
Event EV_Var_DivideEquals
	( 
	"/=",
	EV_DEFAULT,
	"f",
	"num",
	"Divides the current float by the specified number."
	);
Event EV_Var_Div
	( 
	"div",
	EV_DEFAULT,
	"i",
	"num",
	"Divides the current float by the specified number (integer)."
	);
Event EV_Var_Mod
	( 
	"mod",
	EV_DEFAULT,
	"i",
	"num",
	"Gets the mod of the current int by the specified number."
	);
Event EV_Var_IfEqual
	( 
	"ifequal",
	EV_DEFAULT,
	"fSSSSSS",
	"num command arg1 arg2 arg3 arg4 arg5",
	"Processes the specified command if the variable equals the specified number."
	);
Event EV_Var_IfNotEqual
	( 
	"ifnotequal",
	EV_DEFAULT,
	"fSSSSSS",
	"num command arg1 arg2 arg3 arg4 arg5",
	"Processes the specified command if the variable doesn't equal the specified number."
	);
Event EV_Var_IfGreater
	( 
	"ifgreater",
	EV_DEFAULT,
	"fSSSSSS",
	"num command arg1 arg2 arg3 arg4 arg5",
	"Processes the specified command if the variable is greater than the specified number."
	);
Event EV_Var_IfGreaterEqual
	( 
	"ifgreaterequal",
	EV_DEFAULT,
	"fSSSSSS",
	"num command arg1 arg2 arg3 arg4 arg5",
	"Processes the specified command if the variable is\n"
	"greater than or equal to the specified number."
	);
Event EV_Var_IfLess
	( 
	"ifless",
	EV_DEFAULT,
	"fSSSSSS",
	"num command arg1 arg2 arg3 arg4 arg5",
	"Processes the specified command if the variable is less than the specified number."
	);
Event EV_Var_IfLessEqual
	( 
	"iflessequal",
	EV_DEFAULT,
	"fSSSSSS",
	"num command arg1 arg2 arg3 arg4 arg5",
	"Processes the specified command if the variable is less than or equal to the specified number."
	);
Event EV_Var_IfStrEqual
	( 
	"ifstrequal",
	EV_DEFAULT,
	"sSSSSSS",
	"test_string command arg1 arg2 arg3 arg4 arg5",
	"Processes the specified command if the variable equals the specified string."
	);
Event EV_Var_IfStrNotEqual
	( 
	"ifstrnotequal",
	EV_DEFAULT,
	"sSSSSSS",
	"test_string command arg1 arg2 arg3 arg4 arg5",
	"Processes the specified command if the variable doesn't equal the specified string."
	);
Event EV_Var_IfThreadActive
	( 
	"ifthreadactive",
	EV_DEFAULT,
	"SSSSSS",
	"command arg1 arg2 arg3 arg4 arg5",
	"Processes the specified command if the thread\n"
	"specified by the current integer value is active."
	);
Event EV_Var_IfThreadNotActive
	( 
	"ifthreadnotactive",
	EV_DEFAULT,
	"SSSSSS",
	"command arg1 arg2 arg3 arg4 arg5",
	"Processes the specified command if the thread specified\n"
	"by the current integer value is not active."
	);
Event EV_Var_GetCvar
	( 
	"getcvar",
	EV_DEFAULT,
	"s",
	"cvar_name",
	"Sets the variable to the value of the cvar."
	);
Event EV_Var_Vector
	( 
	"vector",
	EV_DEFAULT,
	"v",
	"new_vector",
	"Sets the variable to the specified vector.  New vector can also be a targetname,\n"
   "the origin of that entity will be used as the vector."
	);
Event EV_Var_VectorIfEqual
	( 
	"vector_ifequal",
	EV_DEFAULT,
	"vSSSSSS",
	"test_vector command arg1 arg2 arg3 arg4 arg5",
	"Processes the specified command if the variable is equal to the specified vector."
	);
Event EV_Var_VectorIfNotEqual
	( 
	"vector_ifnotequal",
	EV_DEFAULT,
	"vSSSSSS",
	"test_vector command arg1 arg2 arg3 arg4 arg5",
	"Processes the specified command if the variable is not equal to the specified vector."
	);
Event EV_Var_VectorAdd
	( 
	"vector_add",
	EV_DEFAULT,
	"v",
	"new_vector",
	"Adds the specified vector to the variable."
	);
Event EV_Var_VectorSubtract
	( 
	"vector_subtract",
	EV_DEFAULT,
	"v",
	"new_vector",
	"Subtracts the specified vector from the variable."
	);
Event EV_Var_VectorScale
	( 
	"vector_scale",
	EV_DEFAULT,
	"f",
	"scale",
	"Scales the variable (vector) by the scale value."
	);
Event EV_Var_VectorDotProduct
	( 
	"vector_dot",
	EV_DEFAULT,
	"vv",
	"vector1 vector2",
	"Sets the variable to the dot product of the specified vectors."
	);
Event EV_Var_VectorCrossProduct
	( 
	"vector_cross",
	EV_DEFAULT,
	"vv",
	"vector1 vector2",
	"Sets the variable to the cross product of the specified vectors."
	);
Event EV_Var_VectorNormalize
	( 
	"vector_normalize",
	EV_DEFAULT,
	NULL,
	NULL,
	"Normalize the variable (vector)."
	);
Event EV_Var_VectorLength
	( 
	"vector_length",
	EV_DEFAULT,
	"v",
	"new_vector",
	"Sets the variable (float) to the length of the specified vector."
	);
Event EV_Var_VectorGetX
	( 
	"vector_x",
	EV_DEFAULT,
	"v",
	"new_vector",
	"Sets the variable (float) to the x value of the specified vector."
	);
Event EV_Var_VectorGetY
	( 
	"vector_y",
	EV_DEFAULT,
	"v",
	"new_vector",
	"Sets the variable (float) to the y value of the specified vector."
	);
Event EV_Var_VectorGetZ
	( 
	"vector_z",
	EV_DEFAULT,
	"v",
	"new_vector",
	"Sets the variable (float) to the z value of the specified vector."
	);
Event EV_Var_VectorSetX
	( 
	"vector_setx",
	EV_DEFAULT,
	"f",
	"x_coord",
	"Sets the x value of the variable (vector)."
	);
Event EV_Var_VectorSetY
	( 
	"vector_sety",
	EV_DEFAULT,
	"f",
	"y_coord",
	"Sets the y value of the variable (vector)."
	);
Event EV_Var_VectorSetZ
	( 
	"vector_setz",
	EV_DEFAULT,
	"f",
	"z_coord",
	"Sets the z value of the variable (vector)."
	);
Event EV_Var_AnglesToForward
	( 
	"angles_toforward",
	EV_DEFAULT,
	"v",
	"angles",
	"Sets the variable (vector) to the forward vector of the specified angles."
	);
Event EV_Var_AnglesToLeft
	( 
	"angles_toleft",
	EV_DEFAULT,
	"v",
	"angles",
	"Sets the variable (vector) to the left vector of the specified angles."
	);
Event EV_Var_AnglesToUp
	( 
	"angles_toup",
	EV_DEFAULT,
	"v",
	"angles",
	"Sets the variable (vector) to the up vector of the specified angles."
	);

static void VarProcessCommand
	(
	Event *ev,
	int arg
	)
	
	{
	ScriptThread *thread;

	thread = ev->GetThread();
	if ( thread )
		{
		thread->ProcessCommandFromEvent( ev, arg );
		}
	}

CLASS_DECLARATION( Listener, ScriptVariable, NULL )
	{
	   { &EV_Var_Append,					   Var_Append },
	   { &EV_Var_AppendInt,				   Var_AppendInt },
	   { &EV_Var_AppendFloat,			   Var_AppendFloat },
	   { &EV_Var_String,					   Var_String },
      { &EV_Var_RandomFloat,           Var_RandomFloat },
      { &EV_Var_RandomInteger,         Var_RandomInteger },
	   { &EV_Var_TargetOf,				   Var_TargetOf },
	   { &EV_Var_Equals,					   Var_Equals },
	   { &EV_Var_PlusEquals,			   Var_PlusEquals },
	   { &EV_Var_MinusEquals,			   Var_MinusEquals },
	   { &EV_Var_TimesEquals,			   Var_TimesEquals },
	   { &EV_Var_DivideEquals,			   Var_DivideEquals },
      { &EV_Var_Div,	         		   Var_Div },
      { &EV_Var_Mod,	         		   Var_Mod },
	   { &EV_Var_IfEqual,				   Var_IfEqual },
	   { &EV_Var_IfNotEqual,			   Var_IfNotEqual },
	   { &EV_Var_IfGreater,				   Var_IfGreater },
	   { &EV_Var_IfGreaterEqual,		   Var_IfGreaterEqual },
	   { &EV_Var_IfLess,					   Var_IfLess },
	   { &EV_Var_IfLessEqual,			   Var_IfLessEqual },
	   { &EV_Var_IfStrEqual,			   Var_IfStrEqual },
	   { &EV_Var_IfStrNotEqual,		   Var_IfStrNotEqual },
		{ &EV_Var_IfThreadActive,		   Var_IfThreadActive },
		{ &EV_Var_IfThreadNotActive,	   Var_IfThreadNotActive },
		{ &EV_Var_GetCvar,				   Var_GetCvar },
		{ &EV_Var_Vector,				      Var_Vector },
		{ &EV_Var_VectorAdd,				   Var_Vector_Add },
		{ &EV_Var_VectorSubtract,		   Var_Vector_Subtract },
		{ &EV_Var_VectorScale,			   Var_Vector_Scale },
		{ &EV_Var_VectorNormalize,		   Var_Vector_Normalize },
		{ &EV_Var_VectorGetX,			   Var_Vector_GetX },
		{ &EV_Var_VectorGetY,			   Var_Vector_GetY },
		{ &EV_Var_VectorGetZ,			   Var_Vector_GetZ },
		{ &EV_Var_VectorSetX,			   Var_Vector_SetX },
		{ &EV_Var_VectorSetY,			   Var_Vector_SetY },
		{ &EV_Var_VectorSetZ,			   Var_Vector_SetZ },
		{ &EV_Var_VectorIfEqual,		   Var_Vector_IfEqual },
		{ &EV_Var_VectorIfNotEqual,	   Var_Vector_IfNotEqual },
		{ &EV_Var_VectorDotProduct,	   Var_Vector_DotProduct },
		{ &EV_Var_VectorCrossProduct,	   Var_Vector_CrossProduct },
		{ &EV_Var_VectorLength,	         Var_Vector_Length },
		{ &EV_Var_AnglesToForward,	      Var_Angles_ToForward },
		{ &EV_Var_AnglesToLeft,	         Var_Angles_ToLeft },
		{ &EV_Var_AnglesToUp,	         Var_Angles_ToUp },
		{ NULL, NULL }
	};

ScriptVariable::ScriptVariable()
	{
	value = 0;
	}

qboolean ScriptVariable::isVariableCommand
	(
	const char *name
	)

	{
	int i;

	for( i = 0; ScriptVariable::Responses[ i ].event != NULL; i++ )
		{
		if ( ScriptVariable::Responses[ i ].event->getName() == name )
			{
			return true;
			}
		}

	return false;
	}


void ScriptVariable::setName
	( 
	const char *newname 
	)

	{
	name = newname;
	}

const char *ScriptVariable::getName
	( 
	void 
	)

	{
	return name.c_str();
	}

const char *ScriptVariable::stringValue
	( 
	void 
	)

	{
	return string.c_str();
	}

void ScriptVariable::setString
	( 
	const char *value 
	)

	{
	string = value;
	}

void ScriptVariable::setStringValue
	( 
	const char *newvalue 
	)

	{
	setString( newvalue );
	value = atof( string.c_str() );
	}

int ScriptVariable::intValue
	( 
	void 
	)

	{
	return ( int )value;
	}

void ScriptVariable::setIntValue
	( 
	int newvalue 
	)

	{
	char text[ 128 ];

	value = ( float )newvalue;
	sprintf( text, "%d", newvalue );
	setString( text );
	}

float ScriptVariable::floatValue
	(
	void 
	)

	{
	return value;
	}

void ScriptVariable::setFloatValue
	( 
	float newvalue 
	)

	{
	char text[ 128 ];

	value = newvalue;
	sprintf( text, "%f", newvalue );
	setString( text );
	}

void ScriptVariable::setVectorValue
	( 
	Vector newvector
	)

	{
	char text[ 128 ];

   vec = newvector;
   sprintf( text, "(%f %f %f)", newvector.x, newvector.y, newvector.z );
	setString( text );
	}

Vector ScriptVariable::vectorValue
	(
	void 
	)

	{
	return vec;
	}

CLASS_DECLARATION( Class, ScriptVariableList, NULL )
	{
		{ NULL, NULL }
	};

ScriptVariableList::ScriptVariableList()
	{
	}

ScriptVariableList::~ScriptVariableList()
	{
	ClearList();
	}


void ScriptVariableList::ClearList
	(
	void
	)

	{
	int i;
	int num;
	ScriptVariable *var;

	num = NumVariables();
	for( i = num; i > 0; i-- )
		{
		var = GetVariable( i );
		RemoveVariable( var );
      delete var;
		}

	list.FreeObjectList();
	}

void ScriptVariableList::AddVariable
	(
	ScriptVariable *var
	)

	{
	if ( VariableExists( var->getName() ) )
		{
		warning( "AddVariable", "Variable %s already exists.\n", var->getName() );
		return;
		}

	list.AddObject( var );
	}

ScriptVariable *ScriptVariableList::CreateVariable
	(
	const char *name,
	float value	
	)

	{
	ScriptVariable *var;

	if ( VariableExists( name ) )
		{
		warning( "AddVariable", "Variable %s already exists.\n", name );
		return GetVariable( name );
		}

	var = new ScriptVariable;
	var->setName( name );
	var->setFloatValue( value );
	list.AddObject( var );

	return var;
	}

ScriptVariable *ScriptVariableList::CreateVariable
	(
	const char *name,
	int value
	)

	{
	ScriptVariable *var;

	if ( VariableExists( name ) )
		{
		warning( "AddVariable", "Variable %s already exists.\n", name );
		return GetVariable( name );
		}

	var = new ScriptVariable;
	var->setName( name );
	var->setIntValue( value );
	list.AddObject( var );

	return var;
	}

ScriptVariable *ScriptVariableList::CreateVariable
	(
	const char *name,
	const char *text
	)

	{
	ScriptVariable *var;

	if ( VariableExists( name ) )
		{
		warning( "AddVariable", "Variable %s already exists.\n", name );
		return GetVariable( name );
		}

	var = new ScriptVariable;
	var->setName( name );
	var->setStringValue( text );
	list.AddObject( var );

	return var;
	}

ScriptVariable *ScriptVariableList::CreateVariable
	(
	const char *name,
	Entity *ent
	)

	{
	ScriptVariable *var;

	assert( ent );

	if ( VariableExists( name ) )
		{
		warning( "AddVariable", "Variable %s already exists.\n", name );
		return GetVariable( name );
		}

	var = new ScriptVariable;
	var->setName( name );
	list.AddObject( var );

	if ( !ent )
		{
		warning( "SetVariable", "Null entity\n" );

		// use the world
		var->setStringValue( "*0" );
		}
	else
		{
		var->setStringValue( va( "*%d", ent->entnum ) );
		}

	return var;
	}

ScriptVariable *ScriptVariableList::CreateVariable
	(
	const char *name,
	Vector &vec
	)

	{
	ScriptVariable *var;

	if ( VariableExists( name ) )
		{
		warning( "AddVariable", "Variable %s already exists.\n", name );
		return GetVariable( name );
		}

	var = new ScriptVariable;
	var->setName( name );
	var->setStringValue( va( "(%f %f %f)", vec.x, vec.y, vec.z) );
	list.AddObject( var );

	return var;
	}

void ScriptVariableList::RemoveVariable
	( 
	ScriptVariable *var 
	)

	{
	if ( !list.ObjectInList( var ) )
		{
		warning( "RemoveVariable", "Variable %s does not exist.\n", var->getName() );
		return;
		}

	list.RemoveObject( var );
	}

void ScriptVariableList::RemoveVariable
	( 
	const char *name 
	)

	{
	ScriptVariable *var;

	var = GetVariable( name );
	if ( !var )
		{
		warning( "RemoveVariable", "Variable %s does not exist.\n", name );
		return;
		}

	RemoveVariable( var );
	}

qboolean ScriptVariableList::VariableExists
	(
	const char *name
	)

	{
	int i;
	int num;
	ScriptVariable *var;

	num = list.NumObjects();
	for( i = 1; i <= num; i++ )
		{
		var = list.ObjectAt( i );
		if ( !strcmp( var->getName(), name ) )
			{
			return true;
			}
		}

	return false;
	}

ScriptVariable *ScriptVariableList::GetVariable
	(
	const char *name
	)

	{
	int i;
	int num;
	ScriptVariable *var;

	num = list.NumObjects();
	for( i = 1; i <= num; i++ )
		{
		var = list.ObjectAt( i );
		if ( !strcmp( var->getName(), name ) )
			{
			return var;
			}
		}

	return NULL;
	}

int ScriptVariableList::NumVariables
	(
	void
	)

	{
	return list.NumObjects();
	}

ScriptVariable *ScriptVariableList::GetVariable
	(
	int num
	)

	{
	return list.ObjectAt( num );
	}

ScriptVariable *ScriptVariableList::SetVariable
	(
	const char *name,
	float value	
	)

	{
	ScriptVariable *var;

	var = GetVariable( name );
	if ( !var )
		{
		var = new ScriptVariable;
		var->setName( name );
		list.AddObject( var );
		}

	var->setFloatValue( value );

	return var;
	}

ScriptVariable *ScriptVariableList::SetVariable
	(
	const char *name,
	int value
	)

	{
	ScriptVariable *var;

	var = GetVariable( name );
	if ( !var )
		{
		var = new ScriptVariable;
		var->setName( name );
		list.AddObject( var );
		}

	var->setIntValue( value );

	return var;
	}

ScriptVariable *ScriptVariableList::SetVariable
	(
	const char *name,
	const char *text
	)

	{
	ScriptVariable *var;

	var = GetVariable( name );
	if ( !var )
		{
		var = new ScriptVariable;
		var->setName( name );
		list.AddObject( var );
		}

	var->setStringValue( text );

	return var;
	}

ScriptVariable *ScriptVariableList::SetVariable
	(
	const char *name,
	Entity *ent
	)

	{
	ScriptVariable *var;

	var = GetVariable( name );
	if ( !var )
		{
		var = new ScriptVariable;
		var->setName( name );
		list.AddObject( var );
		}

	if ( !ent )
		{
		// use the world
		var->setStringValue( "*0" );
		}
	else
		{
		var->setStringValue( va( "*%d", ent->entnum ) );
		}

	return var;
	}

ScriptVariable *ScriptVariableList::SetVariable
	(
	const char *name,
	Vector &vec
	)

	{
	ScriptVariable *var;

	var = GetVariable( name );
	if ( !var )
		{
		var = new ScriptVariable;
		var->setName( name );
		list.AddObject( var );
		}

	var->setStringValue( va( "(%f %f %f)", vec.x, vec.y, vec.z) );

	return var;
	}

//****************************************************************************************
//
// Variable commands
// 
//****************************************************************************************

void ScriptVariable::Var_Append
	(
	Event *ev
	)

	{
	str newstring;

	newstring = string + ev->GetString( 1 );
	setStringValue( newstring.c_str() );
	}

void ScriptVariable::Var_AppendInt
	(
	Event *ev
	)

	{
	str newstring;

	newstring = string + va( "%d", ev->GetInteger( 1 ) );
	setStringValue( newstring.c_str() );
	}

void ScriptVariable::Var_AppendFloat
	(
	Event *ev
	)

	{
	str newstring;

	newstring = string + va( "%f", ev->GetFloat( 1 ) );
	setStringValue( newstring.c_str() );
	}

void ScriptVariable::Var_String
	(
	Event *ev
	)

	{
	setStringValue( ev->GetString( 1 ) );
	}

void ScriptVariable::Var_RandomFloat
	(
	Event *ev
	)

	{
   setFloatValue( G_Random( ev->GetFloat( 1 ) ) );
	}

void ScriptVariable::Var_RandomInteger
	(
	Event *ev
	)

	{
   setIntValue( G_Random( ev->GetInteger( 1 ) ) );
	}



void ScriptVariable::Var_Equals
	(
	Event *ev
	)

	{
	setFloatValue( ev->GetFloat( 1 ) );
	}

void ScriptVariable::Var_PlusEquals
	(
	Event *ev
	)

	{
	setFloatValue( floatValue() + ev->GetFloat( 1 ) );
	}

void ScriptVariable::Var_MinusEquals
	(
	Event *ev
	)

	{
	setFloatValue( floatValue() - ev->GetFloat( 1 ) );
	}

void ScriptVariable::Var_TimesEquals
	(
	Event *ev
	)

	{
	setFloatValue( floatValue() * ev->GetFloat( 1 ) );
	}

void ScriptVariable::Var_DivideEquals
	(
	Event *ev
	)

	{
	setFloatValue( floatValue() / ev->GetFloat( 1 ) );
	}

void ScriptVariable::Var_Div
	(
	Event *ev
	)

	{
	setIntValue( floatValue() / ev->GetInteger( 1 ) );
	}

void ScriptVariable::Var_Mod
	(
	Event *ev
	)

	{
	setIntValue( intValue() % ev->GetInteger( 1 ) );
	}


void ScriptVariable::Var_IfEqual
	(
	Event *ev
	)

	{
	if ( fabs( floatValue() - ev->GetFloat( 1 ) ) < VAR_FLOAT_EPSILON )
		{
		VarProcessCommand( ev, 2 );
		}
	}

void ScriptVariable::Var_IfNotEqual
	(
	Event *ev
	)

	{
	if ( fabs( floatValue() - ev->GetFloat( 1 ) ) >= VAR_FLOAT_EPSILON )
		{
		VarProcessCommand( ev, 2 );
		}
	}

void ScriptVariable::Var_IfGreater
	(
	Event *ev
	)

	{
	if ( floatValue() > ev->GetFloat( 1 ) )
		{
		VarProcessCommand( ev, 2 );
		}
	}

void ScriptVariable::Var_IfGreaterEqual
	(
	Event *ev
	)

	{
	if ( floatValue() >= ev->GetFloat( 1 ) )
		{
		VarProcessCommand( ev, 2 );
		}
	}

void ScriptVariable::Var_IfLess
	(
	Event *ev
	)

	{
	if ( floatValue() < ev->GetFloat( 1 ) )
		{
		VarProcessCommand( ev, 2 );
		}
	}

void ScriptVariable::Var_IfLessEqual
	(
	Event *ev
	)

	{
	if ( floatValue() <= ev->GetFloat( 1 ) )
		{
		VarProcessCommand( ev, 2 );
		}
	}

void ScriptVariable::Var_IfStrEqual
	(
	Event *ev
	)

	{
	if ( stricmp( stringValue(), ev->GetString( 1 ) ) == 0 )
		{
		VarProcessCommand( ev, 2 );
		}
	}

void ScriptVariable::Var_IfStrNotEqual
	(
	Event *ev
	)

	{
	if ( stricmp( stringValue(), ev->GetString( 1 ) ) != 0 )
		{
		VarProcessCommand( ev, 2 );
		}
	}

void ScriptVariable::Var_IfThreadActive
	(
	Event *ev
	)

	{
	ScriptThread *thread;
	
	thread = Director.GetThread( intValue() );
	if ( thread )
		{
		VarProcessCommand( ev, 1 );
		}
	}

void ScriptVariable::Var_IfThreadNotActive
	(
	Event *ev
	)

	{
	ScriptThread *thread;
	
	thread = Director.GetThread( intValue() );
	if ( !thread )
		{
		VarProcessCommand( ev, 1 );
		}
	}

void ScriptVariable::Var_GetCvar
	(
	Event *ev
	)

	{
	cvar_t *var;
	
	var = gi.cvar( ev->GetString( 1 ), "", 0 );
	setStringValue( var->string );
	}

void ScriptVariable::Var_Vector
	(
	Event *ev
	)

	{
	setVectorValue( ev->GetVector( 1 ) );
	}

void ScriptVariable::Var_Vector_Add
	(
	Event *ev
	)

	{
   Vector tempvec;

   tempvec = vectorValue();
   tempvec += ev->GetVector( 1 );
	setVectorValue( tempvec );
	}

void ScriptVariable::Var_Vector_Subtract
	(
	Event *ev
	)

	{
   Vector tempvec;

   tempvec = vectorValue();
   tempvec -= ev->GetVector( 1 );
	setVectorValue( tempvec );
	}

void ScriptVariable::Var_Vector_Scale
	(
	Event *ev
	)

	{
   Vector tempvec;

   tempvec = vectorValue();
   tempvec = tempvec * ev->GetFloat( 1 );
	setVectorValue( tempvec );
	}

void ScriptVariable::Var_Vector_Normalize
	(
	Event *ev
	)

	{
   Vector vec( vectorValue() );
   vec.normalize();
	setVectorValue( vec );
	}

void ScriptVariable::Var_Vector_GetX
   ( 
   Event *ev 
   )
   {
	setFloatValue( ev->GetVector( 1 ).x );
   }

void ScriptVariable::Var_Vector_GetY
   ( 
   Event *ev 
   )
   {
	setFloatValue( ev->GetVector( 1 ).y );
   }

void ScriptVariable::Var_Vector_GetZ
   ( 
   Event *ev 
   )
   {
	setFloatValue( ev->GetVector( 1 ).z );
   }

void ScriptVariable::Var_Vector_SetX
   ( 
   Event *ev 
   )
   {
   Vector tempvec;

   tempvec = vectorValue();
   tempvec.x = ev->GetFloat( 1 );
	setVectorValue( tempvec );
   }

void ScriptVariable::Var_Vector_SetY
   ( 
   Event *ev 
   )
   {
   Vector tempvec;

   tempvec = vectorValue();
   tempvec.y = ev->GetFloat( 1 );
	setVectorValue( tempvec );
   }

void ScriptVariable::Var_Vector_SetZ
   ( 
   Event *ev 
   )
   {
   Vector tempvec;

   tempvec = vectorValue();
   tempvec.z = ev->GetFloat( 1 );
	setVectorValue( tempvec );
   }

void ScriptVariable::Var_Vector_IfEqual
	(
	Event *ev
	)

	{
   if ( vectorValue().FuzzyEqual( ev->GetVector( 1 ), VAR_FLOAT_EPSILON ) )
		{
		VarProcessCommand( ev, 2 );
		}
	}

void ScriptVariable::Var_Vector_IfNotEqual
	(
	Event *ev
	)

	{
	if ( !vectorValue().FuzzyEqual( ev->GetVector( 1 ), VAR_FLOAT_EPSILON ) )
		{
		VarProcessCommand( ev, 2 );
		}
	}

void ScriptVariable::Var_Vector_DotProduct
   ( 
   Event *ev 
   )
   {
   Vector vec1, vec2;

   vec1 = ev->GetVector( 1 );
   vec2 = ev->GetVector( 2 );
	setFloatValue( vec1 * vec2 );
   }

void ScriptVariable::Var_Vector_Length
   ( 
   Event *ev 
   )
   {
	setFloatValue( ev->GetVector( 1 ).length() );
   }

void ScriptVariable::Var_Vector_CrossProduct
   ( 
   Event *ev 
   )
   {
   Vector vec1, vec2, cross;

   vec1 = ev->GetVector( 1 );
   vec2 = ev->GetVector( 2 );
   cross.CrossProduct( vec1, vec2 );
	setVectorValue( cross );
   }

void ScriptVariable::Var_Angles_ToForward
   ( 
   Event *ev 
   )
   {
   Vector forward;

   ev->GetVector( 1 ).AngleVectors( &forward, NULL, NULL );
	setVectorValue( forward );
   }

void ScriptVariable::Var_Angles_ToLeft
   ( 
   Event *ev 
   )
   {
   Vector left;

   ev->GetVector( 1 ).AngleVectors( NULL, &left, NULL );
	setVectorValue( left );
   }

void ScriptVariable::Var_Angles_ToUp
   ( 
   Event *ev 
   )
   {
   Vector up;

   ev->GetVector( 1 ).AngleVectors( NULL, NULL, &up );
	setVectorValue( up );
   }

void ScriptVariable::Var_TargetOf
	(
	Event *ev
	)
	{
   Entity * ent;
   const char *target;

   ent = ev->GetEntity( 1 );
   if ( ent )
      {
      target = ent->Target();
      }
   else
      {
      return;
      }

   if ( target )
      {
		setStringValue( va( "$%s", target ) );
		}
	}
