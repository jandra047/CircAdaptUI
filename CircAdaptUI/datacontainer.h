#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QJsonObject>
#include <any>

class DataContainer
{
public:
    DataContainer(const QString& name, const QString& path, const QString& mType) :
        mName(name), mPath(path), mType(mType)
        {};
    QString getType() { return mType; };
    QString getName() { return mName; };
    QString getPath() { return mPath; };
    virtual std::any model_to_ui(std::any value) const = 0;
    virtual std::any ui_to_model(std::any value) const = 0;
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
    // double model_to_ui(double val) const override { return val / 133; };
    std::any model_to_ui(std::any value) const override
    {
        return std::any_cast<double>(value) / 133;
    }
    std::any ui_to_model(std::any value) const override
    {
        return std::any_cast<double>(value) * 133 ;
    }
};

class StressContainer : public DataContainer
{
public:
    StressContainer(const QString& name, const QString& path, const QString& type):
        DataContainer(name, path, type) {};
    // double model_to_ui(double val) const override { return val / 133; };
    std::any model_to_ui(std::any value) const override
    {
        return std::any_cast<double>(value);
    }
    std::any ui_to_model(std::any value) const override
    {
        return std::any_cast<double>(value);
    }
};

class VolumeContainer : public DataContainer
{
public:
    VolumeContainer(const QString& name, const QString& path, const QString& type):
        DataContainer(name, path, type) {};
    std::any model_to_ui(std::any value) const override
    {
        return std::any_cast<double>(value) * 1e6 ;
    }
    std::any ui_to_model(std::any value) const override
    {
        return std::any_cast<double>(value) / 1e6 ;
    }
};

class FlowContainer : public DataContainer
{
public:
    FlowContainer(const QString& name, const QString& path, const QString& type):
        DataContainer(name, path, type) {};
    std::any model_to_ui(std::any value) const override
    {
        return std::any_cast<double>(value) * 1e6 ;
    }
    std::any ui_to_model(std::any value) const override
    {
        return std::any_cast<double>(value) / 1e6 ;
    }
};

class HRContainer : public DataContainer
{
public:
    HRContainer(const QString& name, const QString& path, const QString& type):
        DataContainer(name, path, type) {};
    std::any model_to_ui(std::any value) const override
    {
        return 60 / std::any_cast<double>(value);
    }
    std::any ui_to_model(std::any value) const override
    {
        return 60 / std::any_cast<double>(value);
    }
};

class COContainer : public DataContainer
{
public:
    COContainer(const QString& name, const QString& path, const QString& type):
        DataContainer(name, path, type) {};
    std::any model_to_ui(std::any value) const override
    {
        return std::any_cast<double>(value) * 60000;
    }
    std::any ui_to_model(std::any value) const override
    {
        return std::any_cast<double>(value) / 60000;
    }
};

class BoolContainer : public DataContainer
{
public:
    BoolContainer(const QString& name, const QString& path, const QString& type):
        DataContainer(name, path, type) {};
    std::any model_to_ui(std::any value) const override
    {
        return std::any_cast<bool>(value);
    }
    std::any ui_to_model(std::any value) const override
    {
        return std::any_cast<bool>(value);
    }
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
        if (type == "stress")
        {
            return new StressContainer(name, path, type);
        }
        else if (type == "volume")
        {
            return new VolumeContainer(name, path, type);
        }
        else if (type == "flow")
        {
            return new FlowContainer(name, path, type);
        }
        else if (type == "HR")
        {
            return new HRContainer(name, path, type);
        }
        else if (type == "CO")
        {
            return new COContainer(name, path, type);
        }
        else if (type == "bool")
        {
            return new BoolContainer(name, path, type);
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
