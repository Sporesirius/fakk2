Please do not email Ritual Entertainment with questions about the tools or the
source, we do not have the resources to support the source or the utilities.
They are provided as is, and are meant for the hardcore hackers out there.

Revision History
================
09/17/2000 - Not all the tools properly supported the FTX format.  Tools were
updated so that FTX files would not have to be re-converted back into TGA
files for the tools proper use.
09/15/2000 - Initial Release

Heavy Metal FAKK 2 TOOLS ( Version 1.02 )- 09/15/2000

license-re.rtf             - the license file
readme-re.txt              - what you are reading

bin\dlgedit.exe         - the resource building utility
bin\fontgen.exe         - Windows font converter utility
bin\ftxconvert.exe      - Converts FTX files back into TGA
bin\lipsync.exe         - generates lipsync data for wav's or mp3's
bin\lw2tan.exe          - Lightwave to tan converter
bin\max2skl.exe         - 3D Studio MAX 3.0 to SKL converter
bin\max2tan.exe         - 3D Studio MAX 3.0 to TAN converter
bin\mcopy.exe           - Handy script based copy program
bin\newq3map.exe        - Map building tool using new Vis algorithm
bin\q3map.exe           - Map building tool
bin\q3radiant.exe       - Map Editor
bin\radiant.ini         - INI file for Q3Radiant
bin\runq3radiant.bat    - Batch file to run Q3Radiant
bin\tgaconvert.exe      - Coverts TGA files into FTX files
bin\max2plugins\animout.dle - 3D Studio MAX 2.0 ANM exporter
bin\max2plugins\skelout.dle - 3D Studio MAX 2.0 SKL exporter
bin\max2plugins\uvout.dle   - 3D Studio MAX 2.0 UV exporter
bin\max3plugins\animout.dle - 3D Studio MAX 3.0 ANM exporter
bin\max3plugins\skelout.dle - 3D Studio MAX 3.0 SKL exporter
bin\max3plugins\uvout.dle   - 3D Studio MAX 3.0 UV exporter
bin\maxscripts\example.ms   - example MaxScript
bin\maxscripts\exportskl.ms - MaxScript functions
bin\maxscripts\jimtest.ms   - another MaxScript example
bin\Radiant plugins\Fakk2Plug.dll - Q3Radiant plugin in for FAKK 2

docs\AI.doc             - AI overview
docs\camera documentation.doc   - Camera system overview
docs\Client Side Commands.doc   - Client side (cgame) command overview
docs\commands.txt               - preliminary cmdlist documentation
docs\Coordinate System.doc      - Coordinate systems used in FAKK 2
docs\CVAR DOCUMENTATION.doc     - Extensive CVAR documentation
docs\Description of Menus and Ingame Utils.doc - In game tools overview
docs\Dialog System.doc          - Dialog system overview
docs\Dumping Demo AVI.doc       - Dumping demos to AVI format overview
docs\Event Spec Documentation.doc - How to document new Events
docs\FAKK FAQ.doc               - general q/a on FAKK 2 development
docs\Ghost Particle System.doc  - Particle system overview
docs\Gibs.doc                   - How to add gibs to characters
docs\GUI Documentation.doc      - GUI system overview
docs\How to Make Weapons and Ammo.doc - how to make weapons and ammo
docs\Inventory System Commands.doc - Inventory system overview
docs\Items.doc                  - items in Fakk 2
docs\MAX2SKL Reference Guide.doc - MAX2SKL reference
docs\Radiant Commands.doc       - Radiant documentation
docs\shader_manual_new.doc      - Shader Manual
docs\Sound System.doc           - Sound system overview
docs\TIKI Model System.doc      - TIKI system overview
docs\Tiki QuakeEd Specs.doc     - QUAKED specification for TIKI models

entities\entities.def           - combined QUAKED headers for Q3RADIANT

