#include "beatdata.h"

BeatData::BeatData(QObject* parent):
    QObject(parent)
{}

void BeatData::clear()
{
    m_data.clear();
}

void BeatData::setData(const QMap<QString, QVector<double>>& data)
{
    m_data = data;
    analyzeData();
}

QVector<double> BeatData::get(const QString& param)
{
    return m_data[param];
}

void BeatData::analyzeData()
{
    m_beatStats["CO"] = getCO();
    m_beatStats["Qs"] = getQs();
    m_beatStats["Qp"] = getQp();
    m_beatStats["Qp/Qs"] = m_beatStats["Qp"]/m_beatStats["Qs"];
    m_beatStats["CVP"] = get_CVP();
    m_beatStats["mLAP"] = get_mLAP();
    m_beatStats["mRAP"] = get_mRAP();
    m_beatStats["SBP"] = getSBP();
    m_beatStats["DBP"] = getDBP();
    m_beatStats["MAP"] = getMAP();
    m_beatStats["PVR"] = getPVR();
    m_beatStats["sPAP"] = get_sPAP();
    m_beatStats["dPAP"] = get_dPAP();
    m_beatStats["mPAP"] = get_mPAP();
    m_beatStats["PVP"] = getPVP();
    m_beatStats["idxQRSOnset"] = getIdxQRSOnset();

}

double BeatData::getCO()
{
    double tCycle = m_data["t"].last() - m_data["t"].first();
    return calcIntegral(m_data["qSyVenRa"], m_data["t"]) * 60 / tCycle / 1000;
}

double BeatData::getQs()
{
    double tCycle = m_data["t"].last() - m_data["t"].first();
    return calcIntegral(m_data["qLvAo"], m_data["t"]) * 60 / tCycle / 1000;
}

double BeatData::getQp()
{
    double tCycle = m_data["t"].last() - m_data["t"].first();
    return calcIntegral(m_data["qRvPuArt"], m_data["t"]) * 60 / tCycle / 1000;
}

double BeatData::get_CVP()
{
    double CVP = std::accumulate(m_data["pSyVen"].begin(), m_data["pSyVen"].end(), .0) / m_data["pSyVen"].size();
    return CVP;
}

double BeatData::get_mLAP()
{
    double mLAP = std::accumulate(m_data["pLa"].begin(), m_data["pLa"].end(), .0) / m_data["pLa"].size();
    return mLAP;
}

double BeatData::get_mRAP()
{
    double mRAP = std::accumulate(m_data["pRa"].begin(), m_data["pRa"].end(), .0) / m_data["pRa"].size();
    return mRAP;
}

double BeatData::getSBP()
{
    double SBP = *std::max_element(m_data["pAo"].constBegin(), m_data["pAo"].constEnd());
    return SBP;
}

double BeatData::getDBP()
{
    double DBP = *std::min_element(m_data["pAo"].constBegin(), m_data["pAo"].constEnd());
    return DBP;
}

double BeatData::getMAP()
{
    double MAP = std::accumulate(m_data["pAo"].begin(), m_data["pAo"].end(), .0) / m_data["pAo"].size();
    return MAP;
}

double BeatData::getPVR()
{
    double mPAP = get_mPAP();
    double mLAP = get_mLAP();
    double CO = getCO();
    return (mPAP - mLAP)/CO;
}

double BeatData::get_sPAP()
{
    double sPAP = *std::max_element(m_data["pPu"].begin(), m_data["pPu"].end());
    return sPAP;
}

double BeatData::get_dPAP()
{
    double dPAP = *std::min_element(m_data["pPu"].begin(), m_data["pPu"].end());
    return dPAP;
}

double BeatData::get_mPAP()
{
    double mPAP = std::accumulate(m_data["pPu"].begin(), m_data["pPu"].end(), .0) / m_data["pPu"].size();
    return mPAP;
}

double BeatData::getPVP()
{
    double PVP = std::accumulate(m_data["pPuVen"].begin(), m_data["pPuVen"].end(), .0) / m_data["pPuVen"].size();
    return PVP;
}

