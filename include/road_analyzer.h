#ifndef ROAD_ANALYZER_H
#define ROAD_ANALYZER_H

#include <lms/module.h>
#include <lms/math/polyline.h>
#include <lms/math/vertex.h>
#include <street_environment/obstacle.h>
#include <street_environment/road.h>

/**
 * @brief LMS module road_analyzer
 **/
class RoadAnalyzer : public lms::Module {
    lms::ReadDataChannel<lms::math::polyLine2f> line;
    lms::ReadDataChannel<street_environment::EnvironmentObjects> obstacles;
    lms::WriteDataChannel<street_environment::RoadMatrix> roadMatrix;

    bool markBadPosition(lms::math::vertex2f v);
    bool markAdjacentCellsBad(int x, int y);
    bool markSidelineBad();
    bool adjustBadnessAroundOptimalLane();
  public:
    bool initialize() override;
    bool deinitialize() override;
    bool cycle() override;
    void configsChanged() override;
};

#endif // ROAD_ANALYZER_H
