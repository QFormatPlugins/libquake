#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "brush.h"
#include "types.h"

namespace quakelib::map {
  class BaseEntity {
  public:
    enum eEntityType {
      POINT = 0,
      SOLID = 1,
    };

    explicit BaseEntity(eEntityType type) : type(type) {};

    eEntityType type{};
    std::string classname;
    float angle{};
    fvec3 origin{};
    std::string tbType;
    std::string tbName;
    std::map<std::string, std::string> attributes;
    friend class QMapFile;
  };

  class PointEntity : public BaseEntity {
  public:
    PointEntity() : BaseEntity(POINT) {};
  };

  class SolidEntity : public BaseEntity {
  public:
    SolidEntity() : BaseEntity(SOLID) {};

    [[nodiscard]] std::string ClassName() const { return classname; };

    [[nodiscard]] bool ClassContains(const std::string &substr) const {
      return classname.find(substr) != std::string::npos;
    };

    const std::vector<Brush> &GetOriginalBrushes() { return brushes; }

    const std::vector<Brush> &GetBrushes() {
      if (wasClipped) {
        return clippedBrushes;
      }
      return brushes;
    }

    const std::vector<Brush> &GetClippedBrushes() const { return clippedBrushes; }

    const fvec3 &GetCenter() const { return center; }

    const fvec3 &GetMin() const { return min; }

    const fvec3 &GetMax() const { return max; }

    // stats getter
    size_t StatsClippedFaces() const { return stats_clippedFaces; }

  private:
    void generateMesh(const std::map<int, Face::eFaceType> &faceTypes,
                      const std::map<int, textureBounds> &texBounds);
    void csgUnion();

    std::vector<Brush> brushes;
    std::vector<Brush> clippedBrushes;
    bool hasPhongShading{};
    std::vector<int> textureIDs;
    size_t stats_clippedFaces{};
    bool wasClipped = false;

    fvec3 center{0};
    fvec3 min{0};
    fvec3 max{0};

    friend class QMapFile;
    friend class QMap;
  };

  using BaseEntityPtr = std::shared_ptr<BaseEntity>;
  using SolidEntityPtr = std::shared_ptr<SolidEntity>;
  using PointEntityPtr = std::shared_ptr<PointEntity>;
} // namespace quakelib::map
