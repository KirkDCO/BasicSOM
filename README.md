# BasicSOM

Background

In developing my own version of the SOM, I found myself faced by some choices.  The first was the structure of the SOM lattice itself.  Most implementations have a lattice which consists of a 2 dimensional grid.  This serves most purposes quite well but is not universally applicable.  Often a structure of this sort will be impacted by edge effects in which outliers tend to cluster at the edges or corners.  One application involves the mapping of the surfaces of molecules in order to provide a 2D visualization of properties at the surface.  This is essentially attempting to map a continuous surface and 2D grids can be problematic.  Rather, a torus is used which can be unfolded and viewed as a 2D grid, without the edge effects.  This can be taken further – a 3D lattice, the surface of a sphere, and even an adaptive topology.

Base classes

This dilemma led me to develop a few base classes which I felt captured the essence of the SOM.  I attempted to apply some standard design patterns in order to allow flexibility in the construction of the SOM.

CSOMLattice

        This class is the SOM lattice itself.  It contains the primary functionality of the class, the nodes of the lattice, the training protocol, etc.  In retrospect, I think I would make this into ISOMLattice such that various training methods and lattice behaviors would be allowed.

CSOMLatticeSettings

        This class merely contains all the standard settings for a CSOMLattice.  It allows me to set the properties of my SOM up front and assign them with a single function call.

ISOMLatticeTopology

        This pure virtual class defines an interface for the topology of the lattice.  Its role is to contain the topological structure of the lattice and thus know the relationships between nodes.  The CSOMLattice object asks the ISOMLatticeTopology the distance between nodes during the training process.

ISOMCell

        The ISOMCell interface allows cells to take on any representation.  Typically, I’ve seen representations which are merely vectors of floating point numbers.
Suppose, however, that I have a very non-standard representation that doesn’t fit this method.  Again, many representations of small molecules are quite unusual.  The role of the ISOMCell is to know how to adjust itself during training and also has the ability of measure similarity to another cell.  I use the later as a method to decide winning nodes:  I take an observation from the data space I’m trying to model, convert it to a Cell, and use that for measuring distances to SOM cells/nodes.

ISOMCellFactory

        As mentioned, I always have to convert data observations into SOM cells.  The ISOMCellFactory interface defines those functions necessary to convert any data representation into an ISOMCell.  Effectively, thins acts to convert a file with my data into a Lattice of SOM Cells/nodes.

CExceptionRKD

        This is an exception class I developed which I’ve used a few times in other project.  Very inconsequential.

Dataset and Observation

        These classes are very old and merely allow me to load a comma separated data file.  They have a few hardwired dependencies:
    • Data must be in a CSV file.
    • The first row contains the names of the columns – they are not used
    • It doesn’t tolerate missing values
    • It requires floating point values

This project uses the DataSet as a simple example.  By deriving from the ISOMCellFactory, you can easily use any data class – or not – that you want.

The project I’ve put together is a very simple application that could be improved many times over.  Nonetheless, it illustrates the basic idea.  Here’s the main code with some comments.  There is other code that does some basic drawing and record keeping, but it is simple to understand.
