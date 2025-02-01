#include <quakelib/wad/palette.h>

#include <algorithm>
#include <fstream>
#include <iterator>

namespace quakelib::wad {
  const color Palette::GetColor(int index) const {
    if (index < 0 || index >= colors.size()) {
      throw std::runtime_error("color index out of range");
    }

    return colors[index];
  }

} // namespace quakelib::wad