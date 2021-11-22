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

#include "Engine.h"
#include <assert.h>

using namespace EngineConst;

Engine::Engine( std::weak_ptr<EngineData> Dat )
{
    dat = Dat.lock();
}

Engine::~Engine()
{
    dat.reset();
    cout << "~Engine Destructor -> "<< dat.use_count() << endl;
}

void Engine::init_Engine()
{
    cout << "init Engine" << endl;


    dat->sk = 8;
    dat->ck = 13;
    dat->tk = 10;

    assert( dat->sk );
    assert( dat->ck );
    assert( dat->tk );

    if( dat->sk > 0 )
    {
        dat->rpm_tab   = new double [ dat->sk ];
        dat->sprez_tab = new double [ dat->sk ];
        dat->eta_tab   = new double [ dat->sk ];
        dat->mZR_tab   = new double [ dat->sk ];
    }

    dat->W_opal = 41868000.0;
    dat->Cp     = 1172.30;
    dat->eta_ks = 0.96;

    if( dat->ck > 0 )
    {
        dat->q_pal_thr = new double [dat->ck];
        dat->q_pal_tab = new double [dat->ck];
    }

    if( dat->tk )
    {
        dat->rpm_tab_t = new double [ dat->tk ];
        dat->epsT_roz_tab = new double [ dat->tk ];
    }

}

void Engine::update(Atmosphere *)
{

}

Engine *EngineConstruct::CreateEngine(EngineBuilder &builder)
{

    builder.BuildIntake();
    builder.BuildCompressor();
    builder.BuildCombustionChamber();
    builder.BuildTurbine();

    builder.BuildTurbineFree();



}

TurboShaftEngine::TurboShaftEngine()
{

    dat = std::make_shared<EngineData>( 2443 );

//    TurboShaftEng = new Engine( dat );

    TurboShaftEng = std::make_shared<Engine>(dat);

}

TurboShaftEngine::~TurboShaftEngine()
{
    TurboShaftEng.reset();
    intake.reset();
    compressor.reset();
    combchamber.reset();
    turbine.reset();
    turbine_f.reset();
    dat.reset();

    cout << "intake cout = " << intake.use_count() << endl;
    cout << "~TurboShaftEngine Destructor ->" << dat.use_count() << endl;
}

void TurboShaftEngine::BuildIntake()
{
    intake = std::make_shared<Intake> ( dat );
}

void TurboShaftEngine::BuildCompressor( )
{
    compressor = std::make_shared<Compressor> ( dat );
}

void TurboShaftEngine::BuildCombustionChamber( )
{
    combchamber = std::make_shared<CombustionChamber> ( dat );
}

void TurboShaftEngine::BuildTurbine()
{
    turbine = std::make_shared<Turbine> ( dat );
}

void TurboShaftEngine::BuildTurbineFree( )
{
    turbine_f = std::make_shared<Turbine_f>( dat );
}

Intake::Intake( std::weak_ptr<EngineData> Dat)
{
    dat      = Dat.lock();
    T1_s     = 0.0;
    TH_s     = 0.0;
    TH       = 0.0;
    Mach     = 0.0;
    pH_s     = 0.0;
    pH       = 0.0;
    p1_s     = 0.0;
    sigma_H1 = 0.0;
}

Intake::~Intake()
{
    dat.reset();
    cout << "~Intake Destructor -> " << dat.use_count() << endl;

}

void Intake::update_intake(const double T_H, const double p_H, const double Ma_H)
{
    TH   = T_H;
    pH   = p_H;
    Mach = Ma_H;

    sigma_H1 = 0.96;

    double k_Ma2 = ((k_p - 1.0) / 2.0) * Mach*Mach;
    double b_Ma2 = ( 1.0 + k_Ma2 );
    double k_div_k1 = k_p / ( k_p - 1.0 );
    double b_Ma2_k = pow( b_Ma2 , k_div_k1 );

    T1_s = TH_s = TH * ( b_Ma2 );
    pH_s = pH * ( b_Ma2_k );
    p1_s = sigma_H1 * pH_s;

    c1 = sqrt ( (T1_s - TH) * 2.0 * k_p / ( k_p - 1.0 ) * R_p );
}



Compressor::Compressor( std::weak_ptr<EngineData> Dat )
{
    dat = Dat.lock();

    p3_s = 0.0;
    sprezS_s = 0.0;
    n_zrS = 0.0;
//    n_wc = 0.0;

    mS_zr = 0.0;
    mS = 0.0;
    eta_S = 0.0;
    T3_s = 0.0;
    /// Dane:
    sprezS_s = 1.0;
    eta_S = 0.5;
    ro1_S = 1.2255;
    ro2_II_S = 1.2255;

    double const R_z0    = 0.327;          /// Rz = const
    double const R_0_WWK = 0.285;
    double const R_n_WWK = 0.29;

    double const intake_aera_0 = M_PI * ( R_z0*R_z0 - R_0_WWK*R_0_WWK );
    double const out_aera_0    = M_PI * ( R_z0*R_z0 - R_n_WWK*R_n_WWK );

    A1_S = intake_aera_0;
    A2_II_S = out_aera_0;


    sigma_s_wc = 0.98;         /// Wpolczynnik strat cisnienia spietrzenia str 43 pdf Wiatrek

}

Compressor::~Compressor()
{
    dat.reset();
    cout << "~Compresor Destructor -> " << dat.use_count() << endl;
}

void Compressor::init_compressor()
{
    sigma_s_wc = 0.98;         /// Wpolczynnik strat cisnienia spietrzenia str 43 pdf Wiatrek

}

