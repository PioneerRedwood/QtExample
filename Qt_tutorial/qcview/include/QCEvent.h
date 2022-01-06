#include <QtCore/qglobal.h>
#include <QObject>
#include <QString>
#include "QCUserDefined.h"

class QCEvent : public QObject {
    Q_OBJECT
public:
    QCEvent();
    QCEvent(const QString& name);
    void setEventName(const QString& name);
    
    template<typename T>
    void setPropertyTemp(const QString& key, T value);
};