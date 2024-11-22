#ifndef BEATDATA_H
#define BEATDATA_H

#include <QMap>
#include <QString>
#include <QMutex>
#include <QObject>

class BeatData: public QObject
{
    Q_OBJECT
public:
    BeatData(QObject* parent = Q_NULLPTR);
    void clear();
    void setData(const QMap<QString, QVector<double>>& data);
    QVector<double> get(const QString& param);
    QMap<QString, double> getStats() { return m_beatStats; }
    double getStat(const QString& key) { return m_beatStats[key]; }
    QMap<QString, QVector<double>> getData() { return m_data; }


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
    double get_mPAP();
    double getPVP();
    double getIdxQRSOnset();

    static double calcIntegral(const QVector<double>& vec1, const QVector<double>& vec2);
    static void linearRegression(const QVector<double>& x,
                                 const QVector<double>& y,
                                 double& intercept,
                                 double& slope);
    QMap<QString, QVector<double>> m_data;

    QMap<QString, double> m_beatStats;
};

#endif // BEATDATA_H
