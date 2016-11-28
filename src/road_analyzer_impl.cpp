#include "road_analyzer_impl.h"

bool RoadAnalyzerImpl::markNewObstacles(
    const street_environment::BoundingBox2fVector& obstacles,
    street_environment::RoadMatrix& roadMatrix) {
    m_obstacleCells.clear();
    for (const auto& obstacle : obstacles) {
        if(!markObstacleCells(obstacle, roadMatrix)) {
            return false;
        }
    }
    return true;
}

bool RoadAnalyzerImpl::markObstacleCells(
    const street_environment::BoundingBox2f& obstacle,
    street_environment::RoadMatrix& roadMatrix) {
    street_environment::RoadMatrixCell startCell;
    if (!roadMatrix.findCell(obstacle.corners()[3], &startCell)) {
        return false;
    }
    street_environment::RoadMatrixCell endCell;
    if (!roadMatrix.findCell(obstacle.corners()[1], &endCell)) {
        return false;
    }
    for (int x = startCell.x; x <= endCell.x; x++) {
        for (int y = startCell.y; y <= endCell.y; y++) {
            roadMatrix.cell(x, y).hasObstacle = true;
            m_obstacleCells.push_back(roadMatrix.cell(x, y));
        }
    }
    return true;
}

void RoadAnalyzerImpl::moveExistingObstacles(
    street_environment::RoadMatrix& roadMatrix) {
    for(const auto& cell: m_obstacleCells) {
        roadMatrix.cell(cell.x, cell.y).hasObstacle = true;
    }
}
