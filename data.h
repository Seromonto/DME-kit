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

#ifndef DATA_H
#define DATA_H

namespace units
{
    static const double C2K = 274.15;           ///< (+) Celcius to Kelvin
    static const double deg2rad = M_PI / 180.0;
    static const double rad2deg = 180.0 / M_PI;
    static const double gn = 9.80665;

    static const double ms2kmh = 3.6;
    static const double kmh2ms = 1.0/3.6;
    static const double rads2rpm = 9.5492965964254;
    static const double rpm2rads = 0.10471975499999982;

}

enum Phase
{
    Sim_idle = 0,
    Sim_init,
    Sim_work,
    Sim_pause,
    Sim_stop
};

#endif // DATA_H
