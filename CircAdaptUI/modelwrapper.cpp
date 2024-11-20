#include "modelwrapper.h"
#include "settings.h"
#include <vector>
#include "Oxygen.hpp"

void ModelWrapper::buildModel()
{

// Systemic ArtVen
    // Create and link Components
    add_component("", "ArtVen", "CiSy");
    add_component("", "Tube0D", "SyArt");
    add_component("", "Tube0D", "SyVen");

    set_component("SyArt.adaptation_cavity", "CiSy");
    set_component("SyVen.adaptation_cavity", "CiSy");

    // Link objects
    set_component("CiSy.prox", "SyArt");
    set_component("CiSy.dist", "SyVen");


// Pulmonary ArtVen
    add_component("", "ArtVen", "CiPu");
    add_component("", "Tube0D", "PuArt");
    add_component("", "Tube0D", "PuVen");

    set_component("PuArt.adaptation_cavity", "CiPu");
    set_component("PuVen.adaptation_cavity", "CiPu");

// Link objects
    set_component("CiPu.prox", "PuArt");
    set_component("CiPu.dist", "PuVen");

// Parameterization
    std::vector<std::string> strings = {"SyArt", "SyVen", "PuArt", "PuVen"};
    std::vector<std::string> params = {"V", "A0", "A_wall", "k", "l", "p0", "scaleV"};
    std::vector<double> V = {2e-4, 2e-4, 1e-4, 2e-4};
    std::vector<double> A0 = {0.0004970825734583307, 0.0004992166387264159, 0.0004683231348739835, 0.0005138610352478564};
    std::vector<double> A_wall = {0.00011391746501259797, 4.59301961400394e-05, 8.830762085649456e-05, 4.837402180262195e-05};
    std::vector<double> k = {5.0 / 3.0, 7.0 / 3.0, 5.0 / 3.0, 7.0 / 3.0};
    std::vector<double> l = {0.4, 0.4, 0.2, 0.2};
    std::vector<double> p0 = {12166.38, 140.9967809576559, 2459.4806733964256, 505.49687688319267};
    std::vector<double> scaleV = {1e-5, 1e-5, 1e-5, 1e-5};
    std::vector<std::vector<double>> vectors = {V, A0, A_wall, k, l, p0, scaleV};

    for (size_t j = 0; j < params.size(); j++) {
        for (size_t i = 0; i < strings.size(); i++) {
            std::string loc = "Model." + strings[i] + "." + params[j];
            this->set_double(loc.c_str(), vectors[j][i]);
        }
    }

    strings = {"CiSy", "CiPu"};
    params = {"k", "p0", "q0"};
    p0 = {6550, 1500};
    std::vector<double> q0 = {4.5e-05, 4.5e-05};
    k = {1, 2};
    vectors = {k, p0, q0};
    for (size_t j = 0; j < params.size(); j++) {
        for (size_t i = 0; i < strings.size(); i++) {
            std::string loc = "Model." + strings[i] + "." + params[j];
            this->set_double(loc.c_str(), vectors[j][i]);
        }
    }

// Heart
    // Create components
    add_component("", "Bag", "Peri");

    // add atria
    add_component("Peri", "Chamber", "La");
    add_component("Peri.La.wLa", "Patch", "pLa0");
    add_component("Peri", "Chamber", "Ra");
    add_component("Peri.Ra.wRa", "Patch", "pRa0");

    // add ventricles
    add_component("Peri", "TriSeg", "TriSeg");
    add_component("Peri.TriSeg.wLv", "Patch", "pLv0");
    add_component("Peri.TriSeg.wSv", "Patch", "pSv0");
    add_component("Peri.TriSeg.wRv", "Patch", "pRv0");

    // add valves
    add_component("Peri", "Valve", "SyVenRa");
    add_component("Peri", "Valve", "RaRv");
    add_component("Peri", "Valve", "RvPuArt");
    add_component("Peri", "Valve", "PuVenLa");
    add_component("Peri", "Valve", "LaLv");
    add_component("Peri", "Valve", "LvSyArt");
    add_component("Peri", "Valve", "LaRa");
    add_component("Peri", "Valve", "LvRv");

    // Link components
    set_component("Peri.SyVenRa.prox", "SyVen");
    set_component("Peri.SyVenRa.dist", "Peri.Ra");
    set_component("Peri.RaRv.prox", "Peri.Ra");
    set_component("Peri.RaRv.dist", "Peri.TriSeg.cRv");
    set_component("Peri.RvPuArt.prox", "Peri.TriSeg.cRv");
    set_component("Peri.RvPuArt.dist", "PuArt");

    set_component("Peri.PuVenLa.prox", "PuVen");
    set_component("Peri.PuVenLa.dist", "Peri.La");
    set_component("Peri.LaLv.prox", "Peri.La");
    set_component("Peri.LaLv.dist", "Peri.TriSeg.cLv");
    set_component("Peri.LvSyArt.prox", "Peri.TriSeg.cLv");
    set_component("Peri.LvSyArt.dist", "SyArt");

    set_component("Peri.LaRa.prox", "Peri.La");
    set_component("Peri.LaRa.dist", "Peri.Ra");
    set_component("Peri.LvRv.prox", "Peri.TriSeg.cLv");
    set_component("Peri.LvRv.dist", "Peri.TriSeg.cRv");

    set_component("Peri.SyVenRa.adaptation_cavity", "SyVen");
    set_component("Peri.RaRv.adaptation_cavity", "PuArt");
    set_component("Peri.RvPuArt.adaptation_cavity", "PuArt");
    set_component("Peri.PuVenLa.adaptation_cavity", "PuVen");
    set_component("Peri.LaLv.adaptation_cavity", "SyArt");
    set_component("Peri.LvSyArt.adaptation_cavity", "SyArt");

    set_double("Model.Peri.TriSeg.V", 44e-6);
    set_double("Model.Peri.TriSeg.Y", 34.6e-3);

    set_double("Model.Peri.TriSeg.cLv.V",  100e-6);
    set_double("Model.Peri.TriSeg.cRv.V",  100e-6);
    set_double("Model.Peri.La.V",  50e-6);
    set_double("Model.Peri.Ra.V",  50e-6);

// Walmsley2015
    strings = {
        "Peri.TriSeg.wLv.pLv0",
        "Peri.TriSeg.wSv.pSv0",
        "Peri.TriSeg.wRv.pRv0",
        "Peri.La.wLa.pLa0",
        "Peri.Ra.wRa.pRa0"
    };
    for (auto string : strings)
    {
        set_double("Model."+string+".l_se0", 0.04);
        set_double("Model."+string+".l_s0", 2.0);
        set_double("Model."+string+".l_s0", 1.8);
        set_double("Model."+string+".dl_s_pas", 0.6);
        set_double("Model."+string+".k1", 10);
        set_double("Model."+string+".dt", 0);
        set_double("Model."+string+".C_rest", 0);
        set_double("Model."+string+".l_si0", 1.51);
        set_double("Model."+string+".LDAD", 1.057);
        set_double("Model."+string+".ADO", 0.65);
        set_double("Model."+string+".LDCC", 4);
    }
    set_double("Model.Peri.TriSeg.wLv.pLv0.Am_ref", 0.009805314057621018);
    set_double("Model.Peri.TriSeg.wLv.pLv0.V_wall", 9.60080108859341e-05);
    set_double("Model.Peri.TriSeg.wLv.pLv0.v_max", 7.0);
    set_double("Model.Peri.TriSeg.wLv.pLv0.Sf_pas", 500);
    set_double("Model.Peri.TriSeg.wLv.pLv0.tr", 0.25);
    set_double("Model.Peri.TriSeg.wLv.pLv0.td", 0.25);
    set_double("Model.Peri.TriSeg.wLv.pLv0.Sf_act", 100000);

    set_double("Model.Peri.TriSeg.wSv.pSv0.Am_ref", 0.004884229725474014);
    set_double("Model.Peri.TriSeg.wSv.pSv0.V_wall", 3.23553932981624e-05);
    set_double("Model.Peri.TriSeg.wSv.pSv0.v_max", 7.0);
    set_double("Model.Peri.TriSeg.wSv.pSv0.Sf_pas", 500);
    set_double("Model.Peri.TriSeg.wSv.pSv0.tr", 0.25);
    set_double("Model.Peri.TriSeg.wSv.pSv0.td", 0.25);
    set_double("Model.Peri.TriSeg.wSv.pSv0.Sf_act", 100000);

    set_double("Model.Peri.TriSeg.wRv.pRv0.Am_ref", 0.012970820071535782);
    set_double("Model.Peri.TriSeg.wRv.pRv0.V_wall", 6.29708653593736e-05);
    set_double("Model.Peri.TriSeg.wRv.pRv0.v_max", 7.0);
    set_double("Model.Peri.TriSeg.wRv.pRv0.Sf_pas", 500);
    set_double("Model.Peri.TriSeg.wRv.pRv0.tr", 0.25);
    set_double("Model.Peri.TriSeg.wRv.pRv0.td", 0.25);
    set_double("Model.Peri.TriSeg.wRv.pRv0.Sf_act", 100000);

    set_double("Model.Peri.La.wLa.pLa0.Am_ref", 0.006921646911242356);
    set_double("Model.Peri.La.wLa.pLa0.Am_ref", 0.007);
    set_double("Model.Peri.La.wLa.pLa0.V_wall", 1.5582632867621123e-05);
    set_double("Model.Peri.La.wLa.pLa0.V_wall", 1.6e-05);
    set_double("Model.Peri.La.wLa.pLa0.v_max", 14.0);
    set_double("Model.Peri.La.wLa.pLa0.Sf_pas", 4000);
    set_double("Model.Peri.La.wLa.pLa0.tr", 0.4);
    set_double("Model.Peri.La.wLa.pLa0.td", 0.4);
    set_double("Model.Peri.La.wLa.pLa0.Sf_act", 84000);

    set_double("Model.Peri.Ra.wRa.pRa0.Am_ref", 0.0059862195992063825);
    set_double("Model.Peri.Ra.wRa.pRa0.Am_ref", 0.008);
    set_double("Model.Peri.Ra.wRa.pRa0.V_wall", 6.389451836068464e-05);
    set_double("Model.Peri.Ra.wRa.pRa0.V_wall", 1e-05);
    set_double("Model.Peri.Ra.wRa.pRa0.v_max", 14.0);
    set_double("Model.Peri.Ra.wRa.pRa0.Sf_pas", 4000);
    set_double("Model.Peri.Ra.wRa.pRa0.tr", 0.4);
    set_double("Model.Peri.Ra.wRa.pRa0.td", 0.4);
    set_double("Model.Peri.Ra.wRa.pRa0.Sf_act", 84000);

// Timings
    add_component("", "Timings", "Timings");

    set_component("Timings.wLa", "Peri.La.wLa");
    set_component("Timings.wRa", "Peri.Ra.wRa");
    set_component("Timings.wLv", "Peri.TriSeg.wLv");
    set_component("Timings.wSv", "Peri.TriSeg.wSv");
    set_component("Timings.wRv", "Peri.TriSeg.wRv");

// PFC
    add_component("", "PressureFlowControl", "PFC");

    set_component("PFC.node_pressure", "SyArt");
    set_component("PFC.connector_return", "Peri.SyVenRa");
    set_component("PFC.artven_resistance", "CiSy");
    set_component("PFC.valve_flow_vec", "Peri.SyVenRa");
    set_component("PFC.valve_flow_vec", "Peri.RaRv");
    set_component("PFC.valve_flow_vec", "Peri.RvPuArt");
    set_component("PFC.valve_flow_vec", "Peri.PuVenLa");
    set_component("PFC.valve_flow_vec", "Peri.LaLv");
    set_component("PFC.valve_flow_vec", "Peri.LvSyArt");
    set_component("PFC.valve_flow_vec", "Peri.LaRa");
    set_component("PFC.valve_flow_vec", "Peri.LvRv");
    set_component("PFC.link_fac_pfc", "CiSy");
    set_component("PFC.link_fac_pfc", "CiPu");

    set_component("PFC.circulation_volume_object", "SyArt");
    set_component("PFC.circulation_volume_object", "SyVen");
    set_component("PFC.circulation_volume_object", "PuArt");
    set_component("PFC.circulation_volume_object", "PuVen");
    set_component("PFC.circulation_volume_object", "Peri.La");
    set_component("PFC.circulation_volume_object", "Peri.Ra");
    set_component("PFC.circulation_volume_object", "Peri.TriSeg.cLv");
    set_component("PFC.circulation_volume_object", "Peri.TriSeg.cRv");

// Papillary muscles
    set_component("Peri.RaRv.wPapMus", "Peri.TriSeg.wRv");
    set_component("Peri.LaLv.wPapMus", "Peri.TriSeg.wLv");


// Oxygen model
    factory->register_component<CAcore::Components::Oxygen>("Oxygen");
    add_component("", "Oxygen", "Oxygen");
    set_component("Oxygen.max_saturation", "PuVen");
    set_component("Oxygen.connector", "Peri.SyVenRa");
    set_component("Oxygen.connector", "Peri.RaRv");
    set_component("Oxygen.connector", "Peri.RvPuArt");
    set_component("Oxygen.connector", "Peri.PuVenLa");
    set_component("Oxygen.connector", "Peri.LaLv");
    set_component("Oxygen.connector", "Peri.LvSyArt");
    set_component("Oxygen.connector", "Peri.LaRa");
    set_component("Oxygen.connector", "Peri.LvRv");
    set_component("Oxygen.connector", "CiPu");
    set_component("Oxygen.connector", "CiSy");

}


