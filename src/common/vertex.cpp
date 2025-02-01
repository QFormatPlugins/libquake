#include <quakelib/common/vertex.h>

namespace quakelib {
  inline bool Vertex::inList(const std::vector<Vertex> &list) {
    for (auto const &v : list) {
      if (v.point == point)
        return true;
    }
    return false;
  }
} // namespace quakelib