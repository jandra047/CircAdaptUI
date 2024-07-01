#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QJsonObject>

class DataContainer
{
public:
    DataContainer(const QString& name, const QString& path, const QString& mType) :
        mName(name), mPath(path), mType(mType)
        {};
    QString getType() { return mType; };
    QString getName() { return mName; };
    QString getPath() { return mPath; };
    virtual double convert(double) const = 0;
private:
    QString mName;
    QString mPath;
    QString mType;
};

class PressureContainer : public DataContainer
{
public:
    PressureContainer(const QString& name, const QString& path, const QString& type):
        DataContainer(name, path, type) {};
    double convert(double val) const override { return val / 133; };
};

class VolumeContainer : public DataContainer
{
public:
    VolumeContainer(const QString& name, const QString& path, const QString& type):
        DataContainer(name, path, type) {};
    double convert(double val) const override { return val * 1e6; };
};

class FlowContainer : public DataContainer
{
public:
    FlowContainer(const QString& name, const QString& path, const QString& type):
        DataContainer(name, path, type) {};
    double convert(double val) const override { return val * 60000; };
};

class DataContainerFactory
{
public:
    DataContainerFactory();
    static DataContainer* createSignal(const QJsonObject& json) {
        QString const name = json["name"].toString();
        QString const path = json["path"].toString();
        QString const type = json["type"].toString();
        if (type == "pressure")
        {
            return new PressureContainer(name, path, type);
        }
        else if (type == "volume")
        {
            return new VolumeContainer(name, path, type);
        }
        else if (type == "flow")
        {
            return new FlowContainer(name, path, type);
        }
        else
        {
            throw std::invalid_argument("Unknown signal name: " + type.toStdString());
        }
    };
    DataContainerFactory(const DataContainerFactory&) = delete;
    DataContainerFactory& operator=(const DataContainerFactory&) = delete;
    ~DataContainerFactory() = default;
};

#endif // DATACONTAINER_H
