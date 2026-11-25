#include <QByteArray>
#include <QString>
#include "patcher.h"
#include "hexCodes.h"

int getPalettePos (const QByteArray &data) {
    int pos = data.indexOf(QByteArray::fromHex(SEARCH_HEX_1));

    if (pos == -1)
        pos = data.indexOf(QByteArray::fromHex(SEARCH_HEX_2));

    if (pos != -1)
        return pos + 32;

    return -1;
}

QByteArray getPaletteHexCodes(Palette currentPalette) {
    switch (currentPalette) {
        case NESTOPIA_YUV:
            return QByteArray::fromHex(NESTOPIA_YUV_HEX);
        case NESTOPIA_RGB:
            return QByteArray::fromHex(NESTOPIA_RGB_HEX);
        case COMPOSITE_DIRECT:
            return QByteArray::fromHex(COMPOSITE_DIRECT_HEX);
        case WAVEBEAM:
            return QByteArray::fromHex(WAVEBEAM_HEX);
        case WAVEBEAM_ALT:
            return QByteArray::fromHex(WAVEBEAM_ALT_HEX);
        case FCEUX_COLORFUL:
            return QByteArray::fromHex(FCEUX_COLORFUL_HEX);
        case ORIGINAL_WII_VC:
            return QByteArray::fromHex(ORIGINAL_MEGAMAN_HEX);
        case RESTORED_WII_VC:
            return QByteArray::fromHex(RESTORED_WII_VC_HEX);
        case ANIMAL_CROSSING:
            return QByteArray::fromHex(ANIMAL_CROSSING_HEX);
        case VC_3DS:
            return QByteArray::fromHex(VC_3DS_HEX);
        case NES_CLASSIC_MINI:
            return QByteArray::fromHex(NES_CLASSIC_MINI_HEX);
        case NES_REMIX:
            return QByteArray::fromHex(NES_REMIX_HEX);
        case ORIGINAL_MEGAMAN:
            return QByteArray::fromHex(ORIGINAL_MEGAMAN_HEX);
        case ROCKMAN_9:
            return QByteArray::fromHex(ROCKMAN_9_HEX);
        case MEGAMAN_LEGACY_COLLECTION:
            return QByteArray::fromHex(MEGAMAN_LEGACY_COLLECTION_HEX);
        default:
            return nullptr;
    }
}
