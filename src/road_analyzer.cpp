#include "road_analyzer.h"

namespace {
const float kMaxBadness = 10;
const float kMaxInfluence = 9;
const float kMinInfluence = 1;
}

bool RoadAnalyzer::markBadPosition(lms::math::vertex2f v) {
    for (int x = 0; x < roadMatrix->length(); x++) {
        for (int y = 0; y < roadMatrix->width(); y++) {
            street_environment::RoadMatrixCell &cell = roadMatrix->cell(x, y);
            if (cell.contains(v)) {
                cell.badness(kMaxBadness);
                markAdjacentCellsBad(x, y);
                return true;
            }
        }
    }
    return false;
}

bool RoadAnalyzer::markAdjacentCellsBad(int x, int y) {
    float cellWidth = config().get<float>("laneWidth", 0.4) /
                      config().get<int>("cellsPerLane", 8);
    float cellLength = cellWidth;

    int xCellsToInfluence =
        config().get<int>("xObstacleInfluence", 0.5) / cellLength;
    float xBadnessStep = (kMaxInfluence - kMinInfluence) / xCellsToInfluence;
    for (int i = 1; i <= xCellsToInfluence; i++) {
        float badness =
            kMinInfluence + xBadnessStep * (xCellsToInfluence - i + 1);
        if (x + i < roadMatrix->length()) {
            street_environment::RoadMatrixCell &cell =
                roadMatrix->cell(x + i, y);
            if (badness > cell.badness()) {
                cell.badness(badness);
            }
        }
        if (x - i >= 0) {
            street_environment::RoadMatrixCell &cell =
                roadMatrix->cell(x - i, y);
            if (badness > cell.badness()) {
                cell.badness(badness);
            }
        }
    }

    int yCellsToInfluence = config().get<int>("yObstacleInfluence", 0.1) /
                            cellWidth;
    float yBadnessStep = (kMaxInfluence - kMinInfluence) / yCellsToInfluence;
    for (int j = 1; j <= yCellsToInfluence; j++) {
        float badness =
            kMinInfluence + yBadnessStep * (yCellsToInfluence - j + 1);
        if (y + j < roadMatrix->width()) {
            street_environment::RoadMatrixCell &cell =
                roadMatrix->cell(x, y + j);
            if (badness > cell.badness()) {
                cell.badness(badness);
            }
        }
        if (y - j >= 0) {
            street_environment::RoadMatrixCell &cell =
                roadMatrix->cell(x, y - j);
            if (badness > cell.badness()) {
                cell.badness(badness);
            }
        }
    }

    return true;
}

bool RoadAnalyzer::markSidelineBad() {
    return true;
}

bool RoadAnalyzer::adjustBadnessAroundOptimalLane() {
    return true;
}

bool RoadAnalyzer::initialize() {
    line = readChannel<lms::math::polyLine2f>("LINE");
    obstacles =
        readChannel<street_environment::EnvironmentObjects>("OBSTACLES");
    roadMatrix = writeChannel<street_environment::RoadMatrix>("ROADMATRIX");
    return true;
}

bool RoadAnalyzer::deinitialize() {
    return true;
}

bool RoadAnalyzer::cycle() {
    roadMatrix->aroundLine(*line, config().get<float>("laneWidth", 0.4),
                           config().get<int>("cellsPerLane", 8));
    for (street_environment::EnvironmentObjectPtr ptr : obstacles->objects) {
        if (ptr->getType() == street_environment::Obstacle::TYPE) {
            std::shared_ptr<street_environment::Obstacle> obst =
                std::dynamic_pointer_cast<street_environment::Obstacle>(ptr);
            for (const lms::math::vertex2f &v : obst->points()) {
                markBadPosition(v);
            }
        }
    }
    return true;
}

void RoadAnalyzer::configsChanged() {}
