#pragma once

#include <string_view>

#include <QByteArray>
#include <QHash>

#include "hexCodes.h"

class Helper {
public:
    Helper() = delete;
    static int getPalettePos (const QByteArray &data);

    static inline const QHash<QString, QByteArray> palettes = {
        {"Nestopia Emulator's YUV",                                 QByteArray::fromHex(NESTOPIA_YUV_HEX)},
        {"Nestopia Emulator's RGB",                                 QByteArray::fromHex(NESTOPIA_RGB_HEX)},
        {"FireBrandX's FBX Composite Direct",                       QByteArray::fromHex(COMPOSITE_DIRECT_HEX)},
        {"Wavebeam",                                                QByteArray::fromHex(WAVEBEAM_HEX)},
        {"Wavebeam (Alternative Version)",                          QByteArray::fromHex(WAVEBEAM_ALT_HEX)},
        {"FCEUX NES Emulator's colorful NES",                       QByteArray::fromHex(FCEUX_COLORFUL_HEX)},
        {"Original NES Wii VC",                                     QByteArray::fromHex(ORIGINAL_WII_VC_HEX)},
        {"Restored NES Wii VC",                                     QByteArray::fromHex(RESTORED_WII_VC_HEX)},
        {"Animal Crossing (GameCube) NES Emulator",                 QByteArray::fromHex(ANIMAL_CROSSING_HEX)},
        {"Nintendo 3DS Virtual Console without dark enabled",       QByteArray::fromHex(VC_3DS_HEX)},
        {"NES Classic Mini",                                        QByteArray::fromHex(NES_CLASSIC_MINI_HEX)},
        {"NES Remix U game series (Wii U) NES",                     QByteArray::fromHex(NES_REMIX_HEX)},
        {"Original Mega Man NES",                                   QByteArray::fromHex(ORIGINAL_MEGAMAN_HEX)},
        {"Rockman 9 Modern NES",                                    QByteArray::fromHex(ROCKMAN_9_HEX)},
        {"Mega Man Legacy Collection (Nintendo 3DS) Modern NES",    QByteArray::fromHex(MEGAMAN_LEGACY_COLLECTION_HEX)}
    };

    static inline const QHash<QString, QString> images = {
        {"Nestopia Emulator's YUV",                                 ":/images/nestopia_yuv.png"},
        {"Nestopia Emulator's RGB",                                 ":/images/nestopia_rgb.png"},
        {"FireBrandX's FBX Composite Direct",                       ":/images/composite_direct.png"},
        {"Wavebeam",                                                ":/images/wavebeam_1.png"},
        {"Wavebeam (Alternative Version)",                          ":/images/wavebeam_2.png"},
        {"FCEUX NES Emulator's colorful NES",                       ":/images/fceux_colorful.png"},
        {"Original NES Wii VC",                                     ":/images/original_wii_vc.png"},
        {"Restored NES Wii VC",                                     ":/images/restored_wii_vc.png"},
        {"Animal Crossing (GameCube) NES Emulator",                 ":/images/animal_crossing.png"},
        {"Nintendo 3DS Virtual Console without dark enabled",       ":/images/3ds_vc.png"},
        {"NES Classic Mini",                                        ":/images/nes_classic_mini.png"},
        {"NES Remix U game series (Wii U) NES",                     ":/images/nes_remix.png"},
        {"Original Mega Man NES",                                   ":/images/original_megaman.png"},
        {"Rockman 9 Modern NES",                                    ":/images/rockman_9.png"},
        {"Mega Man Legacy Collection (Nintendo 3DS) Modern NES",    ":/images/megaman_legacy_collection.png"}
    };
private:
    static inline constexpr std::string_view HEX1 = SEARCH_HEX_1;
    static inline constexpr std::string_view HEX2 = SEARCH_HEX_2;
};
