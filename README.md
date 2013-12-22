Complex dynamical systems
-----

Complex analysis is often considered the prettiest corner of mathematics.
Let's explore one of the reasons why that's true.


Run
-----

To build `julia` and run:

$ g++ -std=c++0x -o julia julia.cpp  
$ ./julia \<c\> \<real (z0)\>\<imag (z0)\> \<real (z1)\>\<imag (z1)\> \<dx\> \<maxiters\>

`out.txt` is written once the program is executed. A short Python script
(using `numpy` and `matplotlib`) is included for visualizing the solution.

Authors
-----
Jeff Walls \<jmwalls@umich.edu\>