void Compressor::update_compressor(const double p2_s, const double T2_s, const double c2, const double n_wc, const double throttle)
{
    double T_red = sqrt( T0 / T2_s );
    n_zrS = n_wc * T_red;
    double nzr_rpm = n_zrS * rads2rpm;
    int const k = 8;


    sprezS_s = Interpolation( nzr_rpm , dat->sprez_tab , dat->rpm_tab , k );
    eta_S    = Interpolation( nzr_rpm , dat->eta_tab   , dat->rpm_tab , k );
    mS_zr    = Interpolation( nzr_rpm , dat->mZR_tab   , dat->rpm_tab , k );

    mS = mS_zr * ( p2_s / p0 ) * sqrt( T0 / T2_s );
    p3_s = sprezS_s * p2_s;

    double SPREZ_k = pow( sprezS_s ,  (k_p - 1.0 ) / k_p     );
    T3_s = T2_s * ( 1.0 + ( SPREZ_k - 1.0 ) * 1.0 / (eta_S )  );

    double N_s = n_wc * rads2rpm;
    double N_szr = n_zrS * rads2rpm;

}

CombustionChamber::CombustionChamber(std::weak_ptr<EngineData> Dat)
{
    dat = Dat.lock();

    c4 = 0.01;
    p4_s = 0.0;
    sig_34 = 0.0;
    T4_s = 0.0;
    q_pal = 0.0;
    eta_ks = 0.0;
    W_opal = 0.0;
    Cp_wl = 0.0;
    m_ks = 0.0;
    sig_34 = 0.9578;
}

CombustionChamber::~CombustionChamber()
{
     dat.reset();

     cout << "~CombustionChamber Destructor -> " << dat.use_count() << endl;
}

void CombustionChamber::init_combchamber()
{
    sig_34 = 0.9578;
}

void CombustionChamber::update_comchamber(const double p3_s, const double T3_s, const double mS, const double c3, const double throttle)
{
    p4_s = sig_34 * p3_s;

    double mS_t = 1.0 / mS;

    double T4_tt = mS_t * ( q_pal  * dat->eta_ks * dat->W_opal   ) /  ( dat->Cp ) + T3_s  ;
    T4_s = T4_tt;

    c4 = ( 1.0 - p4_s / p3_s ) * R_s * T3_s / c3 + c3;

    static double T_ch = ( T4_tt );
    T_ch += ((T4_s - T_ch  ) / 1.0) * 0.1;
    T4_s = T_ch;
    m_ks = mS + q_pal ;

}

Turbine::Turbine(std::weak_ptr<EngineData> Dat)
{
    dat = Dat.lock();

    p5_s     = 0.0;
    eta_Twc  = 0.99;
    n_zrT_wc = 0.0;
    mTwc_zr  = 0.0;
    nT_wc_s  = 0.0;
    mT_wc    = 0.0;
    T5_s     = 0.0;
}

Turbine::~Turbine()
{
    dat.reset();
    cout << "~Turbine Destructor -> " << dat.use_count() << endl;
}

void Turbine::init_turbine()
{
    eta_Twc  = 0.89;

}

void Turbine::update_turbine(const double p4_s, const double T4_s, const double mS, const double c4, const double n_wc)
{
    int const k = 10;
    double T_sqrt = sqrt( T0 / T4_s );
    n_zrT_wc = n_wc * T_sqrt;           /// [rad/ s]

    double n_wc_rpm_zr = n_zrT_wc * rads2rpm;

    double epsT_roz = Interpolation( n_wc_rpm_zr , dat->epsT_roz_tab , dat->rpm_tab_t , k  );

    p5_s = p4_s / epsT_roz;

    double p5_SS = p4_s * pow( T5_s / T4_s  , k_s / ( k_s - 1.0 ) );
    p5_s = p5_SS;

    double T5_static = T5_s - c5 * c5 / ( 2.0 * dat->Cp );
    double Ma = c5 / sqrt( k_p * R_p * T5_static );
    double p5_static = p5_s / (pow( (1.0 + (k_p + 1.0) / 2.0 * Ma * Ma) , (k_p / ( k_p - 1.0 )) ));

    double mTwc_zr_tab[k]= { 2.0 , 1.17, 1.23, 1.28, 1.31,1.33, 1.34, 1.35,   1.35,    1.35    };

    T5_s = T4_s * ( 1.0 -   ( 1.0 - pow( epsT_roz , (1.0 - k_s )/k_s ) ) * eta_Twc  ) ;

    double ro_T = p5_s / ( R_s * T5_s );

    c5 = mS /( ro_T * dat->A_turbine );
}

Turbine_f::Turbine_f(std::weak_ptr<EngineData> Dat)
{
    dat = Dat.lock();

    omega = 0.0;
    eta_T = 0.9;
    p6_s = 0.0;
    T6_s = 0.0;
    c6 = 0.0;
    m6 = 0.0;
}

Turbine_f::~Turbine_f()
{
    dat.reset();
    cout << "~Turbine_f Destructor -> " << dat.use_count() << endl;
}

void Turbine_f::update_turbine_f(const double p5_s, const double T5_s, const double mS, const double c5, const double n_wc)
{
    p6_s = p0;

    T6_s = T5_s * pow(( p6_s / p5_s ) , ( k_s - 1.0) / k_s );

    double wpt = dat->Cp * ( T5_s - T6_s );
}

void Turbine_f::init_turbine_f()
{
    omega = 0.0;
    eta_T = 0.0;
    p6_s  = 0.0;
    T6_s  = 0.0;
    c6    = 0.0;
    m6    = 0.0;
}

EngineBuilder::EngineBuilder()
{

}
