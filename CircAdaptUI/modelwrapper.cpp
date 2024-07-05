#include "modelwrapper.h"
#include "settings.h"
#include <vector>

void ModelWrapper::set_model_state() {
    this->set_bool("Model.Peri.La.buckling", false);
    this->set_bool("Model.Peri.Ra.buckling", false);

    this->set_double("Solver.dt", 0.001);
    this->set_double("Solver.dt_export", 0.002);
    this->set_double("Solver.order", 2);

    this->set_double("Model.t_cycle", 0.85);

    this->set_double("Model.PFC.fac", 0.5);
    this->set_double("Model.PFC.epsilon", 0.1);
    this->set_double("Model.PFC.fac_pfc", 1);
    this->set_double("Model.PFC.stable_threshold", 0.001);

    std::vector<std::string> strings = {"SyArt", "SyVen", "PuArt", "PuVen"};
    std::vector<std::string> params = {"A0", "A_wall", "k", "l", "p0", "V"};
    std::vector<double> A0 = {0.00049828, 0.00049899, 0.00046929, 0.00050574};
    std::vector<double> A_Wall = {1.13187792e-04, 3.72289316e-05, 7.27489286e-05, 4.31617949e-05};
    std::vector<double> k = {1.66666667, 2.33333333, 1.66666667, 2.33333333};
    std::vector<double> l = {0.4, 0.4, 0.19, 0.19};
    std::vector<double> p0 = {12155.25602777,   297.44066943,  1912.6684696 ,   580.51425824};
    std::vector<double> V = {2e-4,   4e-4,  1e-4 ,   2e-4};
    std::vector<std::vector<double>> vectors = {A0, A_Wall, k, l, p0, V};

    for (size_t j = 0; j < params.size(); j++) {
        for (size_t i = 0; i < strings.size(); i++) {
            std::string loc = "Model." + strings[i] + "." + params[j];
            this->set_double(loc.c_str(), vectors[j][i]);
        }
    }


    strings = {"CiSy", "CiPu"};
    params = {"p0", "q0", "k"};
    p0 = {6299.86481149, 1000};
    std::vector<double> q0 = {4.5e-05, 4.5e-05};
    k = {1, 1.88};
    vectors = {p0, q0, k};
    for (size_t j = 0; j < params.size(); j++) {
        for (size_t i = 0; i < strings.size(); i++) {
            std::string loc = "Model." + strings[i] + "." + params[j];
            this->set_double(loc.c_str(), vectors[j][i]);
        }
    }

    this->set_double("Model.Peri.TriSeg.V", 56e-6);
    this->set_double("Model.Peri.TriSeg.Y", 36e-3);
    this->set_double("Model.Peri.TriSeg.cLv.V", 150e-6);
    this->set_double("Model.Peri.TriSeg.cRv.V", 110e-6);
    this->set_double("Model.Peri.La.V", 25e-6);
    this->set_double("Model.Peri.Ra.V", 150e-6);

    strings = {"La.wLa.pLa1", "Ra.wRa.pRa1", "TriSeg.wLv.pLv1", "TriSeg.wSv.pSv1", "TriSeg.wRv.pRv1"};
    params = {"l_se0", "l_s_ref", "l_s0", "dl_s_pas", "k1", "dt", "C_rest", "l_si0", "LDAD", "ADO", "LDCC", "v_max", "tr", "td", "Sf_act", "Am_ref", "V_wall", "Sf_pas"};
    std::vector<double> l_se0 = {0.04, 0.04, 0.04, 0.04, 0.04};
    std::vector<double> l_s_ref = {2, 2, 2, 2, 2};
    std::vector<double> l_s0 = {1.79, 1.79, 1.8, 1.8, 1.8};
    std::vector<double> dl_s_pas = {0.6, 0.6, 0.6, 0.6, 0.6};
    std::vector<double> k1 = {10, 10, 10, 10, 10};
    std::vector<double> dt = {0, 0, 0, 0, 0};
    std::vector<double> C_rest = {0, 0, 0, 0, 0};
    std::vector<double> l_si0 = {1.51, 1.51, 1.51, 1.51, 1.51};
    std::vector<double> LDAD = {1.057, 1.057, 0.74, 0.74, 0.74};
    std::vector<double> ADO = {0.081, 0.081, 0.75, 0.75, 0.75};
    std::vector<double> LDCC = {4, 4, 3, 3, 3};
    std::vector<double> v_max = {14, 14, 7, 7, 7};
    std::vector<double> tr = {0.4, 0.4, 0.21, 0.21, 0.21};
    std::vector<double> td = {0.4, 0.4, 0.24, 0.24, 0.24};
    std::vector<double> Sf_act = {100000, 100000, 120000, 120000, 120000};
    std::vector<double> Am_ref = {0.00400721, 0.00311263, 0.00918281, 0.00518683, 0.01321999};
    std::vector<double> V_wall = {1.59935455e-05, 7.72140495e-06, 1.16441768e-04, 4.51241560e-05, 6.88196851e-05};
    std::vector<double> Sf_pas = {9.51064014,  10.3647024 , 424.3537027 , 417.74300178,439.21574206};
    vectors = {l_se0, l_s_ref, l_s0, dl_s_pas, k1, dt, C_rest, l_si0, LDAD, ADO, LDCC, v_max, tr, td, Sf_act, Am_ref, V_wall, Sf_pas};

    for (size_t j = 0; j < params.size(); j++) {
        for (size_t i = 0; i < strings.size(); i++) {
            std::string loc = "Model.Peri." + strings[i] + "." + params[j];
            this->set_double(loc.c_str(), vectors[j][i]);
        }
    }


    strings = {"SyVenRa", "RaRv", "RvPuArt", "PuVenLa", "LaLv", "LvSyArt"};
    params = {"adaptation_A_open_fac", "A_open", "A_leak", "l", "rho_b", "papillary_muscles_slope", "papillary_muscles_min", "papillary_muscles_A_open_fac"};
    std::vector<double> adaptation_A_open_fac = {1, 1.12, 1, 1, 1.12, 1};
    std::vector<double> A_open = {0.00050044, 0.00052598, 0.00046962, 0.00050745, 0.0005583 ,0.00049849};
    std::vector<double> A_leak = {2.64705882e-04, 2.64705882e-10, 2.64705882e-10, 2.64705882e-04,2.64705882e-10, 2.64705882e-10};
    l = {0.01626978, 0.01626978, 0.01626978, 0.01626978, 0.01626978, 0.01626978};
    std::vector<double> rho_b = {1050, 1050, 1050, 1050, 1050, 1050};
    std::vector<double> papillary_muscles_slope = {100, 100, 100, 100, 100, 100};
    std::vector<double> papillary_muscles_min = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    std::vector<double> papillary_muscles_A_open_fac = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    vectors = {adaptation_A_open_fac, A_open, A_leak, l, rho_b, papillary_muscles_slope, papillary_muscles_min, papillary_muscles_A_open_fac};

    for (size_t j = 0; j < params.size(); j++) {
        for (size_t i = 0; i < strings.size(); i++) {
            std::string loc = "Model.Peri." + strings[i] + "." + params[j];
            this->set_double(loc.c_str(), vectors[j][i]);
        }
    }

    std::vector<bool> papillary_muscles = {true, true, true, true, true, true};
    std::vector<bool> soft_closure = {true, true, true, true, true, true};
    params = {"papillary_muscles", "soft_closure"};
    std::vector<std::vector<bool>> vectors_bool = {papillary_muscles, soft_closure};
    for (size_t j = 0; j < params.size(); j++) {
        for (size_t i = 0; i < strings.size(); i++) {
            std::string loc = "Model.Peri." + strings[i] + "." + params[j];
            this->set_bool(loc.c_str(), vectors_bool[j][i]);
        }
    }

    this->set_double("Model.Peri.k", 10);
    this->set_double("Model.Peri.V_ref", 0.00057937);
    this->set_double("Model.Peri.p_ref", 100);

    this->set_double("Model.Peri.TriSeg.Y", 0.035);

    this->set_double("Model.Timings.law_tau_av", 2);
    this->set_double("Model.Timings.c_tau_av0", 0.189);
    this->set_double("Model.Timings.c_tau_av1", -0.029);

    this->set_double("Solver.store_beats", 1);


    // # Adaptation
    //           self['Patch']['adapt_gamma'] = 0.5
    //           self.set('Solver.store_beats', 1)

    //           self['PFC']['stable_threshold'] = 1e-3

    //         self['Patch']['SfPasMaxT'] = [3600., 3600.,  4200.,  4200.,  4200.]
    //         self['Patch']['FacSfActT'] = [0.28, 0.28, 0.69, 0.69, 0.69]
    //         self['Patch']['SfPasActT'] = [2800., 2800., 6600., 6600., 6600.]
    //         self['Patch']['LsPasActT'] = [3.  , 3.  , 2.31, 2.31, 2.31]

}

