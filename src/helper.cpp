#include <QByteArray>

#include "helper.h"

int Helper::getPalettePos (const QByteArray &data) {
    int pos = data.indexOf(QByteArray::fromHex(SEARCH_HEX_1));

    if (pos == -1)
        pos = data.indexOf(QByteArray::fromHex(SEARCH_HEX_2));

    if (pos != -1)
        return pos + 32;

    return -1;
}
