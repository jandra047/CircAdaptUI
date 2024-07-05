#include "beatdata.h"

BeatData::BeatData() {}

void BeatData::clear()
{
    m_data.clear();
}

void BeatData::setData(const QMap<QString, QVector<double>>& data)
{
    m_data = data;
    analyzeData();
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
    return m_data["ven_ret"].last();
}

double BeatData::getQs()
{
    return m_data["ven_ret"].last();
}

double BeatData::getQp()
{
    return m_data["ven_ret"].last();
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
