-- Always include this line.  It defines the "exportskl" command.
include "o:\fakkutils\maxscripts\exportskl.ms" 

-- This is a comment.  All comments begin with double dashes

-- Because of some wierd behavior of slashes in filename strings, I
-- recommend you only use forwardslashes in filenames.  That means
-- that "h:\hm\fakk\models\julie\walk_norm.skl" should be
-- written as "h:/hm/fakk/models/julie/walk_norm.skl".  The
-- other alternative is to use double forward slashes ( "\\" ),
-- like this: "h:\\hm\\fakk\\models\\julie\\walk_norm.skl".
-- Choose whichever is easiest for you to do.

-- The following line says to export froms 449 through 481 to the
-- file d:/winnt/profiles/jimdose/desktop/test.skl.  Do this
-- for each animation you want to export.  If you have a lot
-- of animations listed and only want to export some of them,
-- comment out lines that you don't need by placing a '--' in front
-- of them.

exportskl "d:/winnt/profiles/jimdose/desktop/test.skl" 449 481

-- The command "exportsklf" tells Max to export the animation
-- at a different frame rate.  The 3rd parameter after the filename
-- is the target frame rate.
exportsklf "d:/winnt/profiles/jimdose/desktop/test.skl" 449 481 10