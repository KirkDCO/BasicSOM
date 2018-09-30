# BasicSOM

This project is a very simple example of a self-organizing map implementation that could be improved many times over.  Nonetheless, it illustrates the basic idea.  

Note that this code is _very_ old and goes back to when I did C++ on Windows using Visual Studio.  I've tested it on a Windows 7 machine, and it runs, but in some tests, the graphics don't draw properly.  (All the drawing code is Win32 API.)  There are some hardcoded dependencies (I know, I know) so it expects the Random4.csv file to be in C:\Temp on a Windows machine.  I hope to update this code at some point to be more general and Linux focused, but for now...

**Background**

In developing my own version of the SOM, I found myself faced by some choices.  The first was the structure of the SOM lattice itself.  Most implementations have a lattice which consists of a 2 dimensional grid.  This serves most purposes quite well but is not universally applicable.  Often a structure of this sort will be impacted by edge effects in which outliers tend to cluster at the edges or corners.  One application involves the mapping of the surfaces of molecules in order to provide a 2D visualization of properties at the surface.  This is essentially attempting to map a continuous surface and 2D grids can be problematic.  Rather, a torus is used which can be unfolded and viewed as a 2D grid, without the edge effects.  This can be taken further – a 3D lattice, the surface of a sphere, and even an adaptive topology.

See the documentation folder for more details.
