#include "datacontainer.h"
#include "modelwrapper.h"
#include "buffer.h"

DataContainer::DataContainer(const QString& name, const QString& path, const QString& mType, ModelWrapper* parent) :
    QObject((QObject*)parent),
    mName(name), mPath(path), mType(mType),
    mw(*parent)
    {
    };

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

/**
 * @brief Container for pressure values with automatic unit conversion
 *
 * Converts between model units (Pa) and UI units (mmHg) using a conversion factor of 133.
 */
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

/**
 * @brief Container for stress values with automatic unit conversion
 *
 * Converts between model units and UI units using a conversion factor of 1000.
 */
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

/**
 * @brief Container for volume values with automatic unit conversion
 *
 * Converts between model units (m³) and UI units (mL) using a factor of 1e6.
 */
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

/**
 * @brief Container for flow values with automatic unit conversion
 *
 * Converts between model units (m³/s) and UI units (mL/s) using a factor of 1e6.
 */
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

/**
 * @brief Container for flow velocity values with area-based calculations
 *
 * Computes flow velocity based on flow area parameters. Handles both forward
 * and backward flow calculations using different area parameters.
 */
class FlowVelocityContainer : public DataContainer
{
public:
    /**
     * @brief Constructs a FlowVelocityContainer
     * @param name Container identifier
     * @param path Base path in model
     * @param mType Type identifier
     * @param parent Parent ModelWrapper
     *
     * Automatically constructs paths for A_open, A_leak, and A parameters
     * based on the provided base path.
     */
    FlowVelocityContainer(const QString& name, const QString& path,
                          const QString& type, ModelWrapper* parent):
        DataContainer(name, path, type, parent)
    {
        int position = path.lastIndexOf(".");
        A_openPath = path.left(position) + ".A_open";
        A_leakPath = path.left(position) + ".A_leak";
        A_Path = path.left(position) + ".A";
        mMetaType = QMetaType::Double;

    };

    /**
     * @brief Converts model values to UI representation
     * @param variant Flow to convert to flow velocity
     * @return Converted value as flow divided by area
     *
     * Calculates flow velocity on area.
     * Returns 0 for very small areas.
     */
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
    QString A_Path;      ///< Path to area parameter
    QString A_openPath;  ///< Path to open area parameter
    QString A_leakPath;  ///< Path to leak area parameter
};

/**
 * @brief Container for heart rate values with period conversion
 *
 * Converts between model units (period in seconds) and UI units (beats per minute).
 */
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

/**
 * @brief Container for cardiac output values with unit conversion
 *
 * Converts between model units (m³/s) and UI units (L/min) using appropriate scaling.
 */
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

/**
 * @brief Container for boolean values
 *
 * Performs no conversion
 */
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

/**
 * @brief Container for millisecond time values
 *
 * Converts between model units (seconds) and UI units (milliseconds) using a factor of 1e3.
 */
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

/**
 * @brief Container for area values with automatic unit conversion
 *
 * Converts between model units (m²) and UI units (cm²) using a factor of 1e4.
 */
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

/**
 * @brief Container for diameter values with area conversion
 *
 * Converts between diameter in UI units [mm] and area in model units [m²] using π and appropriate scaling.
 * Base class for specialized diameter containers like ShuntContainer.
 */
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

/**
 * @brief Container for shunt diameter with special area handling
 *
 * Extends DiameterContainer with additional functionality to update both
 * A_leak and A_open parameters simultaneously.
 */
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
    /**
     * @brief Updates both leak and open area parameters
     * @param variant New diameter value
     *
     * Converts diameter to area and updates both A_leak and A_open parameters
     * to maintain consistent shunt behavior.
     */
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

/**
 * @brief Container for percentage coefficient values
 *
 * Converts between model units (0-1) and UI units (0-100) using a factor of 100.
 */
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

/**
 * @brief Container for percentage values with default scaling
 *
 * Converts between model units and UI percentage based on a provided default value.
 */
class PercentageContainer : public DataContainer
{
public:
    /**
     * @brief Constructs a PercentageContainer
     * @param name Container identifier
     * @param path Path in model
     * @param type Type identifier
     * @param defaultValue Reference value for percentage calculation
     * @param parent Parent ModelWrapper
     */
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
    double m_defaultValue;  ///< Reference value for percentage calculations
};

/**
 * @brief Container for coefficient values
 *
 * Direct value conversion without scaling.
 */
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

/**
 * @brief Container for wall strain values with patch support
 *
 * Handles wall strain parameters across multiple patches, updating all patches
 * when values change.
 */
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

/**
 * @brief Container for wall patch millisecond values
 *
 * Handles time values across multiple wall patches with millisecond conversion.
 */
class WallMSContainer : public DataContainer
{
public:
    /**
     * @brief Constructs a WallMSContainer
     * @param name Container identifier
     * @param path Base path in model
     * @param type Type identifier
     * @param defaultValue Default time value
     * @param parent Parent ModelWrapper
     */
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
    int n_patch = qQNaN();        ///< Number of patches
    QString wallPath;   ///< Base path to wall
    QString paramPart;  ///< Parameter path component
    QString patchPart;  ///< Patch path component
    double m_defaultValue;  ///< Default time value
};

/**
 * @brief Container for wall coefficient values
 *
 * Handles coefficient values across multiple wall patches without scaling.
 */
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

/**
 * @brief Container for wall percentage values
 *
 * Handles percentage values across multiple wall patches with scaling based on default value.
 */
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

/**
 * @brief Container for hemoglobin concentration values
 *
 * Converts between model units [g/dL] and UI [mmol/L] units using a factor of 0.6206.
 */
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
