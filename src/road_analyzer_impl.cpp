#include "road_analyzer_impl.h"

void RoadAnalyzerImpl::markObstacles(
    const street_environment::BoundingBox2fVector& obstacles,
    street_environment::RoadMatrix& roadMatrix) {
    for (const auto& obstacle : obstacles) {
        markObstacleCells(obstacle, roadMatrix);
    }
}

bool RoadAnalyzerImpl::markObstacleCells(
    const street_environment::BoundingBox2f& obstacle,
    street_environment::RoadMatrix& roadMatrix) {
    street_environment::RoadMatrixCell startCell;
    if (!roadMatrix.findCell(obstacle.corners()[0], &startCell)) {
        return false;
    }
    street_environment::RoadMatrixCell endCell;
    if (!roadMatrix.findCell(obstacle.corners()[2], &endCell)) {
        return false;
    }
    for (int x = startCell.x; x <= endCell.x; x++) {
        for (int y = startCell.y; y <= endCell.y; y++) {
            roadMatrix.cell(x, y).hasObstacle = true;
        }
    }
    return true;
}