double BeatData::getIdxQRSOnset()
{
    int beatSize = m_data["t"].size();
    QVector<double> CLv(beatSize, 0.0);
    QVector<double> C_dotLv(beatSize, 0.0);
    QVector<double> CSv(beatSize, 0.0);
    QVector<double> C_dotSv(beatSize, 0.0);
    QVector<double> CRv(beatSize, 0.0);
    QVector<double> C_dotRv(beatSize, 0.0);
    for (int i = 0; i < 11; i++)
    {
        for (int idx = 0; idx < beatSize; idx++)
        {
            CLv[idx] += m_data[QString("C_Lv%1").arg(i)].at(idx);
            C_dotLv[idx] += m_data[QString("C_dot_Lv%1").arg(i)].at(idx);
        }
    }
    std::transform(CLv.begin(), CLv.end(), CLv.begin(),
                   [](double value) { return value / 11.0; });
    std::transform(C_dotLv.begin(), C_dotLv.end(), C_dotLv.begin(),
                   [](double value) { return value / 11.0; });

    for (int i = 0; i < 5; i++)
    {
        for (int idx = 0; idx < beatSize; idx++)
        {
            CSv[idx] += m_data[QString("C_Sv%1").arg(i)].at(idx);
            C_dotSv[idx] += m_data[QString("C_dot_Sv%1").arg(i)].at(idx);
        }
    }
    std::transform(CSv.begin(), CSv.end(), CSv.begin(),
                   [](double value) { return value / 5.0; });
    std::transform(C_dotSv.begin(), C_dotSv.end(), C_dotSv.begin(),
                   [](double value) { return value / 5.0; });

    for (int i = 0; i < 7; i++)
    {
        for (int idx = 0; idx < beatSize; idx++)
        {
            CRv[idx] += m_data[QString("C_Rv%1").arg(i)].at(idx);
            C_dotRv[idx] += m_data[QString("C_dot_Rv%1").arg(i)].at(idx);
        }
    }
    std::transform(CRv.begin(), CRv.end(), CRv.begin(),
                   [](double value) { return value / 7.0; });
    std::transform(C_dotRv.begin(), C_dotRv.end(), C_dotRv.begin(),
                   [](double value) { return value / 7.0; });

    QVector<double> Ctot(m_data["t"].size(), 0.0);
    QVector<double> C_dotTot(m_data["t"].size(), 0.0);
    for (int i = 0; i < CLv.size(); i++)
    {
        Ctot[i] += CLv[i] + CSv[i] + CRv[i];
        C_dotTot[i] += C_dotLv[i] + C_dotSv[i] + C_dotRv[i];
    }

    double CMax = *std::max_element(Ctot.begin(), Ctot.end());
    int t10 = 0;
    int t40 = 0;
    double CMax10 = 0.1 * CMax;
    double CMax40 = 0.4 * CMax;
    for ( int t=0; t < Ctot.size(); t++ )
    {
        if ( C_dotTot[t] > 0 )
        {
            if ( Ctot[t] < CMax10 )
            {
                t10 = t;
            }
            if ( Ctot[t] < CMax40 )
            {
                t40 = t;
            }
            else
            {
                break;
            }
        }
    }

    QVector<double> slice = Ctot.mid(t10, t40-t10);
    double sliceMean = std::accumulate(slice.begin(), slice.end(), 0.0) / slice.count();

    QVector<double> ts(slice.size(), 0.0);
    for (int t=0; t < ts.size(); t++)
    {
        ts[t] = t;
    }
    double a;
    double slope;
    linearRegression(ts, slice, a, slope);
    double OnsetActL  = qRound((t40 + t10)/2.0 - sliceMean / slope); //PETER

    // Sum C curves for all patches in a wall and divide it by number of patches.
    // Sum C_dot for all patches in a wall and divide it by number of patches
    // Sum all C values for each wall to get Ctot
    // Find time for 10% and 40% of Ctot
    // Calculate slope
    return OnsetActL;

}

double BeatData::calcIntegral(const QVector<double>& vec1, const QVector<double>& vec2)
{
    // Check if the vectors are of the same size and have at least two elements
    if (vec1.size() != vec2.size() || vec1.size() < 2)
    {
        throw std::invalid_argument("Vectors must have the same size and contain at least two elements.");
    }

    double integral = 0.0;

    // Implement the trapezoidal rule
    for (int i = 0; i < vec1.size() - 1; ++i) {
        double deltaT = vec2[i + 1] - vec2[i];
        double averageFlow = (vec1[i] + vec1[i + 1]) / 2.0;
        integral += averageFlow * deltaT;
    }

    return integral;
}

void BeatData::linearRegression(const QVector<double>& x,
             const QVector<double>& y,
             double& intercept,
             double& slope)
{
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    int n = x.size();

    for(int i = 0; i < n; i++) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    intercept = (sumY - slope * sumX) / n;
}
