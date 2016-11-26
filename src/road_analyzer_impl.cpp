#include "road_analyzer_impl.h"

bool RoadAnalyzerImpl::markNewObstacles(
    const street_environment::BoundingBoxVector& obstacles,
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
    const street_environment::BoundingBox& obstacle,
    street_environment::RoadMatrix& roadMatrix) {
    const lms::math::vertex2f& startVertex = obstacle.corners()[3];
    const street_environment::RoadMatrixCell* startCell =
        findCell(startVertex, roadMatrix);
    if (startCell == nullptr) {
        return false;
    }
    const lms::math::vertex2f& endVertex = obstacle.corners()[1];
    const street_environment::RoadMatrixCell* endCell =
        findCell(endVertex, roadMatrix);
    if (endCell == nullptr) {
        return false;
    }
    for (int x = startCell->x; x <= endCell->x; x++) {
        for (int y = startCell->y; y <= endCell->y; y++) {
            roadMatrix.cell(x, y).hasObstacle = true;
            m_obstacleCells.push_back(roadMatrix.cell(x, y));
        }
    }
    return true;
}

const street_environment::RoadMatrixCell* RoadAnalyzerImpl::findCell(
    const lms::math::vertex2f& v,
    const street_environment::RoadMatrix& roadMatrix) {
    for (int x = 0; x < roadMatrix.length(); x++) {
        for (int y = 0; y < roadMatrix.width(); y++) {
            const street_environment::RoadMatrixCell& rmc =
                roadMatrix.cell(x, y);
            if (rmc.contains(v)) {
                return &rmc;
            }
        }
    }
    return nullptr;
}

void RoadAnalyzerImpl::moveExistingObstacles(
    street_environment::RoadMatrix& roadMatrix) {
    for(const auto& cell: m_obstacleCells) {
        roadMatrix.cell(cell.x, cell.y).hasObstacle = true;
    }
}
