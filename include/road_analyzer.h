#ifndef ROAD_ANALYZER_H
#define ROAD_ANALYZER_H

#include <memory>

#include <lms/math/polyline.h>
#include <lms/math/pose.h>
#include <lms/module.h>
#include <street_environment/basic_obstacle.h>
#include <street_environment/roadmatrix.h>
#include "road_analyzer_impl.h"

/**
 * @brief LMS module road_analyzer
 * Given the center line and a BoundingBox vector creates a matrix
 * representation of the road. The module assumes that the given points are
 * accurate.
 **/
class RoadAnalyzer : public lms::Module {
   public:
    bool initialize() override;
    bool deinitialize() override;
    bool cycle() override;

   private:
    lms::math::Pose2D getDeltaPose();

    lms::Time lastUpdate;

    /////////////////////////////// Data Channels //////////////////////////////
    lms::ReadDataChannel<lms::math::Pose2DHistory> poseHistory;
    lms::ReadDataChannel<lms::math::polyLine2f> centerLine;
    lms::ReadDataChannel<street_environment::BasicObstacleVector> obstacles;
    lms::WriteDataChannel<street_environment::RoadMatrix> roadMatrix;

    std::unique_ptr<RoadAnalyzerImpl> impl;
};

#endif  // ROAD_ANALYZER_H
