#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QJsonObject>

class ModelWrapper;

class DataContainer : public QObject
{
    Q_OBJECT
public:
    DataContainer(const QString& name, const QString& path, const QString& mType, ModelWrapper* parent = Q_NULLPTR) :
        QObject((QObject*)parent),
        mName(name), mPath(path), mType(mType),
        mw(*parent)
        {
        };
    ~DataContainer() = default;
    QString getType() { return mType; };
    QMetaType::Type getMetaType() { return mMetaType; };
    QString getName() { return mName; };
    QString getPath() { return mPath; };
    virtual QVariant model_to_ui(QVariant variant) const = 0;
    virtual QVariant ui_to_model(QVariant variant) const = 0;
    virtual void updateParam(QVariant variant) const;
    virtual QVariant get();
protected:
    QString mName;
    QString mPath;
    QString mType;
    ModelWrapper& mw;
    QMetaType::Type mMetaType = QMetaType::UnknownType;
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
