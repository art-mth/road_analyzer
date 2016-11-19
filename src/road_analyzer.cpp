#include "road_analyzer.h"

bool RoadAnalyzer::initialize() {
    centerLine = readChannel<lms::math::polyLine2f>("CENTER_LINE");
    obstacles =
        readChannel<street_environment::EnvironmentObjects>("OBSTACLES");
    roadMatrix = writeChannel<street_environment::RoadMatrix>("ROADMATRIX");
    return true;
}

bool RoadAnalyzer::deinitialize() { return true; }

bool RoadAnalyzer::cycle() {
    roadMatrix->aroundLine(*centerLine, config().get<float>("laneWidth", 0.4),
                           config().get<int>("cellsPerLane", 4),
                           config().get<float>("cellLength", 0.1));
    roadMatrix->markEnvironmentObjects(obstacles->objects);

    return true;
}
