#include "beatdata.h"

BeatData::BeatData() {}

void BeatData::clear()
{
    m_data.clear();
}

void BeatData::setData(const QMap<QString, QVector<double>>& data)
{
    m_data = data;
}

double BeatData::get(const QString& param)
{
    return m_beatStats[param];
}

void BeatData::analyzeData()
{
    m_beatStats["CO"] = getCO();
    m_beatStats["Qs"] = getQs();
    m_beatStats["Qp"] = getQp();
    m_beatStats["Qp/Qs"] = m_beatStats["Qp"]/m_beatStats["Qs"];
    m_beatStats["mLAP"] = get_mLAP();
    m_beatStats["SBP"] = getSBP();
    m_beatStats["DBP"] = getDBP();
    m_beatStats["MAP"] = getMAP();
    m_beatStats["PVR"] = getPVR();
    m_beatStats["ASD flow"] = get_qASD();
    m_beatStats["VSD flow"] = get_qVSD();
    m_beatStats["mPAP"] = get_mPAP();

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

double BeatData::get_mLAP()
{
    double mLAP = std::accumulate(m_data["pLa"].begin(), m_data["pLa"].end(), .0) / m_data["pLa"].size();
    return mLAP;
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
    double MAP = std::accumulate(m_data["pAo"].begin(), m_data["pAo"].end(), .0) / m_data["pLa"].size();
    return MAP;
}

double BeatData::getPVR()
{
    double mPAP = get_mPAP();
    double mLAP = get_mLAP();
    double CO = getCO();
    return (mPAP - mLAP)/CO;
}

double BeatData::get_qASD()
{
    return m_data["ven_ret"].last();
}

double BeatData::get_qVSD()
{
    return m_data["ven_ret"].last();
}

double BeatData::get_mPAP()
{
    double mPAP = std::accumulate(m_data["pPu"].begin(), m_data["pPu"].end(), .0) / m_data["pLa"].size();
    return mPAP;
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
