#include "buffer.h"
#include <QVariant>

Buffer::Buffer()
{
    m_beatData.reserve(2);

}

void Buffer::append(const QString& string, double value)
{
    m_data[string].append(value);
    m_currentBeatData[string].append(value);
}

double Buffer::get(const QString& string)
{
    return m_data[string].first();
}

QVector<double> Buffer::get(const QString& string, double dt)
{
    int count = 0;
    QVector<double>& vec = m_data[string];
    if (!vec.empty())
    {
        for (int i = 0; i < m_data["t"].size(); i++)
        {
            if (qAbs(m_data["t"][i] - m_data["t"][0]) <= dt)
            {
                ++count;
            }
            else break;
        }

        QVector<double> out;
        out.reserve(count);
        std::copy(vec.begin(), vec.begin() + count, std::back_inserter(out));
        return out;
    }
    else
    {
        throw std::range_error(string.toStdString() + " buffer empty!");
    }
}

void Buffer::clear(double dt)
{
    QMutexLocker l(&mutex);
    int count = 0;
    for (int i = 0; i < m_data["t"].size(); i++)
    {
        if (qAbs(m_data["t"][i] - m_data["t"][0]) <= dt)
        {
            count++;
        }
        else break;
    }

    for (auto [key, vec] : m_data.asKeyValueRange())
    {
        vec.erase(vec.cbegin(), vec.cbegin() + count);
    }
}

void Buffer::clear(int count)
{
    for (auto [key, vec] : m_data.asKeyValueRange())
    {
        vec.erase(vec.cbegin(), vec.cbegin() + count);
    }
}

void Buffer::clear()
{
    QMutexLocker l(&mutex);
    for (auto [key, vec] : m_data.asKeyValueRange())
    {
        vec.clear();
    }
    for (auto [key, vec] : m_currentBeatData.asKeyValueRange())
    {
        vec.clear();
    }
    while (m_beatData.count())
        delete m_beatData.takeLast();
}

void Buffer::runAfterBeat()
{
    if (m_beatData.count() >= 2)
        m_beatData.first()->setData(m_beatData.last()->getData());
    else
    {
        m_beatData.emplaceBack(new BeatData(this));
    }
    m_beatData.last()->setData(m_currentBeatData);
    m_currentBeatData.clear();

    emit updateValueView(m_beatData.last()->getStats());
}

const QVector<double> Buffer::getSnapshot(const QString& key) const
{
    QVector<double> data;
    if (key != "t")
    {
        for (auto elem : m_beatData)
        {
            data += elem->get(key);
        }
    }
    else
    {
        for (auto elem : m_beatData)
        {
            if (data.isEmpty())
            {
                data += elem->get(key);
            }
            else {
                double last = data.last();
                for (auto x : elem->get(key))
                {
                    data.push_back(last + x);
                }
            }
        }
    }
    return data;
}

void Buffer::postprocessing()
{
    calculateMMode();
    calculateEngineeringStrain();
    calculateAverageWallStress();
}

