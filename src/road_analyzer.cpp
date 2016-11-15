#include "road_analyzer.h"

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
                           config().get<int>("cellsPerLane", 8),
                           config().get<float>("cellLength", 0.1));
    roadMatrix->markEnvironmentObjects(obstacles->objects);

    return true;
}
