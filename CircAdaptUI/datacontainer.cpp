#include "datacontainer.h"
#include "modelwrapper.h"
#include "buffer.h"

void DataContainer::updateParam(QVariant variant) const
{
    switch (variant.userType())
    {
        case QMetaType::Bool:
        {
            bool b = variant.toBool();
            mw.set_bool(mPath.toStdString(), b);
            break;
        }
        case QMetaType::Double:
        {
            double d = ui_to_model(variant).toDouble();
            mw.set_double(mPath.toStdString(), d);
            break;
        }
    }
}

QVariant DataContainer::get()
{
    switch (mMetaType)
    {
        case (QMetaType::Double):
        {
            double d;
            mw.get_double(mPath.toStdString(), d);
            return model_to_ui(d);
        }
        case (QMetaType::Bool):
        {
            bool b;
            mw.get_bool(mPath.toStdString(), b);
            return model_to_ui(b);
        }
        default:
            return QVariant();
    }
}

void DataContainer::updateBuffer(Buffer& buffer)
{
    QVariant variant = get();
    switch (variant.userType())
    {
        case (QMetaType::Double):
        {
            buffer.append(getName(), variant.toDouble());
            break;
        }
        case (QMetaType::Bool):
        {
            buffer.append(getName(), variant.toBool());
            break;
        }
    }
}

class PressureContainer : public DataContainer
{
public:
    PressureContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        mMetaType = QMetaType::Double;
    };
    // double model_to_ui(double val) const override { return val / 133; };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble() / 133;
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble() * 133 ;
    }
};

class StressContainer : public DataContainer
{
public:
    StressContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        mMetaType = QMetaType::Double;
    };
    // double model_to_ui(double val) const override { return val / 133; };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble() / 1000;
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble() / 1000;
    }
};

class VolumeContainer : public DataContainer
{
public:
    VolumeContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        mMetaType = QMetaType::Double;
    };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble() * 1e6 ;
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble() / 1e6 ;
    }
};

class FlowContainer : public DataContainer
{
public:
    FlowContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        mMetaType = QMetaType::Double;
    };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble() * 1e6 ;
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble() / 1e6 ;
    }
};

class FlowVelocityContainer : public DataContainer
{
public:
    FlowVelocityContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        int position = path.lastIndexOf(".");
        A_openPath = path.left(position) + ".A_open";
        A_leakPath = path.left(position) + ".A_leak";
        A_Path = path.left(position) + ".A";
        mMetaType = QMetaType::Double;

    };
    QVariant model_to_ui(QVariant variant) const override
    {
        double val = variant.toDouble();
        double A = 0;
        double A_leak = 0;
        double A_open = 0;
        mw.get_double(A_openPath.toStdString(), A_open);
        mw.get_double(A_leakPath.toStdString(), A_leak);
        mw.get_double(A_Path.toStdString(), A);
        if (A < 1.5 * A_leak && A_leak < 1e-7 )
            return 0.;
        if (val < 0)
        {
            return val / A_leak * 100;
        }
        else
        {
            return val / A_open * 100;
        }
    }

    // should not be used, rethink the structure
    QVariant ui_to_model(QVariant variant) const override
    {
        return -1;
    }

private:
    QString A_Path;
    QString A_openPath;
    QString A_leakPath;
};

class HRContainer : public DataContainer
{
public:
    HRContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        mMetaType = QMetaType::Double;
    };
    QVariant model_to_ui(QVariant variant) const override
    {
        return 60 / variant.toDouble();
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return 60 / variant.toDouble();
    }
};

class COContainer : public DataContainer
{
public:
    COContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        mMetaType = QMetaType::Double;
    };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble() * 60000;
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble() / 60000;
    }
};

class BoolContainer : public DataContainer
{
public:
    BoolContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        mMetaType = QMetaType::Bool;
    };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toBool();
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toBool();
    }
};


class MilliSecondsContainer : public DataContainer
{
public:
    MilliSecondsContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        mMetaType = QMetaType::Double;
    };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble() * 1e3;
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble() / 1e3;
    }
};

class AreaContainer : public DataContainer
{
public:
    AreaContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        mMetaType = QMetaType::Double;
    };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble() * 1e4;
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble() / 1e4;
    }
};

