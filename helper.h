#ifndef HELPER_H
#define HELPER_H

#include <string_view>
#include <QMessageBox>
#include <QFileDialog>


class Helper {
public:
    Helper() = delete;
    static int getPalettePos (QByteArray& data);
private:
    static inline constexpr std::string_view HEX1 = "00600000426F6D426C69737300000000425921C80D5341540000000000000000";
    static inline constexpr std::string_view HEX2 = "BA7F0000426F6D426C69737300000000425921C80D5341540000000000000000";
};

#endif // HELPER_H
