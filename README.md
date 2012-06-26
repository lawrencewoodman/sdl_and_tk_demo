sdl\_and\_tk\_demo
===============
A demonstration of how to embed an SDL surface in a Tk window.

This demo was inspired after seeing Kent Mein's [SDL and Tk MDI demo](http://www.libsdl.org/projects/tcl-demo/) and thinking how nice it would be to embed the SDL surface directly in the Tk window.

Requirements
------------
*  Tcl/Tk 8.5+
*  SDL Library and development files
*  CMake 2.8+ (To compile)

Compiling and Running
---------------------
To create the Makefile from the root of the repository:

    $ cmake .

Then to compile the project:

    $ make

Finally to run the program:

    $ ./sdl_and_tk_demo

Explanation
-----------
To embed an SDL surface in another window you have to alter the `SDL_WINDOWID` environmental variable so that it matches the id of the window that you want the SDL surface embedded in.  This must be done after the main window is displayed and before SDL_Init() is called.  For further information have a look at [Embedding an SDL Surface in a Tk Window](http://techtinkering.com/2012/06/26/embedding-an-sdl-surface-in-a-tk-window/)

Contributions
-------------
If you want to improve this demo please make a pull request to the [repo](https://github.com/LawrenceWoodman/sdl_and_tk_demo) on github.

Licence
-------
Copyright (c) 2012, Lawrence Woodman

This software is licensed under an MIT Licence.  Please see the file, LICENCE.md, for details.
