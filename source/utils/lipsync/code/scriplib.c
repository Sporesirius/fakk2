//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/lipsync/code/scriplib.c                      $
// $Revision:: 1                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 2/15/00 12:14p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/lipsync/code/scriplib.c                           $
// 
// 1     2/15/00 12:14p Steven
// 
// 7     6/08/98 11:10a Markd
// fixed const char * stuff
// 
// 6     4/28/98 10:15a Markd
// Put in scriptline support for // comments
// 
// 5     2/04/98 5:02p Markd
// Added Push and Pop Stack
// 
// 4     1/19/98 7:02p Aldie
// Changed printf to qprintf
// 
// 3     12/30/97 6:31p Jimdose
// Added header text
//
// DESCRIPTION:
// 

#include "cmdlib.h"
#include "scriplib.h"

/*
=============================================================================

						PARSING STUFF

=============================================================================
*/

typedef struct
{
	char	filename[1024];
	char    *buffer,*script_p,*end_p;
	int     line;
} script_t;

#define	MAX_INCLUDES	8
script_t	scriptstack[MAX_INCLUDES];
script_t	*script = NULL;
int			scriptline;
#ifdef SIN
script_t savedscript;
qboolean scriptstored = false;
#endif

char    token[MAXTOKEN];
qboolean endofscript;
qboolean tokenready;                     // only true if UnGetToken was just called

#ifdef SIN
/*
==============
PushScript
==============
*/
void PushScript ( void )
{
   if (script && !scriptstored)
      {
      savedscript = *script;
      scriptstored = true;
      }
}
/*
==============
PopScript
==============
*/
void PopScript ( void )
{
   if (scriptstored)
      {
      scriptstored = false;
      *script = savedscript;
      }
}

#endif

/*
==============
AddScriptToStack
==============
*/
#ifdef SIN
void AddScriptToStack (const char *filename)
#else
void AddScriptToStack (char *filename)
#endif
{
	int            size;

	script++;
	if (script == &scriptstack[MAX_INCLUDES])
		Error ("script file exceeded MAX_INCLUDES");
	strcpy (script->filename, ExpandPath (filename) );

	size = LoadFile (script->filename, (void **)&script->buffer);

	qprintf ("entering %s\n", script->filename);

	script->line = 1;

	script->script_p = script->buffer;
	script->end_p = script->buffer + size;
}


/*
==============
LoadScriptFile
==============
*/
#ifdef SIN
void LoadScriptFile (const char *filename)
#else
void LoadScriptFile (char *filename)
#endif
{
	script = scriptstack;
	AddScriptToStack (filename);

	endofscript = false;
	tokenready = false;
}


/*
==============
ParseFromMemory
==============
*/
void ParseFromMemory (char *buffer, int size)
{
	script = scriptstack;
	script++;
	if (script == &scriptstack[MAX_INCLUDES])
		Error ("script file exceeded MAX_INCLUDES");
	strcpy (script->filename, "memory buffer" );

	script->buffer = buffer;
	script->line = 1;
	script->script_p = script->buffer;
	script->end_p = script->buffer + size;

	endofscript = false;
	tokenready = false;
}


/*
==============
UnGetToken

Signals that the current token was not used, and should be reported
for the next GetToken.  Note that

GetToken (true);
UnGetToken ();
GetToken (false);

could cross a line boundary.
==============
*/
void UnGetToken (void)
{
	tokenready = true;
}


qboolean EndOfScript (qboolean crossline)
{
	if (!crossline)
		Error ("Line %i is incomplete\n",scriptline);

	if (!strcmp (script->filename, "memory buffer"))
	{
		endofscript = true;
		return false;
	}

	free (script->buffer);
	if (script == scriptstack+1)
	{
		endofscript = true;
		return false;
	}
	script--;
	scriptline = script->line;
	qprintf ("returning to %s\n", script->filename);
	return GetToken (crossline);
}

/*
==============
GetToken
==============
*/
qboolean GetToken (qboolean crossline)
{
	char    *token_p;

	if (tokenready)                         // is a token allready waiting?
	{
		tokenready = false;
		return true;
	}

	if (script->script_p >= script->end_p)
		return EndOfScript (crossline);

//
// skip space
//
skipspace:
	while (*script->script_p <= 32)
	{
		if (script->script_p >= script->end_p)
			return EndOfScript (crossline);
		if (*script->script_p++ == '\n')
		{
			if (!crossline)
				Error ("Line %i is incomplete\n",scriptline);
			scriptline = script->line++;
		}
	}

	if (script->script_p >= script->end_p)
		return EndOfScript (crossline);

	// ; # // comments
	if (*script->script_p == ';' || *script->script_p == '#'
		|| ( script->script_p[0] == '/' && script->script_p[1] == '/') )
	{
		if (!crossline)
			Error ("Line %i is incomplete\n",scriptline);
		while (*script->script_p++ != '\n')
			if (script->script_p >= script->end_p)
				return EndOfScript (crossline);
		scriptline = script->line++;
		goto skipspace;
	}

	// /* */ comments
	if (script->script_p[0] == '/' && script->script_p[1] == '*')
	{
		if (!crossline)
			Error ("Line %i is incomplete\n",scriptline);
		script->script_p+=2;
		while (script->script_p[0] != '*' && script->script_p[1] != '/')
		{
			script->script_p++;
			if (script->script_p >= script->end_p)
				return EndOfScript (crossline);
		}
		script->script_p += 2;
		goto skipspace;
	}

//
// copy token
//
	token_p = token;

	if (*script->script_p == '"')
	{
		// quoted token
		script->script_p++;
		while (*script->script_p != '"')
		{
			*token_p++ = *script->script_p++;
			if (script->script_p == script->end_p)
				break;
			if (token_p == &token[MAXTOKEN])
				Error ("Token too large on line %i\n",scriptline);
		}
		script->script_p++;
	}
	else	// regular token
	while ( *script->script_p > 32 && *script->script_p != ';')
	{
		*token_p++ = *script->script_p++;
		if (script->script_p == script->end_p)
			break;
		if (token_p == &token[MAXTOKEN])
			Error ("Token too large on line %i\n",scriptline);
	}

	*token_p = 0;

	if (!strcmp (token, "$include"))
	{
		GetToken (false);
		AddScriptToStack (token);
		return GetToken (crossline);
	}

	return true;
}


/*
==============
TokenAvailable

Returns true if there is another token on the line
==============
*/
qboolean TokenAvailable (void)
{
	char    *search_p;

	search_p = script->script_p;

	if (search_p >= script->end_p)
		return false;

	while ( *search_p <= 32)
	{
		if (*search_p == '\n')
			return false;
		search_p++;
		if (search_p == script->end_p)
			return false;

	}

	if (*search_p == ';')
		return false;

	return true;
}


