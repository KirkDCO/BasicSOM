# BasicSOM

This project is a very simple example of a self-organizing map implementation that could be improved many times over.  Nonetheless, it illustrates the basic idea.  

Note that this code is _very_ old and goes back to when I did C++ on Windows using Visual Studio.  I've tested it on a Windows 7 machine, and it runs, but in some tests, the graphics don't draw properly.  (All the drawing code is Win32 API.)  There are some hardcoded dependencies (I know, I know) so it expects the Random4.csv file to be in C:\Temp on a Windows machine.  I hope to update this code at some point to be more general and Linux focused, but for now...

**Background**

In developing my own version of the SOM, I found myself faced by some choices.  The first was the structure of the SOM lattice itself.  Most implementations have a lattice which consists of a 2 dimensional grid.  This serves most purposes quite well but is not universally applicable.  Often a structure of this sort will be impacted by edge effects in which outliers tend to cluster at the edges or corners.  One application involves the mapping of the surfaces of molecules in order to provide a 2D visualization of properties at the surface.  This is essentially attempting to map a continuous surface and 2D grids can be problematic.  Rather, a torus is used which can be unfolded and viewed as a 2D grid, without the edge effects.  This can be taken further – a 3D lattice, the surface of a sphere, and even an adaptive topology.

See the documentation folder for more details.

## LICENSE

Copyright 2018 Robert Kirk DeLisle

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