void Buffer::calculateMMode()
{
    double Am_Lv = 10000 * m_data["Am_Lv"].last();
    double Am_Sv = 10000 * m_data["Am_Sv"].last();
    double Am_Rv = 10000 * m_data["Am_Rv"].last();
    double Cm_Lv = - m_data["Cm_Lv"].last() / 100;
    double Cm_Sv = m_data["Cm_Sv"].last() / 100; // May be +ve or -ve
    double Cm_Rv = m_data["Cm_Rv"].last() / 100;
    double Xm_Lv = -100 * m_data["Xm1"].last();
    double Xm_Sv = 100 * m_data["Xm2"].last();
    double Xm_Rv = 100 * m_data["Xm3"].last();
    double Vw_Lv = modelParams["V_wall_Lv"].toDouble() * 1e6;
    double Vw_Sv = modelParams["V_wall_Sv"].toDouble() * 1e6;
    double Vw_Rv = modelParams["V_wall_Rv"].toDouble() * 1e6;
    double dsv = Vw_Sv / Am_Sv;

    double ratio_Lv = Am_Lv * ( Cm_Lv * Cm_Lv ) / ( 4 * M_PI );
    double ratio_Sv = Am_Sv * ( Cm_Sv * Cm_Sv ) / ( 4 * M_PI );
    double ratio_Rv = Am_Rv * ( Cm_Rv * Cm_Rv ) / ( 4 * M_PI );
    double Vw_s_Lv = Vw_Lv / ratio_Lv;
    double Vw_s_Sv = Vw_Sv / ratio_Sv;
    double Vw_s_Rv = Vw_Rv / ratio_Rv;
    double Vm_s_Lv = ( 4 * M_PI / 3) * pow( 1 / fabs(Cm_Lv), 3);
    double Vm_s_Sv = ( 4 * M_PI / 3) * pow( 1 / fabs( Cm_Sv ), 3 );
    double Vm_s_Rv = ( 4 * M_PI / 3) * pow( 1 / fabs( Cm_Rv ), 3 );
    double R_s_Lv = - pow( ( 3.0 / ( 4 * M_PI ) ) * ( Vm_s_Lv + ( 0.5 * Vw_s_Lv ) ), 1.0 / 3.0 );
    double r_s_Lv = - pow( ( 3.0 / ( 4 * M_PI ) ) * ( Vm_s_Lv - ( 0.5 * Vw_s_Lv ) ), 1.0 / 3.0 );
    double r_s_Sv = pow( ( 3 / ( 4 * M_PI ) ) * ( Vm_s_Sv - ( 0.5 * Vw_s_Sv ) ) , 1.0 / 3 );
    if ( Xm_Sv < 0 && Cm_Sv > 0.01 ) r_s_Sv *= -1.0;
    double R_s_Sv = pow( ( 3 / ( 4 * M_PI ) ) * ( Vm_s_Sv + ( 0.5 * Vw_s_Sv ) ), 1.0 / 3 );
    if ( Xm_Sv < 0 && Cm_Sv > 0.01 ) R_s_Sv *= -1.0;
    double R_s_Rv = pow( ( 3 / ( 4 * M_PI ) ) * ( Vm_s_Rv + ( 0.5 * Vw_s_Rv ) ), 1.0 / 3 );
    double r_s_Rv = pow( ( 3 / ( 4 * M_PI ) ) * ( Vm_s_Rv - ( 0.5 * Vw_s_Rv ) ),  1.0 / 3 );

    double LvEpi = - Xm_Lv + 1./Cm_Lv + R_s_Lv;
    double LvEndo = - Xm_Lv + 1./Cm_Lv + r_s_Lv;

    double SvEpi {0};
    double SvEndo {0};

    if (Cm_Sv < 0.01 )
    {
        SvEpi  = Xm_Sv + ( dsv / 2 );
        SvEndo = Xm_Sv - ( dsv / 2 );
    }
    else
    {
        SvEpi  = R_s_Sv + Xm_Sv - 1./Cm_Sv;
        SvEndo = r_s_Sv + Xm_Sv - 1./Cm_Sv; // (multiplying by sign(Xm) ensures that Xm is positive)
    }


    double RvEpi =  Xm_Rv - 1./Cm_Rv + R_s_Rv;
    double RvEndo =  Xm_Rv - 1./Cm_Rv + r_s_Rv;


    m_data["LvEpi"].append(LvEpi);
    m_currentBeatData["LvEpi"].append(LvEpi);
    m_data["LvEndo"].append(LvEndo);
    m_currentBeatData["LvEndo"].append(LvEndo);
    m_data["RvEpi"].append(RvEpi);
    m_currentBeatData["RvEpi"].append(RvEpi);
    m_data["RvEndo"].append(RvEndo);
    m_currentBeatData["RvEndo"].append(RvEndo);
    m_data["SvEpi"].append(SvEpi);
    m_currentBeatData["SvEpi"].append(SvEpi);
    m_data["SvEndo"].append(SvEndo);
    m_currentBeatData["SvEndo"].append(SvEndo);

}

