#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QJsonObject>
#include <any>

class DataContainer : public QObject
{
    Q_OBJECT
public:
    DataContainer(const QString& name, const QString& path, const QString& mType, QObject* parent = Q_NULLPTR) :
        QObject(parent),
        mName(name), mPath(path), mType(mType)
        {};
    ~DataContainer() = default;
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
    PressureContainer(const QString& name, const QString& path, const QString& type, QObject* parent):
        DataContainer(name, path, type, parent) {};
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
    StressContainer(const QString& name, const QString& path, const QString& type, QObject* parent):
        DataContainer(name, path, type, parent) {};
    // double model_to_ui(double val) const override { return val / 133; };
    std::any model_to_ui(std::any value) const override
    {
        return std::any_cast<double>(value) / 1000;
    }
    std::any ui_to_model(std::any value) const override
    {
        return std::any_cast<double>(value) / 1000;
    }
};

class VolumeContainer : public DataContainer
{
public:
    VolumeContainer(const QString& name, const QString& path, const QString& type, QObject* parent):
        DataContainer(name, path, type, parent) {};
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
    FlowContainer(const QString& name, const QString& path, const QString& type, QObject* parent):
        DataContainer(name, path, type, parent) {};
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
    HRContainer(const QString& name, const QString& path, const QString& type, QObject* parent):
        DataContainer(name, path, type, parent) {};
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
    COContainer(const QString& name, const QString& path, const QString& type, QObject* parent):
        DataContainer(name, path, type, parent) {};
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
    BoolContainer(const QString& name, const QString& path, const QString& type, QObject* parent):
        DataContainer(name, path, type, parent) {};
    std::any model_to_ui(std::any value) const override
    {
        return std::any_cast<bool>(value);
    }
    std::any ui_to_model(std::any value) const override
    {
        return std::any_cast<bool>(value);
    }
};


class MilliSecondsContainer : public DataContainer
{
public:
    MilliSecondsContainer(const QString& name, const QString& path, const QString& type, QObject* parent):
        DataContainer(name, path, type, parent) {};
    std::any model_to_ui(std::any value) const override
    {
        return std::any_cast<double>(value) * 1e3;
    }
    std::any ui_to_model(std::any value) const override
    {
        return std::any_cast<double>(value) / 1e3;
    }
};

class AreaContainer : public DataContainer
{
public:
    AreaContainer(const QString& name, const QString& path, const QString& type, QObject* parent):
        DataContainer(name, path, type, parent) {};
    std::any model_to_ui(std::any value) const override
    {
        return std::any_cast<double>(value) * 1e4;
    }
    std::any ui_to_model(std::any value) const override
    {
        return std::any_cast<double>(value) / 1e4;
    }
};

class DiameterContainer : public DataContainer
{
public:
    DiameterContainer(const QString& name, const QString& path, const QString& type, QObject* parent):
        DataContainer(name, path, type, parent)
        {};
    std::any model_to_ui(std::any value) const override
    {
        return sqrt(std::any_cast<double>(value) / M_PI) / 1e-6;
    }
    std::any ui_to_model(std::any value) const override
    {
        return pow(std::any_cast<double>(value), 2) * M_PI * 1e-6;
    }
};

class PercentageContainer : public DataContainer
{
public:
    PercentageContainer(const QString& name, const QString& path, const QString& type, const double defaultValue, QObject* parent):
        DataContainer(name, path, type, parent),
        m_defaultValue(defaultValue)
        {};
    std::any model_to_ui(std::any value) const override
    {
        return std::any_cast<double>(value) / m_defaultValue * 100;
    }
    std::any ui_to_model(std::any value) const override
    {
        return std::any_cast<double>(value) * m_defaultValue / 100;
    }
private:
    double m_defaultValue;
};

class CoefficientContainer : public DataContainer
{
public:
    CoefficientContainer(const QString& name, const QString& path, const QString& type, QObject* parent):
        DataContainer(name, path, type, parent) {};
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

class DataContainerFactory
{
public:
    DataContainerFactory();
    static DataContainer* createSignal(const QJsonObject& json, QObject* parent = Q_NULLPTR) {
        QString const name = json["name"].toString();
        QString const path = json["path"].toString();
        QString const type = json["type"].toString();
        double const defaultValue = json["default"].toDouble();
        if (type == "pressure")
        {
            return new PressureContainer(name, path, type, parent);
        }
        if (type == "stress")
        {
            return new StressContainer(name, path, type, parent);
        }
        else if (type == "volume")
        {
            return new VolumeContainer(name, path, type, parent);
        }
        else if (type == "flow")
        {
            return new FlowContainer(name, path, type, parent);
        }
        else if (type == "HR")
        {
            return new HRContainer(name, path, type, parent);
        }
        else if (type == "CO")
        {
            return new COContainer(name, path, type, parent);
        }
        else if (type == "bool")
        {
            return new BoolContainer(name, path, type, parent);
        }
        else if (type == "ms")
        {
            return new MilliSecondsContainer(name, path, type, parent);
        }
        else if (type == "area")
        {
            return new AreaContainer(name, path, type, parent);
        }
        else if (type == "diameter")
        {
            return new DiameterContainer(name, path, type, parent);
        }
        else if (type == "percentage")
        {
            return new PercentageContainer(name, path, type, defaultValue, parent);
        }
        else if (type == "coefficient")
        {
            return new CoefficientContainer(name, path, type, parent);
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
