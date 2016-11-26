#ifndef ROAD_ANALYZER_H
#define ROAD_ANALYZER_H

#include <lms/math/polyline.h>
#include <lms/math/vertex.h>
#include <lms/module.h>
#include <street_environment/bounding_box.h>
#include <street_environment/roadmatrix.h>
#include <street_environment/street_environment.h>

/**
 * @brief LMS module road_analyzer
 * Given the center line and a stream of obstacles creates a matrix
 * representation of the road. The module assumes that the given points
 * are accurate.
 **/
class RoadAnalyzer : public lms::Module {
   public:
    bool initialize() override;
    bool deinitialize() override;
    bool cycle() override;

   private:
    lms::ReadDataChannel<lms::math::polyLine2f> centerLine;
    lms::ReadDataChannel<bool> newObstacles;
    lms::ReadDataChannel<street_environment::BoundingBoxVector> obstacles;
    lms::WriteDataChannel<street_environment::RoadMatrix> roadMatrix;
};

#endif  // ROAD_ANALYZER_H