void ModelWrapper::setReferenceParameters()
{
// Parameterization
    set_bool("Model.Peri.La.buckling", true);
    set_bool("Model.Peri.Ra.buckling", true);

    std::vector<std::string> strings = { "SyVenRa", "RaRv", "RvPuArt", "PuVenLa", "LaLv", "LvSyArt", "LaRa", "LvRv" };
    std::vector<std::string> params = {"soft_closure", "papillary_muscles"};
    std::vector<bool> soft_closure = { true, true, true, true, true, true, true, true };
    std::vector<bool> papillary_muscles = { false, false, false, false, false, false, false, false };

    std::vector<std::vector<bool>> boolvectors = {soft_closure, papillary_muscles};
    for (size_t j = 0; j < params.size(); j++) {
        for (size_t i = 0; i < strings.size(); i++) {
            std::string loc = "Model.Peri." + strings[i] + "." + params[j];
            this->set_bool(loc.c_str(), boolvectors[j][i]);
        }
    }

    set_double("Solver.dt", 0.001);
    set_double("Solver.dt_export", 0.002);
    set_int("Solver.order", 2);

    set_double("Model.t_cycle", 0.85);

    strings = {"CiSy", "CiPu"};
    params = {"p0", "q0", "k"};
    std::vector<double> p0 = {6306.25831487, 1000};
    std::vector<double> q0 = {4.5e-05, 4.5e-05};
    std::vector<double> k = {1.0, 2.0};
    std::vector<std::vector<double>> vectors = {p0, q0, k};
    for (size_t j = 0; j < params.size(); j++) {
        for (size_t i = 0; i < strings.size(); i++) {
            std::string loc = "Model." + strings[i] + "." + params[j];
            this->set_double(loc.c_str(), vectors[j][i]);
        }
    }

    strings = {"SyArt", "SyVen", "PuArt", "PuVen"};
    params = {"l", "A_wall", "k", "p0", "A0", "target_wall_stress", "target_mean_flow"};
    std::vector<double> l = {0.4, 0.4, 0.2, 0.2};
    std::vector<double> A_wall = {1.12362733e-04, 6.57883944e-05, 9.45910889e-05, 8.22655361e-05};
    k = {1.66666667, 2.33333333, 1.66666667, 2.33333333};
    p0 = {12162.50457811,   287.7083132 ,  2132.51755623,   830.54673184};
    std::vector<double> A0 = {0.0004983 , 0.00049909, 0.00047138, 0.00050803};
    std::vector<double> target_wall_stress = {500000., 500000., 500000., 500000.};
    std::vector<double> target_mean_flow = {0.17, 0.17, 0.17, 0.17};
    vectors = {l, A_wall, k, p0, A0, target_wall_stress, target_mean_flow};

    for (size_t j = 0; j < params.size(); j++) {
        for (size_t i = 0; i < strings.size(); i++) {
            std::string loc = "Model." + strings[i] + "." + params[j];
            this->set_double(loc.c_str(), vectors[j][i]);
        }
    }

    set_double("Model.Peri.k", 10.0);
    set_double("Model.Peri.p_ref", 1000.0);
    set_double("Model.Peri.V_ref", 0.00054267);

    strings = {"La.wLa.pLa0", "Ra.wRa.pRa0", "TriSeg.wLv.pLv0", "TriSeg.wRv.pRv0", "TriSeg.wSv.pSv0"};
    params = {"Am_ref", "V_wall", "v_max", "l_se0", "l_s0", "l_s_ref", "dl_s_pas", "Sf_pas",
               "tr", "td", "time_act", "Sf_act", "fac_Sf_tit", "k1", "dt", "C_rest", "l_si0",
               "LDAD", "ADO", "LDCC", "SfPasMaxT", "SfPasActT", "FacSfActT", "LsPasActT", "adapt_gamma",
               "transmat00", "transmat01", "transmat02", "transmat03",
               "transmat10", "transmat11", "transmat12", "transmat13",
              "transmat20", "transmat21", "transmat22", "transmat23"};
    std::vector<double> Am_ref = {0.00425687, 0.00401573, 0.00966859, 0.01084227, 0.00289936};
    std::vector<double> V_wall = {4.46069398e-06, 2.14548521e-06, 7.35720515e-05, 3.67720116e-05, 1.88904978e-05};
    std::vector<double> v_max = {14., 14.,  7.,  7.,  7.};
    std::vector<double> l_se0 = {0.04, 0.04, 0.04, 0.04, 0.04};
    std::vector<double> l_s0 = {1.8, 1.8, 1.8, 1.8, 1.8};
    std::vector<double> l_s_ref = {2., 2., 2., 2., 2.};
    std::vector<double> dl_s_pas = {0.6, 0.6, 0.6, 0.6, 0.6};
    std::vector<double> Sf_pas = {2248.53598   , 2684.76100348,  731.24545453,  749.47694522, 729.06063771};
    std::vector<double> tr = {0.4 , 0.4 , 0.25, 0.25, 0.25};
    std::vector<double> td = {0.4 , 0.4 , 0.25, 0.25, 0.25};
    std::vector<double> time_act = {0.15 , 0.15 , 0.425, 0.425, 0.425};
    std::vector<double> Sf_act = { 84000.,  84000., 120000., 120000., 120000.};
    std::vector<double> fac_Sf_tit = {0.01, 0.01, 0.01, 0.01, 0.01};
    std::vector<double> k1 = {10., 10., 10., 10., 10.};
    std::vector<double> dt = {0., 0., 0., 0., 0.};
    std::vector<double> C_rest = {0., 0., 0., 0., 0.};
    std::vector<double> l_si0 = {1.51, 1.51, 1.51, 1.51, 1.51};
    std::vector<double> LDAD = {1.057, 1.057, 1.057, 1.057, 1.057};
    std::vector<double> ADO = {0.65, 0.65, 0.65, 0.65, 0.65};
    std::vector<double> LDCC = {4., 4., 4., 4., 4.};
    std::vector<double> SfPasMaxT = {320000., 320000.,  16000.,  16000.,  16000.};
    std::vector<double> SfPasActT = {40000., 40000., 20000., 20000., 20000.};
    std::vector<double> FacSfActT = {0.8, 0.8, 1. , 1. , 1. };
    std::vector<double> LsPasActT = {2.42, 2.42, 2.42, 2.42, 2.42};
    std::vector<double> adapt_gamma = {0.5, 0.5, 0.5, 0.5, 0.5};
    std::vector<double> transmat00 = {-0.5751, -0.5751, -0.5751, -0.5751, -0.5751};
    std::vector<double> transmat01 = {-0.7851, -0.7851, -0.7851, -0.7851, -0.7851};
    std::vector<double> transmat02 = {0.6063, 0.6063, 0.6063, 0.6063, 0.6063};
    std::vector<double> transmat03 = {-0.5565, -0.5565, -0.5565, -0.5565, -0.5565};
    std::vector<double> transmat10 = {-0.1279, -0.1279, -0.1279, -0.1279, -0.1279};
    std::vector<double> transmat11 = {0.0999, 0.0999, 0.0999, 0.0999, 0.0999};
    std::vector<double> transmat12 = {0.2066, 0.2066, 0.2066, 0.2066, 0.2066};
    std::vector<double> transmat13 = {-1.8441, -1.8441, -1.8441, -1.8441, -1.8441};
    std::vector<double> transmat20 = {-0.1865, -0.1865, -0.1865, -0.1865, -0.1865};
    std::vector<double> transmat21 = {-0.201, -0.201, -0.201, -0.201, -0.201};
    std::vector<double> transmat22 = {1.3195, 1.3195, 1.3195, 1.3195, 1.3195};
    std::vector<double> transmat23 = {-11.8745, -11.8745, -11.8745, -11.8745, -11.8745};
    vectors = {Am_ref, V_wall, v_max, l_se0, l_s0, l_s_ref, dl_s_pas, Sf_pas,
              tr, td, time_act, Sf_act, fac_Sf_tit, k1, dt, C_rest, l_si0,
              LDAD, ADO, LDCC, SfPasMaxT, SfPasActT, FacSfActT, LsPasActT, adapt_gamma,
              transmat00, transmat01, transmat02, transmat03,
              transmat10, transmat11, transmat12, transmat13,
              transmat20, transmat21, transmat22, transmat23};

    for (size_t j = 0; j < params.size(); j++) {
        for (size_t i = 0; i < strings.size(); i++) {
            std::string loc = "Model.Peri." + strings[i] + "." + params[j];
            this->set_double(loc.c_str(), vectors[j][i]);
        }
    }

    strings = { "SyVenRa", "RaRv", "RvPuArt", "PuVenLa", "LaLv", "LvSyArt", "LaRa", "LvRv" };
    params = {"adaptation_A_open_fac", "A_open", "A_leak", "l", "L_fac_prox",
               "L_fac_dist", "L_fac_valve", "rho_b", "papillary_muscles_slope",
              "papillary_muscles_min", "papillary_muscles_A_open_fac",
              "fraction_A_open_Aext"};
    std::vector<double> adaptation_A_open_fac = {1., 1., 1., 1., 1., 1., 1., 1.};
    std::vector<double> A_open = {0.00049916, 0.00047155, 0.00047155, 0.00050805, 0.00049835, 0.00049835, 1e-9, 1e-9};
    std::vector<double> A_leak = {0.00049916, 1.e-09, 1.e-09, 0.00050805, 1.e-09, 1.e-09, 1e-9, 1e-9};
    l = {0.01260512, 0.01225144, 0.01225144, 0.01271679, 0.01259479, 0.01259479, 0.01259479, 0.01259479};
    std::vector<double> L_fac_prox = {0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75};
    std::vector<double> L_fac_dist = {0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75};
    std::vector<double> L_fac_valve = {1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5};
    std::vector<double> rho_b = {1050., 1050., 1050., 1050., 1050., 1050., 1050, 1050};
    std::vector<double> papillary_muscles_slope = {100., 100., 100., 100., 100., 100., 100., 100.};
    std::vector<double> papillary_muscles_min = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    std::vector<double> papillary_muscles_A_open_fac = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    std::vector<double> fraction_A_open_Aext = {0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9};
    vectors = {adaptation_A_open_fac, A_open, A_leak, l, L_fac_prox,
              L_fac_dist, L_fac_valve, rho_b, papillary_muscles_slope,
              papillary_muscles_min, papillary_muscles_A_open_fac,
              fraction_A_open_Aext};

    for (size_t j = 0; j < params.size(); j++) {
        for (size_t i = 0; i < strings.size(); i++) {
            std::string loc = "Model.Peri." + strings[i] + "." + params[j];
            this->set_double(loc.c_str(), vectors[j][i]);
        }
    }

    params = {"soft_closure", "papillary_muscles"};
    soft_closure = { true,  true,  true,  true,  true,  true, true, true};
    papillary_muscles = {false, false, false, false, false, false, false, false};
    boolvectors =  {soft_closure, papillary_muscles};

    for (size_t j = 0; j < params.size(); j++) {
        for (size_t i = 0; i < strings.size(); i++) {
            std::string loc = "Model.Peri." + strings[i] + "." + params[j];
            this->set_bool(loc.c_str(), boolvectors[j][i]);
        }
    }
    set_double("Model.Timings.time_fac", 1.0);
    set_double("Model.Timings.tau_av", 0.150025);
    set_double("Model.Timings.dtau_av", 0);
    set_int("Model.Timings.law_tau_av", 1);
    set_int("Model.Timings.law_Ra2La", 1);
    set_int("Model.Timings.law_ta", 1);
    set_int("Model.Timings.law_tv", 1);
    set_double("Model.Timings.c_tau_av0", 0.);
    set_double("Model.Timings.c_tau_av1", 0.1765);
    set_double("Model.Timings.c_ta_rest", 0.);
    set_double("Model.Timings.c_ta_tcycle", 0.17647059);
    set_double("Model.Timings.c_tv_rest", 0.1);
    set_double("Model.Timings.c_tv_tcycle", 0.4);

    set_double("Model.PFC.p0", 12200.);
    set_double("Model.PFC.q0", 8.5e-05);
    set_double("Model.PFC.stable_threshold", 0.0001);
    set_bool("Model.PFC.is_active", true);
    set_double("Model.PFC.fac", 1.);
    set_double("Model.PFC.fac_pfc", 1.);
    set_double("Model.PFC.epsilon", 0.4);
    set_double("Model.Peri.TriSeg.tau", 2.);
    set_double("Model.Peri.TriSeg.ratio_septal_LV_Am", 0.3);
    set_double("Model.Peri.TriSeg.max_number_of_iterations", 100);
    set_double("Model.Peri.TriSeg.thresh_F", 0.001);
    set_double("Model.Peri.TriSeg.thresh_dV", 1e-9);
    set_double("Model.Peri.TriSeg.thresh_dY", 1e-6);
    //
    set_int("Model.Peri.TriSeg.wLv.n_patch", 11);
    set_int("Model.Peri.TriSeg.wSv.n_patch", 5);
    set_int("Model.Peri.TriSeg.wRv.n_patch", 7);
    run_stable();

    double circulation_volume;
    get_double("Model.PFC.circulation_volume", circulation_volume);
    set_double("Model.PFC.target_volume", circulation_volume);

}

