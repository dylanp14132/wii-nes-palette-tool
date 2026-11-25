#pragma once

#include <QString>

enum Palette {
    NESTOPIA_YUV,
    NESTOPIA_RGB,
    COMPOSITE_DIRECT,
    WAVEBEAM,
    WAVEBEAM_ALT,
    FCEUX_COLORFUL,
    ORIGINAL_WII_VC,
    RESTORED_WII_VC,
    ANIMAL_CROSSING,
    VC_3DS,
    NES_CLASSIC_MINI,
    NES_REMIX,
    ORIGINAL_MEGAMAN,
    ROCKMAN_9,
    MEGAMAN_LEGACY_COLLECTION,
};

int getPalettePos(const QByteArray &data);
QByteArray getPaletteHexCodes(Palette currentPalette);