void ModelWrapper::run_steps()
{

    for (int i = buffer.getLen(); i < Settings::instance().buffersize(); i++)
    {
        run_single_step();
    }
}

void ModelWrapper::run_single_step() {
    size_t nt = ((size_t)(model->get_t_cycle() / solver->get_dt_export()));
    if (it == 0) {
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
        it = 0;
        beatDone = true;
    }
    updateBuffer();
    emit timestep_done();
}

void ModelWrapper::changeParam(int val)
{
    double Sf_act;
    get_double("Model.Peri.TriSeg.wLv.pLv1.Sf_act", Sf_act);
    set_double("Model.Peri.TriSeg.wLv.pLv1.Sf_act", 120000 * val / 100);
}

void ModelWrapper::setup()
{
    setupSignals();
    build("VanOsta2022", Settings::instance().MWSettings()["solver"].toString().toStdString());
    set_model_state();
    init_SVar();
    m_thread.reset(new QThread);
    m_thread->setObjectName("Simulation thread");
    moveToThread(m_thread.get());
    m_thread->start();
    run_steps();
}

void ModelWrapper::setupSignals()
{
    QJsonArray signalArray = Settings::instance().ExportSignals();
    mModelSignals.reserve(signalArray.size());
    for (auto s : signalArray)
    {
        mModelSignals.push_back(DataContainerFactory::createSignal(s.toObject()));

    }
}

void ModelWrapper::updateBuffer()
{
    double val{};
    for (auto s : mModelSignals)
    {
        get_double(s->getPath().toStdString(), val);
        buffer.append(s->getName(), s->convert(val));
    }
    buffer.append("t", solver->get_t());

    get_double("Model.PFC.cumulative_flow_beat", val);
    buffer.append("ven_ret", val*60000);

    if (beatDone)
    {
        buffer.runAfterBeat();
    }

}
