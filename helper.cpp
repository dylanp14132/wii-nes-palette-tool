#include "helper.h"

int Helper::getPalettePos (QByteArray& data) {
    int pos = data.indexOf(QByteArray::fromHex(HEX1.data()));

    if (pos == -1)
        pos = data.indexOf(QByteArray::fromHex(HEX2.data()));

    if (pos != -1)
        return pos + 32;

    return -1;
}