class DiameterContainer : public DataContainer
{
public:
    DiameterContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
        {
            mMetaType = QMetaType::Double;
        };
    QVariant model_to_ui(QVariant variant) const override
    {
        return sqrt(variant.toDouble() / M_PI) / 1e-6;
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return pow(variant.toDouble(), 2) * M_PI * 1e-6;
    }
};

class ShuntContainer : public DiameterContainer
{
public:
    ShuntContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DiameterContainer(name, path, type, parent)
        {
            mMetaType = QMetaType::Double;
        };
    QVariant model_to_ui(QVariant variant) const override
    {
        return sqrt(variant.toDouble() / M_PI) / 1e-6;
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return pow(variant.toDouble(), 2) * M_PI * 1e-6;
    }
    void updateParam(QVariant variant) const override
    {
        bool ok = false;
        double value = ui_to_model(variant).toDouble(&ok);
        if (ok)
            mw.set_double(
                QString(mPath + ".A_leak").toStdString(), value
                );
            mw.set_double(
                QString(mPath + ".A_open").toStdString(), value
                );
    }
};

class PercentageCoeffContainer : public DataContainer
{
public:
    PercentageCoeffContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
        {
            mMetaType = QMetaType::Double;
        };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble() * 100;
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble() / 100;
    }
};

class PercentageContainer : public DataContainer
{
public:
    PercentageContainer(const QString& name, const QString& path, const QString& type, const double defaultValue, ModelWrapper* parent):
        DataContainer(name, path, type, parent),
        m_defaultValue(defaultValue)
        {
            mMetaType = QMetaType::Double;
        };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble() / m_defaultValue * 100;
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble() * m_defaultValue / 100;
    }
private:
    double m_defaultValue;
};

class CoefficientContainer : public DataContainer
{
public:
    CoefficientContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        mMetaType = QMetaType::Double;
    };
    // double model_to_ui(double val) const override { return val / 133; };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble();
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble();
    }
};

class WallStrainContainer : public DataContainer
{
public:
    WallStrainContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        int position = path.lastIndexOf(".");
        wallPath = path.left(position);
        paramPart = path.right(path.length() - position);
        patchPart = ".p" + wallPath.right(2);

        mMetaType = QMetaType::Double;
        mw.get_int(
            QString(wallPath + ".n_patch").toStdString(), n_patch);

    };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble() * 1e3;
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble() / 1e3;
    }
    void updateParam(QVariant variant) const override
    {
        bool ok = false;
        double value = ui_to_model(variant).toDouble(&ok);
        if (ok)
        {
            QString str = wallPath + patchPart + "%1" + paramPart;
            for (int i = 0; i < n_patch; i++)
            {
                mw.set_double(
                    QString(str.arg(i)).toStdString(), value
                    );
            }
        }
    }
private:
    int n_patch = qQNaN();
    QString wallPath;
    QString paramPart;
    QString patchPart;
    double m_defaultValue;
};

class WallMSContainer : public DataContainer
{
public:
    WallMSContainer(const QString& name, const QString& path, const QString& type, const double defaultValue, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        int position = path.lastIndexOf(".");
        wallPath = path.left(position);
        paramPart = path.right(path.length() - position);
        patchPart = ".p" + wallPath.right(2);

        mw.get_double(
            QString(
                wallPath + patchPart + "0" + paramPart
                ).toStdString(),
            m_defaultValue
            );

        mMetaType = QMetaType::Double;
        mw.get_int(
            QString(wallPath + ".n_patch").toStdString(), n_patch);

    };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble() * 1e3;
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble() / 1e3;
    }
    void updateParam(QVariant variant) const override
    {
        bool ok = false;
        double value = ui_to_model(variant).toDouble(&ok);
        if (ok)
        {
            QString str = wallPath + patchPart + "%1" + paramPart;
            for (int i = 0; i < n_patch; i++)
            {
                mw.set_double(
                    QString(str.arg(i)).toStdString(), value
                    );
            }
        }
    }
private:
    int n_patch = qQNaN();
    QString wallPath;
    QString paramPart;
    QString patchPart;
    double m_defaultValue;
};

