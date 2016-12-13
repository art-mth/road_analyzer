#include "road_analyzer_impl.h"

#include <street_environment/bounding_box.h>

void RoadAnalyzerImpl::markObstacles(
    const street_environment::BasicObstacleVector& obstacles,
    street_environment::RoadMatrix& roadMatrix) {
    for (const auto& obstacle : obstacles) {
        markObstacleCells(obstacle, roadMatrix);
    }
}

bool RoadAnalyzerImpl::markObstacleCells(
    const street_environment::BasicObstacle& obstacle,
    street_environment::RoadMatrix& roadMatrix) {
    street_environment::RoadMatrixCell startCell;
    street_environment::BoundingBox2f boundingBox(obstacle.boundingBox());
    if (!roadMatrix.findCell(boundingBox.corners()[0], &startCell)) {
        return false;
    }
    street_environment::RoadMatrixCell endCell;
    if (!roadMatrix.findCell(boundingBox.corners()[2], &endCell)) {
        return false;
    }
    for (int x = startCell.x; x <= endCell.x; x++) {
        for (int y = startCell.y; y <= endCell.y; y++) {
            roadMatrix.cell(x, y).hasObstacle = true;
        }
    }
    return true;
}
