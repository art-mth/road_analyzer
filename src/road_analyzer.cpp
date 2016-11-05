#include "road_analyzer.h"

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
    roadMatrix->aroundLine(*line, config().get<int>("cellsPerLane", 2),
                           config().get<float>("cellWidth", 0.2),
                           config().get<float>("cellLength", 0.4));
    for (street_environment::EnvironmentObjectPtr ptr : obstacles->objects) {
        if (ptr->getType() == street_environment::Obstacle::TYPE) {
            std::shared_ptr<street_environment::Obstacle> obst =
                std::dynamic_pointer_cast<street_environment::Obstacle>(ptr);
            for (const lms::math::vertex2f &v : obst->points()) {
                if (roadMatrix->markBadPosition(v)) {}
            }
        }
    }
    return true;
}

void RoadAnalyzer::configsChanged() {}
