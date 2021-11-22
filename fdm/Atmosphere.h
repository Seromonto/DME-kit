/****************************************************************************//*
* MIT License
* Copyright (c) 2020 Dawid Marzec
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom
* the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
******************************************************************************/

#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H
#include <math.h>
#include <data.h>

using namespace units;
using namespace std;

class Atmosphere
{
public:
    Atmosphere();

    void update( double H_alt  );

    void set( double Temp0 , double press0 );

    double get_a(){ return a;}
    double get_T(){ return T;}
    double get_p(){ return p;}
    double get_ro(){ return ro;}

private:
    double p;
    double T;
    double ro;
    double a;

    double T_celc;

    double ro0 = 1.2255;      ///< [kg/m3]
    double T0 = 288.15;       ///< [K]
    double p0 = 101325;       ///< [Pa]
    double a0 = 340.3;        ///< [m/s]

};

#endif // ATMOSPHERE_H
