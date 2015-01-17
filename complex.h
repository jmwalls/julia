#ifndef __JULIA_COMPLEX_H__
#define __JULIA_COMPLEX_H__

#include <cmath>
#include <iostream>

class Complex
{
public:
  Complex (double re, double im) : _re (re), _im (im) {}
  Complex (const double* c) : _re (c[0]), _im (c[1]) {}
  Complex () : _re (0), _im (0) {}

  Complex& operator= (const Complex& c)
  {
      if (this==&c) return *this;
      _re = c._re;
      _im = c._im;
      return *this;
  }

  double abs () const {return sqrt (_re*_re + _im*_im);}
  double real () const {return _re;}
  double imag () const {return _im;}

  bool operator== (const Complex& c) const 
  {
      return (_re==c._re && _im==c._im);
  }
  Complex operator+ (const Complex& rhs)
  {
      Complex ret (*this);
      ret._re += rhs._re;
      ret._im += rhs._im;
      return ret;
  }
  Complex operator- (const Complex& rhs)
  {
      Complex ret (*this);
      ret._re -= rhs._re;
      ret._im -= rhs._im;
      return ret;
  }
  Complex operator* (const Complex& rhs)
  {
      Complex ret (*this);
      ret._re = _re*rhs._re - _im*rhs._im;
      ret._im = _re*rhs._im + _im*rhs._re;
      return ret;
  }

private:
  double _re, _im;
};

std::ostream& operator<< (std::ostream& os, const Complex& c)
{
    double re = c.real (), im = c.imag ();
    os << re << (im<0 ? " - " : " + ") << fabs (im) << "i";
    return os;
}

#endif // __JULIA_COMPLEX_H__
