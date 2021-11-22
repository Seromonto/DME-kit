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

#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <Atmosphere.h>
#include <enginedata.h>
#include <memory>

using namespace std;

class Intake
{
public:
    Intake( std::weak_ptr<EngineData> Dat );
    virtual ~Intake() ;


    void init_intake();
    void update_intake( double const T_H , double const p_H , double const Ma_H  );

    double get_p1_s(){ return p1_s; }
    double get_T1_s(){ return T1_s; }
    double get_c1() { return  c1;}

private:

    double T1_s;
    double TH_s;
    double TH;
    double Mach;
    double pH_s , pH , p1_s ;
    double sigma_H1;
    double c1;

    std::shared_ptr<EngineData> dat;

};

class Compressor
{
public:
    Compressor( std::weak_ptr<EngineData> Dat );
    ~Compressor();
    void init_compressor();

    void update_compressor( double const p2_s, double const T2_s, const double c2 , double const n_wc, double const throttle  );

private:
    double p3_s;
    double sprezS_s;
    double n_zrS;
    double mS_zr;
    double mS;
    double eta_S;
    double T3_s;
    double A1_S , A2_II_S;
    double ro1_S , ro2_II_S;
    double sigma_s_wc;
    double c3;

    std::shared_ptr<EngineData> dat;
};

class CombustionChamber
{
public:
    CombustionChamber( std::weak_ptr<EngineData> Dat  );
    ~CombustionChamber() ;
    void init_combchamber();
    void update_comchamber( double const p3_s , double const T3_s ,
                                double const mS ,  double const c3,
                                double const throttle  );

private:
    double p4_s;
    double sig_34;
    double T4_s;
    double q_pal;
    double eta_ks;
    double W_opal;
    double Cp_wl;
    double m_ks;
    double c4;
    std::shared_ptr<EngineData> dat ;

};

class Turbine
{
public:
    Turbine( std::weak_ptr<EngineData> Dat  );
    ~Turbine();
    void init_turbine();

    void update_turbine( const double p4_s , double const T4_s ,
                                double const mS ,   double const c4 ,
                                double const n_wc);

    double get_T5_s() {return T5_s;  }
    double get_p5_s() {return p5_s;  }
    double get_m5() {return mT_wc; }
    double get_Pt() {return P_turbine; }
    double get_c5() { return  c5; }

private:
    double p5_s;
    double eta_Twc;
    double n_zrT_wc;
    double mTwc_zr;
    double nT_wc_s;
    double mT_wc;
    double T5_s;
    double P_turbine;
    double c5;
    std::shared_ptr<EngineData> dat ;
};

class Turbine_f
{
public:
    Turbine_f( std::weak_ptr<EngineData> Dat  );
    ~Turbine_f();

    void update_turbine_f( const double p5_s , double const T5_s ,
                           double const mS ,  double const c5 ,
                           double const n_wc );

    void init_turbine_f();

    double get_T6_s() { return  T6_s; }
    double get_p6_s() { return  p6_s; }
    double get_c6()   { return  c6;   }

private:
    double omega;
    double eta_T;
    double p6_s , T6_s , c6;
    double m6;

    std::shared_ptr<EngineData> dat;
};

class Engine
{
public:
    Engine( std::weak_ptr<EngineData> Dat );
    ~Engine();

    void init_Engine();
    void update( Atmosphere * );

private:
    std::shared_ptr<EngineData> dat;

};

typedef std::weak_ptr<Engine> Eptr;

class EngineBuilder
{
 public:
    virtual void BuildIntake(){}
    virtual void BuildFan(){}
    virtual void BuildCompressor(){}
    virtual void BuildCombustionChamber(){}
    virtual void BuildTurbine(){}
    virtual void BuildTurbineFree(){}

    virtual void BuildCanal(){}
    virtual void BuildDiffuzer(){}
    virtual void BuildAfterburner(){}

//    virtual Engine *GetEngine(){ return 0; }
    virtual Eptr GetEngine(){ return null;  }

protected:
    EngineBuilder();
    ~EngineBuilder() { cout << "~EngineBuilder Destructor -> " << null.use_count() << endl; }

private:
    Eptr null;


};

class EngineConstruct
{
public:
    EngineConstruct() {}

    Engine *CreateEngine( EngineBuilder &builder );

};


class TurboShaftEngine : public EngineBuilder
{
public:
    TurboShaftEngine();
    ~TurboShaftEngine() ;
    virtual void BuildIntake( );             // TH - T1
    virtual void BuildCompressor();          // T1 - T2
    virtual void BuildCombustionChamber(  ); // T2 - T3
    virtual void BuildTurbine( );            // T3 - T4
    virtual void BuildTurbineFree( );        // T4 - T5

//    virtual Engine *GetEngine(){ return  TurboShaftEng; }

    virtual Eptr GetEngine(){ return  TurboShaftEng; }


private:
    std::shared_ptr<Engine> TurboShaftEng;
    std::shared_ptr<EngineData> dat;

    std::shared_ptr<Intake>            intake;
    std::shared_ptr<Compressor>        compressor;
    std::shared_ptr<CombustionChamber> combchamber;
    std::shared_ptr<Turbine>           turbine;
    std::shared_ptr<Turbine_f>         turbine_f;

    struct Temp     { double TH  , T1s , T2s , T3s , T4s , T5s;  };
    struct Press    { double ph  , p1s , p2s , p3s , p4s , p5s;  };
    struct MassFlow { double mh  , m1  , m2  , m3  , m4  , m5;   };
    struct Speed    { double ch  , c1  , c2  , c3  , c4  , c5;   };

    Temp temp;
    Press press;
    MassFlow mS;
    Speed speed;

};




#endif // ENGINE_H
