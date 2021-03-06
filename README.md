Complex dynamical systems
-----

Complex analysis is often considered the prettiest corner of mathematics.
Let's explore one of the reasons why that's true.

We'll compute the Julia set of a complex dynamical system---the quadratic
polynomial

$$
\begin{equation}
    f (z) = z^2 + c
\end{equation}
$$

![Alt text](https://raw.githubusercontent.com/jmwalls/julia/master/example.png "c = -0.726895347709114071439 + 0.188887129043845954792 i")


Run
-----

We use Boost (for lexical casting), but otherwise there are no other
dependencies. To build `julia` and run:

$ g++ -std=c++0x -o julia julia.cpp  
$ ./julia \<c\> \<real (z0)\>\<imag (z0)\> \<real (z1)\>\<imag (z1)\> \<dx\> \<maxiters\>

`out.txt` is written once the program is executed. A short Python script
(using `numpy` and `matplotlib`) is included for visualizing the solution.

Authors
-----
Jeff Walls \<jmwalls@umich.edu\>