class WallCoeffContainer : public DataContainer
{
public:
    WallCoeffContainer(const QString& name, const QString& path, const QString& type, const double defaultValue, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        int position = path.lastIndexOf(".");
        wallPath = path.left(position);
        paramPart = path.right(path.length() - position);
        patchPart = ".p" + wallPath.right(2);

        mw.get_double(
            QString(
                wallPath + patchPart + "0" + paramPart
                ).toStdString(),
            m_defaultValue
            );

        mMetaType = QMetaType::Double;
        mw.get_int(
            QString(wallPath + ".n_patch").toStdString(), n_patch);

    };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble();
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble();
    }
    void updateParam(QVariant variant) const override
    {
        bool ok = false;
        double value = ui_to_model(variant).toDouble(&ok);
        if (ok)
        {
            QString str = wallPath + patchPart + "%1" + paramPart;
            for (int i = 0; i < n_patch; i++)
            {
                mw.set_double(
                    QString(str.arg(i)).toStdString(), value
                    );
            }
        }
    }
private:
    int n_patch = qQNaN();
    QString wallPath;
    QString paramPart;
    QString patchPart;
    double m_defaultValue;
};

class WallPercentageContainer : public DataContainer
{
public:
    WallPercentageContainer(const QString& name, const QString& path, const QString& type, const double defaultValue, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        int position = path.lastIndexOf(".");
        wallPath = path.left(position);
        paramPart = path.right(path.length() - position);
        patchPart = ".p" + wallPath.right(2);

        mw.get_double(
            QString(
                wallPath + patchPart + "0" + paramPart
                ).toStdString(),
            m_defaultValue
            );

        mMetaType = QMetaType::Double;
        mw.get_int(
            QString(wallPath + ".n_patch").toStdString(), n_patch);

    };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble() / m_defaultValue * 100;
    }

    // should not be used, rethink the structure
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble() * m_defaultValue / 100;
    }
    void updateParam(QVariant variant) const override
    {
        bool ok = false;
        double value = ui_to_model(variant).toDouble(&ok);
        if (ok)
        {
            QString str = wallPath + patchPart + "%1" + paramPart;
            for (int i = 0; i < n_patch; i++)
            {
                mw.set_double(
                    QString(str.arg(i)).toStdString(), value
                    );
            }
        }
    }
private:
    int n_patch = qQNaN();
    QString wallPath;
    QString paramPart;
    QString patchPart;
    double m_defaultValue;
};

class ConcentrationContainer : public DataContainer
{
public:
    ConcentrationContainer(const QString& name, const QString& path, const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        mMetaType = QMetaType::Double;
    };
    // double model_to_ui(double val) const override { return val / 133; };
    QVariant model_to_ui(QVariant variant) const override
    {
        return variant.toDouble() * 0.6206;
    }
    QVariant ui_to_model(QVariant variant) const override
    {
        return variant.toDouble() / 0.6206 ;
    }
};

DataContainer* DataContainerFactory::createContainer(const QJsonObject& json, ModelWrapper* parent) {
    QString const name = json["name"].toString();
    QString const path = json["path"].toString();
    QString const type = json["type"].toString();
    double const defaultValue = json["default"].toDouble();
    if (type == "pressure")
    {
        return new PressureContainer(name, path, type, parent);
    }
    else if (type == "stress")
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
    else if (type == "flowvelocity")
    {
        return new FlowVelocityContainer(name, path, type, parent);
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
    else if (type == "shunt")
    {
        return new ShuntContainer(name, path, type, parent);
    }
    else if (type == "percentagecoeff")
    {
        return new PercentageCoeffContainer(name, path, type, parent);
    }
    else if (type == "percentage")
    {
        return new PercentageContainer(name, path, type, defaultValue, parent);
    }
    else if (type == "coefficient")
    {
        return new CoefficientContainer(name, path, type, parent);
    }
    else if (type == "wallpercentage")
    {
        return new WallPercentageContainer(name, path, type, defaultValue, parent);
    }
    else if (type == "wallms")
    {
        return new WallMSContainer(name, path, type, defaultValue, parent);
    }
    else if (type == "wallcoeff")
    {
        return new WallCoeffContainer(name, path, type, defaultValue, parent);
    }
    else if (type == "wall")
    {
        return new WallStrainContainer(name, path, type, parent);
    }
    else if (type == "concentration")
    {
        return new ConcentrationContainer(name, path, type, parent);
    }
    else
    {
        throw std::invalid_argument("Unknown signal name: " + type.toStdString());
    }
};
