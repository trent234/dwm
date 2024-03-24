# xwm - eXperimental window manager

xwm is an experiment that started as a fork of dwm and dmenu. I've been interested in hacking on a wm and instead of starting from scratch thought it'd be more fun to start with a fork of the wm that I've been using for years and have come to appreciate. Kind of like learning how a car works by slowly taking it apart, I'm using dwm to learn about xlib.

One potential goal is to boil this wm into an even simpler version that will be useful on touch devices like the reMarkable 1 and/or the PinePhone. The idea is to use dwm as the start point for the xlib wm components and dmenu for the app launcher which instead of being typing centric will list out gui apps and be scrollable and clickable. Also will be able to list open processes in that launcher as well as programs, and modifying the classic layout to instead have one main client, and all others are hidden. One exception will need to be the onscreen keyboard which will involve learning from the team behind the sxmo-dwm project and use a dock patch where svkb declares itself as a special type of client that gets handled by dwm specially.

## Current Project Status & Notes

Generally speaking these are the changes so far to dwm
* Added: 
	* Visibility for non-floating windows is defined as being the top client in the stack
	* Socket server 
		* serves the client stack 
		* accepts request for a change in client selection
		* these endpoints are used to enable app switching with dmenu
	* Default behavior is monocle, while still permitting floating windows
* Removed: 
	* Multi-monitor support
	* Tags
	* Tile layout
	* Fullscreen (technically. in practice monocle is essentially fullscreen.)
	* Layout indicator in bar

I'm removing features partly as an exercise, but it has the benefit of reducing complexity, and certain features are incompatible with the new (simpler) program architecture. 

#### wm

 This is a dynamic window manager is designed like any other X client as well. It is
 driven through handling X events (and socket events). In contrast to other X clients, a window
 manager selects for SubstructureRedirectMask on the root window, to receive
 events about window (dis-)appearance. Only one X connection at a time is
 allowed to select for this event mask.  

 The event handlers of wm are organized in an array which is accessed
 whenever a new event has been fetched. This allows event dispatching
 in O(1) time.  

 Each child of the root window is called a client, except windows which have
 set the override_redirect flag. Clients are organized in a linked client list.  

 Keys rules are organized as arrays and defined in config.h.  

## Requirements

In order to build you need the Xlib header files.

## Installation

Edit `config.mk` to match your local setup (files are installed into the /usr/local namespace by default).

Afterwards enter the following command to build and install (if necessary as root):

```
make clean install
```

## Running wm

Add the following line to your `.xinitrc` to start the window manager using `startx`:

```
exec wm
```

In order to display status info in the bar, you can do something like this in your `.xinitrc`:

```shell
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
	sleep 1
done &
exec wm
```
