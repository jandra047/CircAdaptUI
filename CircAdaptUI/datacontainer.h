#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QJsonObject>

class ModelWrapper;
class Buffer;

/**
 * @brief A bridge between model data and UI representations with automatic value conversion
 *
 * DataContainer serves as an abstraction layer that handles the conversion between internal
 * model values and their user interface representations. It provides type-safe data access
 * and automated unit conversion for various physical quantities.
 *
 * The class is designed to work with a ModelWrapper instance and supports different types
 * of data (pressure, volume, flow, etc.) through specialized derived classes. Each derived
 * class implements specific conversion logic appropriate for its data type.
 *
 * Example usage:
 * @code
 * // Create a pressure container
 * DataContainer* pc = new PressureContainer("aorticPressure", "Model.SyArt.p", "pressure", modelWrapper);
 *
 * // Get value (automatically converts from model to UI units)
 * QVariant value = pressure->get();
 *
 * // Update value (automatically converts from UI to model units)
 * pressure->updateParam(QVariant(120.0));
 * @endcode
 *
 * @note The class is abstract and requires derived classes to implement model_to_ui() and
 * ui_to_model() for specific type conversions.
 *
 * @see ModelWrapper, Buffer, PressureContainer, VolumeContainer
 */
class DataContainer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a DataContainer with specified parameters
     * @param name Identifier name for the container
     * @param path Path to the parameter in the model
     * @param mType Type identifier string
     * @param parent Parent ModelWrapper instance
     */
    DataContainer(const QString& name, const QString& path, const QString& mType, ModelWrapper* parent = Q_NULLPTR);

    /**
     * @brief Gets the type identifier string
     * @return String identifying the container type
     */
    QString getType() { return mType; };

    /**
     * @brief Gets the Qt meta type information
     * @return QMetaType::Type of the contained data
     */
    QMetaType::Type getMetaType() { return mMetaType; };

    /**
     * @brief Gets the container name
     * @return Name identifier of the container
     */
    QString getName() { return mName; };

    /**
     * @brief Gets the model parameter path
     * @return Path to the parameter in the model
     */
    QString getPath() { return mPath; };

    /**
     * @brief Converts model values to UI representation
     * @param variant Value in model units
     * @return Value converted to UI units
     */
    virtual QVariant model_to_ui(QVariant variant) const = 0;

    /**
     * @brief Converts UI values to model representation
     * @param variant Value in UI units
     * @return Value converted to model units
     */
    virtual QVariant ui_to_model(QVariant variant) const = 0;

    /**
     * @brief Updates the model parameter with a new value
     * @param variant New value in UI units (will be converted to model units)
     */
    virtual void updateParam(QVariant variant) const;

    /**
     * @brief Gets the current value from the model
     * @return Current value converted to UI units
     */
    virtual QVariant get();

    /**
     * @brief Updates a buffer with the current value
     * @param buffer Buffer to update
     */
    virtual void updateBuffer(Buffer& buffer);

protected:
    QString mName;      ///< Container name identifier
    QString mPath;      ///< Path to parameter in model
    QString mType;      ///< Type identifier string
    ModelWrapper& mw;   ///< Reference to model wrapper
    QMetaType::Type mMetaType = QMetaType::UnknownType;  ///< Qt meta type information
};

/**
 * @brief Factory class for creating specialized DataContainer instances
 *
 * DataContainerFactory implements the factory pattern to create appropriate DataContainer
 * instances based on configuration data. It supports creation of all specialized container
 * types (pressure, volume, flow, etc.) and handles their initialization.
 *
 * Example usage:
 * @code
 * QJsonObject config;
 * config["name"] = "Left atrial contractility";
 * config["path"] = "Model.Peri.La.Sf_act";
 * config["type"] = "percentage";
 * config["default"] = 100.0;
 *
 * Buffer* buffer = new Buffer();
 * ModelWrapper* wrapper = new ModelWrapper(buffer);
 * DataContainer* container = DataContainerFactory::createContainer(config, wrapper);
 * @endcode
 *
 * @see DataContainer, PressureContainer, VolumeContainer
 */
class DataContainerFactory
{
public:
    /**
     * @brief Creates a DataContainer instance based on JSON configuration
     * @param json Configuration object containing container parameters
     * @param parent Parent ModelWrapper instance
     * @return Pointer to created DataContainer instance
     * @throws std::invalid_argument if container type is unknown
     *
     * The JSON configuration object should contain:
     * - name: Container identifier
     * - path: Path to parameter in model
     * - type: Container type string
     * - default: Default value (optional, used by some container types)
     */
    static DataContainer* createContainer(const QJsonObject& json, ModelWrapper* parent = Q_NULLPTR);

    /**
     * @brief Default constructor
     */
    DataContainerFactory();

    /**
     * @brief Copy constructor (deleted)
     */
    DataContainerFactory(const DataContainerFactory&) = delete;

    /**
     * @brief Assignment operator (deleted)
     */
    DataContainerFactory& operator=(const DataContainerFactory&) = delete;
};

#endif // DATACONTAINER_H
