#ifndef ROAD_ANALYZER_IMPL_H
#define ROAD_ANALYZER_IMPL_H

#include <street_environment/basic_obstacle.h>
#include <street_environment/roadmatrix.h>

class RoadAnalyzerImpl {
   public:
    void markObstacles(const street_environment::BasicObstacleVector& obstacles,
                       street_environment::RoadMatrix& roadMatrix);

    bool markObstacleCells(const street_environment::BasicObstacle& obstacle,
                           street_environment::RoadMatrix& roadMatrix);
};

#endif  // ROAD_ANALYZER_IMPL_H
