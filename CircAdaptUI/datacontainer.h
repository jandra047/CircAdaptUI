#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QJsonObject>
#include <any>

class ModelWrapper;

class DataContainer : public QObject
{
    Q_OBJECT
public:
    DataContainer(const QString& name, const QString& path, const QString& mType, ModelWrapper* parent = Q_NULLPTR) :
        QObject((QObject*)parent),
        mName(name), mPath(path), mType(mType),
        mw(*parent)
        {};
    ~DataContainer() = default;
    QString getType() { return mType; };
    QString getName() { return mName; };
    QString getPath() { return mPath; };
    virtual std::any model_to_ui(std::any value) const = 0;
    virtual std::any ui_to_model(std::any value) const = 0;
protected:
    QString mName;
    QString mPath;
    QString mType;
    ModelWrapper& mw;
};


class DataContainerFactory
{
public:
    static DataContainer* createSignal(const QJsonObject& json, ModelWrapper* parent = Q_NULLPTR);
    DataContainerFactory();
    DataContainerFactory(const DataContainerFactory&) = delete;
    DataContainerFactory& operator=(const DataContainerFactory&) = delete;
    ~DataContainerFactory() = default;
};

#endif // DATACONTAINER_H
