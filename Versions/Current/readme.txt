Blitzkrieg
==========================================================================
Master Candidate
17 December 2002


Contents of readme
==================

1. System requirements
2. Controls and parameters
3. Ports used for multiplayer
4. Developers feedback


==========================================================================
1. System requirements
======================

Minimum configuration:
	Windows 95/98/ME/2000
	DirectX 8.0
	Pentium II 366 MHz
	64 MB RAM
	Riva TNT / 8 MB video RAM
	2150 MB free hard drive space plus about 500 MB for Windows swap file and save games

Recommended configuration:
 	Pentium III 600 MHz
	GeForce DDR / 32 MB video RAM


==========================================================================
2. Controls and parameters
==========================

a) Supported input
------------------

	<F1> - keyboard help
	<Ctrl-F2> - <Ctrl-F4> - remember map position
	<F2> - <F4> - recall map position
	<F5> - quick save game
	<F8> - quick load game
	<F9> - make screenshot
	<F10> or <Esc> - menu

	<Space> - pause (commands can still be given in pause mode)
	<Numpad +> - increase speed
	<Numpad -> - decrease speed

	<Ctrl-0> - <Ctrl-9> - assign group number to selected units
	<0> - <9> - select group

	<Ctrl> - force attack
	<Alt> - force move
	<Shift> - add command to queue. All queued commands are executed one after another after <Shift> button is released. Note, that some commands, such as Ambush, might be blocking the rest of the queue.

	<Alt-R> - show fire ranges
	<Alt-Z> - show ranging areas

	<Enter> - enter chat mode in multiplayer
	<Backspace> - clear messages

	<`> - console

	"Ctrl-Shift-W" - wireframe mode
	"Ctrl-Shift-G" - show/hide grid
	"Ctrl-Shift-T" - show/hide terrain
	"Ctrl-Shift-O" - show/hide objects
	"Ctrl-Shift-U" - show/hide units
	"Ctrl-Shift-B" - show/hide bounding boxes
	"Ctrl-Shift-S" - turn shadows on/off
	"Ctrl-Shift-E" - show/hide effects
	"Ctrl-Shift-Q" - show/hide fog of war
	"Ctrl-Shift-R" - turn rotation on/off
	"Ctrl-Shift-A" - show/hide AI passability
	"Ctrl-Shift-D" - show/hide texture depth (32bit mode only)
	"Ctrl-Shift-I" - show/hide interface
	"Ctrl-Shift-Y" - show/hide haze
	"Ctrl-Shift-H" - show/hide health bars
	"Ctrl-Shift-N" - show/hide noise
	"Ctrl-Shift-M" - run animations
	"Ctrl-Shift-C" - center camera
	"Ctrl-Shift-P" - place effect
	"Ctrl-Shift-Backspace" - toggle ingame editor mode

	<Ctrl-R> - call recon plane
	<Ctrl-F> - call fighters
	<Ctrl-B> - call bombers
	<Ctrl-P> - call paradropers
	<Ctrl-I> - place anti-personnel mines
	<Ctrl-T> - place anti-tank mines
	<Ctrl-B-F> - build fence
	<Ctrl-B-E> - build trench
	<Ctrl-B-P> - build tank pit
	<Ctrl-R-P> - repair
	<Ctrl-R-S> - resupply
	<Ctrl-B-S> - build storage

b) Command line parameters
--------------------------

List of parameters:
	"res<width>x<height>" - set screen resolution (default - 1024x768)
	"windowed" - windowed mode
	"dxt" - use DXT compression for textures (off by default)
	"freq<##>" - set refresh frequency (60, 70, 85, 100, etc)
	"16", "32" - force 16 bit or 32 bit color depth (default - 16)
	"mapname.xml" - load map

Example:
	Game.exe -res1280x1024 -16 -windowed -freq100 -mapname.xml


c) Build description
--------------------

Build contains complete game.

==========================================================================
3. Ports used for multiplayer
======================

This section contains description of TCP/IP porst used by Blitzkrieg and GameSpy for multiplayer. 

Blitzkrieg is using UDP ports 8889 & 9089. 

GameSpy is using the following ports (unless specified otherwise, they're TCP): 
6667 (IRC) 
80 (HTTP) 
27900 (Master Server UDP Heartbeat) 
28900 (Master Server List Request) 
29900 (GP Connection Manager) 
29901 (GP Search Manager) 
13139 (Custom UDP Pings) 
6500 (incoming, UDP, default roomquery port; can be customized with roomqueryport=<port #> in svc.cfg) 
Further explanations on firewalls are available in the user help section at http://www.gamespyarcade.com/support/firewalls.shtml . 

==========================================================================
4. Developers feedback
======================

Nival Interactive
http://www.nival.com
dmitry.devishev@nival.com
