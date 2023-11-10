#ifndef GPIOLISTMODEL_H
#define GPIOLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QSettings>
#include "gpioitem.h"

class GPIOListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit GPIOListModel(QObject *parent = nullptr);

    enum Role{
        GPIONameRole = Qt::UserRole + 1,
        GPIONumberRole,
        GPIOStateRole,
        GPIOModeRole
    };

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

signals:
    void setGPIOout(int GPIOnumber, bool state);

public slots:
    void changeMode(int pos, int mode);

private:
    QList<GPIOitem*> m_GPIOList;
};

#endif // GPIOLISTMODEL_H
