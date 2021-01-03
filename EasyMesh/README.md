# EasyMesh

********************************************************
****************                       *****************
****************   PROGRAM: EasyMesh   *****************
****************                       *****************
****************  Date: 12. 12. 2007.  *****************
****************                       *****************
****************  Author Bojan NICENO  *****************
****************                       *****************
****************  bojan.niceno@psi.ch  *****************
****************                       *****************
********************************************************

Usage: C:\Users\dell\Desktop\C++ Code\easymesh_1\Debug\easymesh_1.exe  [<options>] <NAME>

Note: <NAME> and [<options>] can be entered in any order

===============
=== OPTIONS ===
===============

Valid options are:
   +a [0..6]   bee more agressive when meshing
   -d          don't triangulate domain, just boundary
   -m          without any messages
   -r          without mesh relaxation
   -s          without Laplacian smoothing
   +eps [D,V]  create drawing in eps format
   +example    create example input files and exit

Note 1: After +a option, you should specify the agressivity
        level which is an integer value from 0 to 6. The more
        agressive you are, the chances of getting the final
        mesh are better, but the mesh quality is poorer.

Note 2: Input (and output) file can have entities such as
        nodes, segments, elements, and sides numbered from 0
        or from 1. By default, the output file will have the
        same numbering as the input file.

Note 3: If you want eps output with Delaunay or Voronoi
        mesh only, specify D or V after +eps option.
        If you don't specify anything after +eps option,
        EasyMesh will draw both meshes.

>>>>>>>>>>>>>
>>> INPUT >>>
>>>>>>>>>>>>>

Input file (NAME.d) has the following format
  first line:          <Nbp>
  following Nbp lines: <point:> <x> <y> <spacing> <marker>
  one line:            <Nbs>
  following Nbs lines: <segment:> <start_point> <end_point> <marker>

  where:
    Nbn     is the number of points defining the boundary
    Nbp     is the number of sides defining the boundary
    marker  is the boundary condition marker

Note: Input file has to end with the extension: .d !

<<<<<<<<<<<<<<
<<< OUTPUT <<<
<<<<<<<<<<<<<<

EasyMesh produces the following three output files:
  NAME.n
  NAME.e
  NAME.s

Node file (NAME.n) has the following format:
  first line:         <Nn>
  following Nn lines: <node:> <x> <y> <marker>
  last two lines:     comments inserted by the program

  where:
  Nn      is the number of nodes
  x, y    are the node coordinates
  marker  is the node boundary marker

Element file (NAME.e) has the following format:
  first line          <Ne>
  following Ne lines: <element:> <i> <j> <k> <ei> <ej> <ek> <si> <sj> <sk> <xV> <yV> <marker>
  last two lines:     comments inserted by the program

  where:
    Ne          is the number of elements
    i,   j,  k  are the nodes belonging to the element,
    ei, ej, ek  are the neighbouring elements,
    si, sj, sk  are the element sides.
    xV, yV      are the coordinates of the element circumcenter
    marker      is the side boundary marker

Side file (NAME.s) has the following format:
  first line:         <Ns>
  following Ns lines: <side:> <c> <d> <ea> <eb> <marker>
  last two lines:     comments inserted by the program

  where:
    Ns      is the number of sides
    c,  d   are the starting and ending node of the side,
    ea, eb  are the elements on the left and on the right of the side.

Note: If eb equals to -1, it means that the right element does not exists,
      i.e. the side is on the boundary !

