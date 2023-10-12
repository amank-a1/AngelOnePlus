#ifndef MAINHEADERS_H
#define MAINHEADERS_H

#include <QString>

typedef struct ScripMaster {
    QString ExchangeSeg;
    QString Expiry;
    QString InstrumentType;
    QString LotSize;
    QString Name;
    QString StrikePrice;
    QString Symbol;
    QString TickSize;
    QString Token;
}ScripMaster;

#endif // MAINHEADERS_H
