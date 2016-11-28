#ifndef ROAD_ANALYZER_IMPL_H
#define ROAD_ANALYZER_IMPL_H

#include <vector>

#include <lms/math/vertex.h>
#include <street_environment/bounding_box.h>
#include <street_environment/roadmatrix.h>

class RoadAnalyzerImpl {
   public:
    bool markNewObstacles(
        const street_environment::BoundingBox2fVector& obstacles,
        street_environment::RoadMatrix& roadMatrix);

    bool markObstacleCells(const street_environment::BoundingBox2f& obstacle,
                           street_environment::RoadMatrix& roadMatrix);

    const street_environment::RoadMatrixCell* findCell(
        const lms::math::vertex2f& v,
        const street_environment::RoadMatrix& roadMatrix);

    void moveExistingObstacles(street_environment::RoadMatrix& roadMatrix);

    std::vector<street_environment::RoadMatrixCell> m_obstacleCells;
};

#endif  // ROAD_ANALYZER_IMPL_H
