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
                cell.hasObstacle = true;
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
                //TODO Das macht so wenig Sinn, ein falsches Messergebnis ergibt ein nicht-befahrbares Element. Deswegen gab es die badness
                //TODO Wenn du etwas an meinem Code änderst solltest du das davor absprechen, es hatte einen Sinn
                markBadPosition(v);

            }
        }
    }
    return true;
}

void RoadAnalyzer::configsChanged() {}