void Buffer::calculateEngineeringStrain()
{

    if (m_beatData.isEmpty())
    {
        m_data["strain_Lv"].append(0);
        m_currentBeatData["strain_Lv"].append(0);
        m_data["strain_Sv"].append(0);
        m_currentBeatData["strain_Sv"].append(0);
        m_data["strain_Rv"].append(0);
        m_currentBeatData["strain_Rv"].append(0);
        m_data["strain_La"].append(0);
        m_currentBeatData["strain_La"].append(0);
        m_data["strain_Ra"].append(0);
        m_currentBeatData["strain_Ra"].append(0);
        for (const QString& s : {"l_s_Lv0", "l_s_Lv1", "l_s_Lv2", "l_s_Lv3", "l_s_Lv4", "l_s_Lv5", "l_s_Lv6", "l_s_Lv7", "l_s_Lv8", "l_s_Lv9", "l_s_Lv10"})
        {
            QString extracted = s.section('_', -1);
            m_data["strain_" + extracted].append(0);
            m_currentBeatData["strain_" + extracted].append(0);

        }
        for (const QString& s : {"l_s_Sv0", "l_s_Sv1", "l_s_Sv2", "l_s_Sv3", "l_s_Sv4"})
        {
            QString extracted = s.section('_', -1);
            m_data["strain_" + extracted].append(0);
            m_currentBeatData["strain_" + extracted].append(0);
        }
        for (const QString& s : {"l_s_Rv0", "l_s_Rv1", "l_s_Rv2", "l_s_Rv3", "l_s_Rv4", "l_s_Rv5", "l_s_Rv6"})
        {
            QString extracted = s.section('_', -1);
            m_data["strain_" + extracted].append(0);
            m_currentBeatData["strain_" + extracted].append(0);
        }
    }
    else
    {
        double idxQRSOnset = getLastBeat()->getStat("idxQRSOnset");
        double d = 0;
        // // Here calculate Ls/l_s_mvc for all strains
        for (const QString& s : {"l_s_Lv0", "l_s_Lv1", "l_s_Lv2", "l_s_Lv3", "l_s_Lv4", "l_s_Lv5", "l_s_Lv6", "l_s_Lv7", "l_s_Lv8", "l_s_Lv9", "l_s_Lv10"})
        {
            QString extracted = s.section('_', -1);
            m_data["strain_" + extracted].append(((m_data[s].last() / getLastBeat()->get(s).at(idxQRSOnset)) - 1) * 100) ;
            m_currentBeatData["strain_" + extracted].append(((m_data[s].last() / getLastBeat()->get(s).at(idxQRSOnset)) - 1) * 100) ;
            d += ((m_data[s].last() / getLastBeat()->get(s).at(idxQRSOnset)) - 1) * 100 ;

        }
        m_data["strain_Lv"].append(d/11);
        m_currentBeatData["strain_Lv"].append(d/11);
        d = 0;
        for (const QString& s : {"l_s_Sv0", "l_s_Sv1", "l_s_Sv2", "l_s_Sv3", "l_s_Sv4"})
        {
            QString extracted = s.section('_', -1);
            m_data["strain_" + extracted].append(((m_data[s].last() / getLastBeat()->get(s).at(idxQRSOnset)) - 1) * 100) ;
            m_currentBeatData["strain_" + extracted].append(((m_data[s].last() / getLastBeat()->get(s).at(idxQRSOnset)) - 1) * 100) ;
            d += ((m_data[s].last() / getLastBeat()->get(s).at(idxQRSOnset)) - 1) * 100 ;
        }
        m_data["strain_Sv"].append(d/5);
        m_currentBeatData["strain_Sv"].append(d/5);
        d = 0;
        for (const QString& s : {"l_s_Rv0", "l_s_Rv1", "l_s_Rv2", "l_s_Rv3", "l_s_Rv4", "l_s_Rv5", "l_s_Rv6"})
        {
            QString extracted = s.section('_', -1);
            m_data["strain_" + extracted].append(((m_data[s].last() / getLastBeat()->get(s).at(idxQRSOnset)) - 1) * 100) ;
            m_currentBeatData["strain_" + extracted].append(((m_data[s].last() / getLastBeat()->get(s).at(idxQRSOnset)) - 1) * 100) ;
            d += ((m_data[s].last() / getLastBeat()->get(s).at(idxQRSOnset)) - 1) * 100 ;
        }
        m_data["strain_Rv"].append(d/7);
        m_currentBeatData["strain_Rv"].append(d/7);

        for (const QString& s : {"l_s_La", "l_s_Ra"})
        {
            QString extracted = s.section('_', -1);
            m_data["strain_" + extracted].append(((m_data[s].last() / getLastBeat()->get(s).at(idxQRSOnset)) - 1) * 100) ;
            m_currentBeatData["strain_" + extracted].append(((m_data[s].last() / getLastBeat()->get(s).at(idxQRSOnset)) - 1) * 100) ;
        }
    }
}


void Buffer::calculateAverageWallStress()
{
    double d = 0;
    for (auto s : {"Sf_Lv0", "Sf_Lv1", "Sf_Lv2", "Sf_Lv3", "Sf_Lv4", "Sf_Lv5", "Sf_Lv6", "Sf_Lv7", "Sf_Lv8", "Sf_Lv9", "Sf_Lv10"})
    {
        d += m_data[s].last();

    }
    m_data["Sf_Lv"].append(d/11);
    m_currentBeatData["Sf_Lv"].append(d/11);
    d = 0;
    for (auto s : {"Sf_Sv0", "Sf_Sv1", "Sf_Sv2", "Sf_Sv3", "Sf_Sv4"})
    {
        d += m_data[s].last();
    }
    m_data["Sf_Sv"].append(d/5);
    m_currentBeatData["Sf_Sv"].append(d/5);
    d = 0;
    for (auto s : {"Sf_Rv0", "Sf_Rv1", "Sf_Rv2", "Sf_Rv3", "Sf_Rv4", "Sf_Rv5", "Sf_Rv6"})
    {
        d += m_data[s].last();
    }
    m_data["Sf_Rv"].append(d/7);
    m_currentBeatData["Sf_Rv"].append(d/7);
}
