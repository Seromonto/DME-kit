/****************************************************************************//*
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

#ifndef ENGINEDATA_H
#define ENGINEDATA_H
#include <math.h>
#include <Fun.h>

//////////////////////////////////////////////////////////

namespace EngineConst
{
    static double const k_p     = 1.4;           /// wykladnik izentropy dla powietrza
    static double const k_s     = 1.33;          /// wykladnik izentropy dla spalin
    static double const R_p     = 287.14;      /// [J/kgK] stala gazowa dla powietrza
    static double const R_s     = 287.43;      /// [J/kgK] stala gazowa dla spalin
    static double const n_po    = 1.48;        /// wykladnik politropy
    static double const p0      = 101325;      /// [Pa] cisnienie - Atm wzorcowa
    static double const T0      = 288.15;      /// [K]  temp Atm wzorcowa
    static double const Tmin    = 0.01;        /// [K]  temp Atm wzorcowa
    static double const n_30_PI = 30.0/M_PI;   /// [1/rad] - 30 / PI
    static double const n_PI_30 = M_PI/30.0;   /// [rad]   - PI / 30
    static double const ro0     = 1.2255;      /// [ kg/m3 ]
}

//////////////////////////////////////////////////////////

struct EngineData
{
public:
    /// COMPRESSOR:
    int sk;

    int test;
    EngineData( int Test ) { test = Test; }

    ~EngineData()
    {
        erase (rpm_tab);
        erase (sprez_tab);
        erase (eta_tab);
        erase (mZR_tab);
        erase (q_pal_thr);
        erase (q_pal_tab);
        erase (rpm_tab_t);
        erase (epsT_roz_tab);

        cout << "~EngineData Destructor ->" << test << endl;
    }

    double *rpm_tab;
    double *sprez_tab;
    double *eta_tab;
    double *mZR_tab;


    /// COMBUSTION CHAMBER:
    int ck;
    double eta_ks;              ///< [-] - Sprawnosc komory spalania
    double Cp;                  ///< [ J / ( kg * K ) ] - cieplo wlasciwe
    double W_opal;              ///< [J/kg] - Wartosc opalowa

    double * q_pal_thr;          ///< wydatek paliwa w zaleznosci od polozenia throttle
    double * q_pal_tab;          ///< wydatek paliwa w zaleznosci od polozenia throttle

    /// TURBINE:
    int tk;

    double *rpm_tab_t;
    double *epsT_roz_tab;

    /////////////////////////////////
    double A_compressor;
    double D_compressor;
    double Dw_compressor;

    double D_turbine;
    double Dw_turbine;
    double A_turbine;
};

//////////////////////////////////////////////////////////


#endif // ENGINEDATA_H




