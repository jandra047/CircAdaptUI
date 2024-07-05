#ifndef BEATDATA_H
#define BEATDATA_H

#include <QMap>
#include <QString>
#include <QMutex>

class BeatData
{
public:
    BeatData();
    void clear();
    void setData(const QMap<QString, QVector<double>>& data);
    double get(const QString& param);
    QMap<QString, double> getStats() { return m_beatStats; };


private:
    void analyzeData();
    double getCO();
    double getQs();
    double getQp();
    double get_mLAP();
    double getSBP();
    double getDBP();
    double getMAP();
    double getPVR();
    double get_qASD();
    double get_qVSD();
    double get_mPAP();

    QMap<QString, QVector<double>> m_data;

    QMap<QString, double> m_beatStats;
};

#endif // BEATDATA_H
