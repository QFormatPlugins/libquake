#pragma once

#include <functional>
#include <quakelib/common/entities.h>
#include <sstream>

namespace quakelib {

  using EntityParsedFunc = std::function<void(ParsedEntity *)>;

  class EntityParser {

  public:
    static void ParseEntites(const std::string &buffer, EntityParsedFunc fn);
  };

} // namespace quakelib