fakk\maps\example\autocamera.bsp - demonstrates use of autocameras
fakk\maps\example\autosprite.bsp - demonstrates use of autosprites
fakk\maps\example\beam.bsp      - demonstrates use of beams
fakk\maps\example\beam1.bsp     - demonstrates use of beams
fakk\maps\example\box3.bsp      - simple map
fakk\maps\example\CameraScript.bsp - demonstrates use of Scripted Cameras
fakk\maps\example\climb.bsp     - demonstrates climbing on walls and ropes
fakk\maps\example\cover.bsp     - demonstrates AI Cover
fakk\maps\example\door.bsp      - demonstrates different doors
fakk\maps\example\doors.bsp     - demonstartes more doors
fakk\maps\example\earthquake.bsp - earthquake demonstration
fakk\maps\example\explodeobject.bsp - exploding object demonstration
fakk\maps\example\exploder.bsp  - exploder demonstration
fakk\maps\example\explodingwall.bsp - explodingwall demonstration
fakk\maps\example\fallingrock.bsp - falling rock demonstration
fakk\maps\example\fulcrum.bsp   - fulcrum demonstration
fakk\maps\example\funcspawn.bsp - func_spawn demonstration
fakk\maps\example\gibs_and_health.bsp - gibs and health demonstration
fakk\maps\example\letterbox.bsp - letterbox demonstration
fakk\maps\example\multiexploder.bsp - multi-exploder demonstration
fakk\maps\example\patrol.bsp    - AI Patrol demonstration
fakk\maps\example\pickup.bsp    - Picking up Shgliek demonstration
fakk\maps\example\pushobject.bsp - Push Object demonstration
fakk\maps\example\rain.bsp      - Rain and Leaves demonstration
fakk\maps\example\runthrough.bsp - func_runthrough demonstartion
fakk\maps\example\scriptgravity.bsp - Script gravity demonstration
fakk\maps\example\sinkobject.bsp - Sink Object demonstration
fakk\maps\example\teleporter.bsp - Teleporter demonstration
fakk\maps\example\useanim.bsp   - UseAnim demonstration
fakk\maps\example\useobject.bsp - UseObject demonstration
fakk\maps\example\vehicle.bsp   - Vehicle demonstration
fakk\maps\example\zoo.bsp       - Zoo map

fakk\scripts\fakk.qe4           - Q3Radiant setup file
fakk\scripts\surfacelist.txt    - list of all textures with surface defs

source\source\cgame             - FAKK 2 CGame source

source\source\fgame             - FAKK 2 Game source

source\source\qcommon           - common files needed for above
source\source\win32             - common files needed for above

source\utils\common             - common source files for utilities
source\utils\dlgedit            - source for resource editor
source\utils\fontgen            - source for font generator
source\utils\ftxconvert         - source for FTX converter
source\utils\lipsync            - source for LIPSYNC tool
source\utils\lw2tan             - source for Lightwave converter
source\utils\max2plugins        - source for MAX 2 plugins
source\utils\max2skl            - source for MAX skeletal converter
source\utils\max2tan            - source for MAX vertex animation converter
source\utils\max3plugins        - source for MAX 3 plugins
source\utils\tgaconvert         - source for TGA converter

You will need to download the 3D Studio MAX SDK in order to rebuild the
plugins.  The lipsync converter does not include the header or library from
Miles since that is not re-distributable.

Thank you and good luck,

Scott Alden, Mark Dochtermann and Steven Peeler

The FAKK 2 Programming Team

---------------------------------------------------------------

INSTALLATION:

The tools ships with almost no game data.  As a result you will have to unpack
pak0.pk3, pak1.pk3 and pak2.pk3 in order to start building maps for the game.
You will need about 750 MB free on your hard drive to unpack these files.  To do
this, drop the PK3 files on zip extraction utility like WinZip and unpack the
paks with the Folder Names option checked into the "fakk" directory of this
install. Once you have unpacked the pak files, the editor and tools will be
able to access them freely.

In order to build maps directly from q3radiant you will need to make sure that
the file fakk.qe4 in fakk/scripts is setup properly.  The file has been
configured for an installation in the c:\fakktools\ directory if this is not
the directory you installed the tools into, you will need to edit the fakk.qe4
file.

To run the editor, run runq3radiant.bat in the bin directory or you can
create a shortcut on your desktop by leftclick-dragging q3radiant.exe on
your desktop. Go the properties tab and add the following to the command line
(Target field):

q3radiant.exe ..\fakk\scripts\fakk.qe4

LINKS:

www.gith.net - Heavy Metal FAKK 2 editing site
www.fakkyou.com - Heavy Metal FAKK 2 page

www.ritual.com - Ritual Entertainment's Home Page
www.ritualistic.com - #1 resource for Ritual related news
www.heavymetal.net - Official Heavy Metal site for Heavy Metal Magazine
