#ifndef ROAD_ANALYZER_IMPL_H
#define ROAD_ANALYZER_IMPL_H

#include <street_environment/bounding_box.h>
#include <street_environment/roadmatrix.h>

class RoadAnalyzerImpl {
   public:
    void markNewObstacles(
        const street_environment::BoundingBoxVector& obstacles,
        street_environment::RoadMatrix& roadMatrix);
    void moveExistingObstacles(street_environment::RoadMatrix& roadMatrix);
};

#endif  // ROAD_ANALYZER_IMPL_H
