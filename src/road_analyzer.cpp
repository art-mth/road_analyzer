#include "road_analyzer.h"

bool RoadAnalyzer::markBadPosition(const lms::math::vertex2f &v,
                                   const float &badness) {
    for (int x = 0; x < roadMatrix->length(); x++) {
        for (int y = 0; y < roadMatrix->width(); y++) {
            street_environment::RoadMatrixCell &cell = roadMatrix->cell(x, y);
            if (cell.contains(v)) {
                cell.badness += badness;
                if (cell.badness < 0) {
                    cell.badness = 0;
                } else if (cell.badness > 1) {
                    cell.badness = 1;
                }
                return true;
            }
        }
    }
    return false;
}

bool RoadAnalyzer::initialize() {
    line = readChannel<lms::math::polyLine2f>("LINE");
    obstacles =
        readChannel<street_environment::EnvironmentObjects>("OBSTACLES");
    roadMatrix = writeChannel<street_environment::RoadMatrix>("ROADMATRIX");
    return true;
}

bool RoadAnalyzer::deinitialize() { return true; }

bool RoadAnalyzer::cycle() {
    roadMatrix->aroundLine(*line, config().get<float>("laneWidth", 0.4),
                           config().get<int>("cellsPerLane", 8));
    for (street_environment::EnvironmentObjectPtr ptr : obstacles->objects) {
        if (ptr->getType() == street_environment::Obstacle::TYPE) {
            std::shared_ptr<street_environment::Obstacle> obst =
                std::dynamic_pointer_cast<street_environment::Obstacle>(ptr);
            for (const lms::math::vertex2f &v : obst->points()) {
                // TODO sinnvolle delta badness-werte ermitteln
                markBadPosition(v, 0.1);
            }
        }
    }
    return true;
}

void RoadAnalyzer::configsChanged() {}
