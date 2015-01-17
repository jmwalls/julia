/*
 * Generate the Julia set for a specified constant c. The Julia set is region
 * for which points behave 'chaotically' under an iterated function.
 *
 *      f (z) = z^2 + c
 *
 * To build:
 *      $ g++ -std=c++0x -o julia julia.cpp
 *
 * To run:
 *      $ ./julia <c> <real (z0)><imag (z0)> <real (z1)><imag (z1)> <dx> <maxiters>
 *      c : parameter in f(z) = z^2 + c
 *      z0 : corner of window
 *      z1 : opposite corner of window
 *      dx : step size in points to evaluate
 *      maxiters : maximum iterations to compute
 *
 * Writes a file containing the 'color' of each point inside the specified
 * window.
 *
 * R = 1/2 + ((1 + 4*|c|)^(1/2))/2
 */

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/lexical_cast.hpp>

#include "complex.h"

using namespace std;

class Julia 
{
public:
  Julia (const Complex& c, const Complex& z0, const Complex& z1, double dx,
          size_t maxiters);
  ~Julia () {} 

  void compute ();

private:
  const Complex _c;              // complex parameter
  double _r;                     // divergence threshold

  Complex _llcorner;             // lower-left, upper-right corners
  double _dx;                    // step size
  size_t _rows, _cols;           // coordinate vals

  size_t _maxiters;

  // track coords in window, null first means has diverged, second is
  // 'color' indicating iteration when converged iter/maxiters
  vector<pair<Complex*,double> > _vals; 

  Julia () {}
};

Julia::Julia (const Complex& c, const Complex& z0, const Complex& z1, 
        double dx, size_t maxiters) 
    : _c (c), _dx (dx), _maxiters (maxiters)
{
    _r = 0.5*(1 + sqrt (1+4*_c.abs ()));

    // set window and initialize vals with coords inside window
    double ll_re = z0.real () < z1.real () ? z0.real (): z1.real (), 
           ll_im = z0.imag () < z1.imag () ? z0.imag (): z1.imag (), 
           ur_re = z0.real () > z1.real () ? z0.real (): z1.real (), 
           ur_im = z0.imag () > z1.imag () ? z0.imag (): z1.imag ();
    _llcorner = Complex (ll_re, ll_im);
    _rows = floor (ur_im - ll_im)/_dx; 
    _cols = floor (ur_re - ll_re)/_dx;
    cout << "ll left corner: " << _llcorner << endl;

    _vals.reserve (_rows*_cols);
    for (size_t i=0;i<_rows;++i) {
        for (size_t j=0;j<_cols;++j) {
            Complex *z = new Complex (ll_re+j*_dx, ll_im+i*_dx);
            if (z->abs () > _r) {
                delete z;
                z = 0;
            }
            pair<Complex*,double> p (z, 0);
            _vals.push_back (p);
        }
    }
}

void Julia::compute ()
{
    // iterate
    for (size_t k=0;k<_maxiters;++k) {
        for (size_t i=0;i<_rows;++i) {
            for (size_t j=0;j<_cols;++j) {
                pair<Complex*,double> *p = &_vals[i*_cols+j];
                if (!p->first) continue;
                Complex z = *(p->first);
                z = z*z + _c;
                if (z.abs () > _r) {
                    delete p->first;
                    p->first = 0;
                    p->second = static_cast<double> (k)/_maxiters;
                }
                else *(p->first) = z;
            }
        }
    }

    // save to file
    ofstream out ("out.txt");
    for (size_t i=0;i<_rows;++i) {
        for (size_t j=0;j<_cols;++j) {
            pair<Complex*,double> *p = &_vals[i*_cols+j];
            if (!p->first) out << p->second << "\t";
            else {
                out << 1 << "\t";
                delete p->first;
            }
        }
        out << endl;
    }
}


Complex args_to_complex (const string& re, const string& im)
{
    double r = boost::lexical_cast<double>(re);
    double i = boost::lexical_cast<double>(im);
    return Complex (r, i);
}

void print_usage (const string& bin)
{
    cout << "usage: " << bin 
        << " <re(c)><im(c)> <re(z0)><im(z0)> <re(z1)><im(z1)> <dx> <maxiters>"
        << endl 
        << "\tc : parameter in f(z) = z^2 + c" << endl
        << "\tz0 : corner of window" << endl
        << "\tz1 : opposite corner of window" << endl
        << "\tdx : step size in points to evaluate" << endl
        << "\tmaxiters : maximum iterations to compute" << endl;
}

int main (int argc, char *argv[])
{
    cout << "Generating a Julia set..." << endl;
    if (argc < 9) {
        print_usage (argv[0]);
        return EXIT_FAILURE;
    }

    Complex c = args_to_complex (argv[1], argv[2]);
    Complex z0 = args_to_complex (argv[3], argv[4]);
    Complex z1 = args_to_complex (argv[5], argv[6]);

    double dx = boost::lexical_cast<double> (argv[7]);
    size_t maxiters = boost::lexical_cast<size_t> (argv[8]);

    Julia jules (c,z0,z1,dx,maxiters);
    jules.compute ();

    return EXIT_SUCCESS;
}
