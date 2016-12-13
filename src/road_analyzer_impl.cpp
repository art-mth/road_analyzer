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
    street_environment::RoadMatrixCell endCell;
    street_environment::BoundingBox2f boundingBox(obstacle.boundingBox());
    if (roadMatrix.findCell(boundingBox.corners()[0], &startCell)) {
        if (roadMatrix.findCell(boundingBox.corners()[2], &endCell)) {
            for (int x = startCell.x; x <= endCell.x; x++) {
                for (int y = startCell.y; y <= endCell.y; y++) {
                    roadMatrix.cell(x, y).hasObstacle = true;
                }
            }
            return true;
        } else {
            street_environment::RoadMatrixCell cell;
            for (const auto& point : obstacle.points()) {
                roadMatrix.findCell(point, &cell);
                roadMatrix.cell(cell.x, cell.y).hasObstacle = true;
            }
            return true;
        }
    } else {
        if (!roadMatrix.findCell(boundingBox.corners()[2], &endCell)) {
            return false;
        } else {
            street_environment::RoadMatrixCell cell;
            for (const auto& point : obstacle.points()) {
                roadMatrix.findCell(point, &cell);
                roadMatrix.cell(cell.x, cell.y).hasObstacle = true;
            }
            return true;
        }
    }
}
