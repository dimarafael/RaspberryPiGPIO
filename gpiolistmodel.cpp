#include "gpiolistmodel.h"

GPIOListModel::GPIOListModel(QObject *parent)
    :QAbstractListModel {parent}
{
    GPIOitem *gpioItem;
    for(int i = 1; i <= 40; i++){
        gpioItem = new GPIOitem(parent);
        switch (i) {
        case 1: gpioItem->setName("3.3V"); break;
        case 2: gpioItem->setName("5V"); break;
        case 3: gpioItem->setGPIOnumber(2); break;
        case 4: gpioItem->setName("5V"); break;
        case 5: gpioItem->setGPIOnumber(3); break;
        case 6: gpioItem->setName("GND"); break;
        case 7: gpioItem->setGPIOnumber(4); break;
        case 8: gpioItem->setGPIOnumber(14); break;
        case 9: gpioItem->setName("GND"); break;
        case 10: gpioItem->setGPIOnumber(15); break;
        case 11: gpioItem->setGPIOnumber(17); break;
        case 12: gpioItem->setGPIOnumber(18); break;
        case 13: gpioItem->setGPIOnumber(27); break;
        case 14: gpioItem->setName("GND"); break;
        case 15: gpioItem->setGPIOnumber(22); break;
        case 16: gpioItem->setGPIOnumber(23); break;
        case 17: gpioItem->setName("3.3V"); break;
        case 18: gpioItem->setGPIOnumber(24); break;
        case 19: gpioItem->setGPIOnumber(10); break;
        case 20: gpioItem->setName("GND"); break;
        case 21: gpioItem->setGPIOnumber(9); break;
        case 22: gpioItem->setGPIOnumber(25); break;
        case 23: gpioItem->setGPIOnumber(11); break;
        case 24: gpioItem->setGPIOnumber(8); break;
        case 25: gpioItem->setName("GND"); break;
        case 26: gpioItem->setGPIOnumber(7); break;
        case 27: gpioItem->setGPIOnumber(0); break;
        case 28: gpioItem->setGPIOnumber(1); break;
        case 29: gpioItem->setGPIOnumber(5); break;
        case 30: gpioItem->setName("GND"); break;
        case 31: gpioItem->setGPIOnumber(6); break;
        case 32: gpioItem->setGPIOnumber(12); break;
        case 33: gpioItem->setGPIOnumber(13); break;
        case 34: gpioItem->setName("GND"); break;
        case 35: gpioItem->setGPIOnumber(19); break;
        case 36: gpioItem->setGPIOnumber(16); break;
        case 37: gpioItem->setGPIOnumber(26); break;
        case 38: gpioItem->setGPIOnumber(20); break;
        case 39: gpioItem->setName("GND"); break;
        case 40: gpioItem->setGPIOnumber(21); break;
        default:
            break;
        }
        m_GPIOList.append(gpioItem);
    }

    QSettings settings("Dima", "RaspberryPiGPIO");
    int settingsSize = settings.beginReadArray("GPIO");
    qDebug() << "Settings size =" << settingsSize;
    if(settingsSize == m_GPIOList.size()){ // read settings
        qDebug() << "Reading settings";
        for(int i = 0; i < settingsSize; i++){
            settings.setArrayIndex(i);
            int mode = settings.value("mode").toInt();
            if(mode >= 0 && mode < 2) m_GPIOList[i]->setMode(mode);
            else m_GPIOList[i]->setMode(0);
        }
        settings.endArray();
    } else{ // create settings
        qDebug() << "Creating settings";
        settings.endArray();
        settings.beginWriteArray("GPIO");
        for(int i = 0; i < m_GPIOList.size(); i++){
            settings.setArrayIndex(i);
            settings.setValue("mode", 0);
        }
        settings.endArray();
    }
}

int GPIOListModel::rowCount(const QModelIndex &parent) const
{
    return m_GPIOList.size();
}

QVariant GPIOListModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && index.row() >= 0 && index.row() < m_GPIOList.size()){
        GPIOitem *item = m_GPIOList[index.row()];
        switch((Role)role){
        case GPIONameRole: return item->name();
        case GPIONumberRole: return item->GPIOnumber();
        case GPIOStateRole: return item->state();
        case GPIOModeRole: return item->mode();
        }
    }
    return {};
}

QHash<int, QByteArray> GPIOListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[GPIONameRole] = "gpioName";
    names[GPIONumberRole] = "gpioNumber";
    names[GPIOStateRole] = "gpioState";
    names[GPIOModeRole] = "gpioMode";
    return names;
}

void GPIOListModel::changeMode(int pos, int mode)
{
    beginResetModel();
    m_GPIOList[pos]->setMode(mode);
    endResetModel();
    QSettings settings("Dima", "RaspberryPiGPIO");
    settings.beginWriteArray("GPIO", 40);
    settings.setArrayIndex(pos);
    settings.setValue("mode", mode);
    settings.endArray();
}
