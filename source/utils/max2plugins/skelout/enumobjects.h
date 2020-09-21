//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max2plugins/skelout/enumobjects.h            $
// $Revision:: 3                                                              $
//     $Date:: 9/07/99 3:12p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max2plugins/skelout/enumobjects.h                 $
// 
// 3     9/07/99 3:12p Jimdose
// rewrote for ascii output
// 
// 2     7/30/99 4:23p Jimdose
// working on skel output
//
// DESCRIPTION:
// 

#ifndef __ENUMOBJECTS_H__
#define __ENUMOBJECTS_H__

#include "Max.h"
#include "skelout.h"

class GetObjectsEnumProc : public ITreeEnumProc
   {
   private :
      SkelExport     *m_skel;
      Interface      *interfaceptr;
      const char     *m_name;

	public :

      void           GetObject( str name, SkelExport *skel, ExpInterface *ei, Interface *gi );
		int            callback( INode *node );
	};

class GetNamesEnumProc : public ITreeEnumProc
   {
   private :
      Container<str> *objectnames;
      Interface      *interfaceptr;

	public :
      void           GetNames( Container<str> *names, ExpInterface *ei, Interface *gi );
		int            callback( INode *node );
	};

class GetBoneNamesEnumProc : public ITreeEnumProc
   {
   private :
      Container<str> *bonenames;
      Interface      *interfaceptr;

	public :
      void           GetNames( Container<str> *names, ExpInterface *ei, Interface *gi );
		int            callback( INode *node );
	};

class GetBonesEnumProc : public ITreeEnumProc
   {
   private :
      SkelExport     *m_skel;
      Interface      *interfaceptr;

	public :
      void           GetBones( SkelExport *skel, ExpInterface *ei, Interface *gi );
		int            callback( INode *node );
	};

#endif /* !__ENUMOBJECTS_H__ */
