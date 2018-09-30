# BasicSOM

This project is a very simple example of a self-organizing map implementation that could be improved many times over.  Nonetheless, it illustrates the basic idea.  

Note that this code is _very_ old and goes back to when I did C++ on Windows using Visual Studio.  I hope to update this code at some point, but for now...

**Background**

In developing my own version of the SOM, I found myself faced by some choices.  The first was the structure of the SOM lattice itself.  Most implementations have a lattice which consists of a 2 dimensional grid.  This serves most purposes quite well but is not universally applicable.  Often a structure of this sort will be impacted by edge effects in which outliers tend to cluster at the edges or corners.  One application involves the mapping of the surfaces of molecules in order to provide a 2D visualization of properties at the surface.  This is essentially attempting to map a continuous surface and 2D grids can be problematic.  Rather, a torus is used which can be unfolded and viewed as a 2D grid, without the edge effects.  This can be taken further – a 3D lattice, the surface of a sphere, and even an adaptive topology.

See the documentation folder for more details.
