animate on 
lastpos = 0
thepos = 0
for t in 1920 to 1941 by 1 do
   (
   format "Frame: %  \t" t
   
   guysize=80
   bboxminy = -9 + 15
   horizminy = -9
   bboxminz = 118.5
  
   at time t PelvisPos=$Bip01_Pelvis.objectTransform.pos
   at time t $TAG_ORIGIN_MANUAL.pos.x=PelvisPos.x
   if ( PelvisPos.y <= horizminy ) then
      (
	  format "  One: %, %\t\t" PelvisPos.y horizminy
      if ( lastpos == 2 ) then
	     (
		 print "Last pos"
		 at time t $TAG_ORIGIN_MANUAL.pos.z=bboxminz
         at time t $TAG_ORIGIN_MANUAL.pos.y=bboxminy
		 )
	  else
	     (
	  at time t $TAG_ORIGIN_MANUAL.pos.y=PelvisPos.y
	  
	  if ( PelvisPos.z - guysize <= bboxminz ) then 
	     at time t $TAG_ORIGIN_MANUAL.pos.z=bboxminz
      else
	     at time t $TAG_ORIGIN_MANUAL.pos.z=PelvisPos.z-guysize
		 
		 )
      lastpos = 1
      )
   else
      (
      format "  Two: %, %\t\t" PelvisPos.y horizminy
	  if ( PelvisPos.y <= bboxminy ) then 
	     (
		 thepos = bboxminy
	     at time t $TAG_ORIGIN_MANUAL.pos.y = bboxminy
		 )
	  else
	     (
		 thepos = PelvisPos.y
	     at time t $TAG_ORIGIN_MANUAL.pos.y=PelvisPos.y
		 )
		 
      at time t $TAG_ORIGIN_MANUAL.pos.z=PelvisPos.z-guysize
	  
	  lastpos = 2
	  )   

   at time t format "  Result: %\n" $TAG_ORIGIN_MANUAL.pos.y
   )
