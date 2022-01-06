#pragma once
#include <QString>
#include <QByteArray>
#include <QtCore/qglobal.h>
#include <QMetaType>
#include "QCUserDefined.h"

class QCResourceProvider {
public:
    virtual bool onRequest(const QString& resourceUrl, QByteArray& buffer) = 0;
};