void ModelWrapper::run_steps()
{
    int bufferLen = buffer.getLen();
    int bufferSize = Settings::instance().buffersize();
    for (int i = bufferLen; i < bufferSize; i++)
    {
        run_single_step();
    }
}

void ModelWrapper::run_beats(int N_beats)
{
    int beat_idx = 0;
    do
    {
        run_single_step();

        if (beatDone == true)
        {
            beat_idx += 1;
        }

    } while (beat_idx < N_beats);

}

void ModelWrapper::run_single_step() {
    size_t nt = ((size_t)(model->get_t_cycle() / solver->get_dt_export()));
    if (it == -1) {
        solver->pre_beat();
        solver->init_iteration();
        it++;
        beatDone = false;
    }
    else {
        t_export = (it + 1) * solver->get_dt_export();
        solver->stepper(t_export, true);

        model->true_iteration(t_export, solver->get_dt_export());

        it++;
    }
    if (it >= nt)
    {
        solver->after_beat();
        Settings::instance().beatIdxIncrement();
        it = -1;
        beatDone = true;
        emit beat_done();
    }
    updateBuffer();
    emit timestep_done();
}

void ModelWrapper::setup()
{
    build("Custom", "backward_differential");
    buildModel();
    setReferenceParameters();
    setupSignals();
    setupParameters();
    init_SVar();
    m_thread.reset(new QThread);
    m_thread->setObjectName("Simulation thread");
    moveToThread(m_thread.get());
    m_thread->start();
#ifdef QT_NO_DEBUG
    run_stable();
#endif
    run_beats(2);
    emit setup_done();
}

