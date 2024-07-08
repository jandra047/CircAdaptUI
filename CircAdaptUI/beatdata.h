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
    QVector<double> get(const QString& param);
    QMap<QString, double> getStats() { analyzeData(); return m_beatStats; };
    QMap<QString, QVector<double>> getData() { return m_data; };


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

    double calcIntegral(const QVector<double>& vec1, const QVector<double>& vec2);
    QMap<QString, QVector<double>> m_data;

    QMap<QString, double> m_beatStats;
};

#endif // BEATDATA_H