void ModelWrapper::setupSignals()
{
    QJsonArray signalArray = Settings::instance().ExportSignals();
    mModelSignals.reserve(signalArray.size());
    for (auto s : signalArray)
    {
        mModelSignals.push_back(DataContainerFactory::createSignal(s.toObject(), this));

    }
}

void ModelWrapper::setupParameters()
{
    QJsonArray paramArray = Settings::instance().ExportParameters();
    mModelSignals.reserve(paramArray.size());
    for (auto s : paramArray)
    {
        QJsonObject obj = s.toObject();
        double d = qQNaN();
        if (obj["type"].toString() != "bool")
            get_double(obj["path"].toString().toStdString(), d);
        obj["default"] = d;
        mModelParameters[s.toObject()["name"].toString()] = DataContainerFactory::createSignal(obj, this);

    }

    double val;
    get_double("Model.Peri.TriSeg.wLv.V_wall", val);
    buffer.modelParams["V_wall_Lv"] = val;
    get_double("Model.Peri.TriSeg.wSv.V_wall", val);
    buffer.modelParams["V_wall_Sv"] = val;
    get_double("Model.Peri.TriSeg.wRv.V_wall", val);
    buffer.modelParams["V_wall_Rv"] = val;

}

void ModelWrapper::updateBuffer()
{
    double val{};
    bool success;
    buffer.lock();
    for (auto s : mModelSignals)
    {
        s->updateBuffer(buffer);
    }
    buffer.append("t", solver->get_t());
    buffer.postprocessing();

    if (beatDone)
    {
        buffer.runAfterBeat();
    }
    buffer.unlock();

}

void ModelWrapper::updateParam(const QString& name, const QVariant& value)
{
    mModelParameters[name]->updateParam(value);
}

void ModelWrapper::reset()
{
    solver->clear_SVar();
    it = -1;

    set_int("Model.Peri.TriSeg.wLv.n_patch", 1);
    set_int("Model.Peri.TriSeg.wSv.n_patch", 1);
    set_int("Model.Peri.TriSeg.wRv.n_patch", 1);

    setReferenceParameters();

    set_int("Model.Peri.TriSeg.wLv.n_patch", 11);
    set_int("Model.Peri.TriSeg.wSv.n_patch", 5);
    set_int("Model.Peri.TriSeg.wRv.n_patch", 7);

    init_SVar();
    run_stable();
    run_beats(2);
    Settings::instance().setBeatIdx(0);

    emit setup_done();
}
