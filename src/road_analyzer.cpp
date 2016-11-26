#include "road_analyzer.h"

bool RoadAnalyzer::initialize() {
    centerLine = readChannel<lms::math::polyLine2f>("CENTER_LINE");
    newObstacles = readChannel<bool>("NEW_OBSTACLES");
    obstacles = readChannel<street_environment::BoundingBoxVector>("OBSTACLES");
    roadMatrix = writeChannel<street_environment::RoadMatrix>("ROADMATRIX");
    return true;
}

bool RoadAnalyzer::deinitialize() { return true; }

bool RoadAnalyzer::cycle() {
    roadMatrix->aroundLine(*centerLine, config().get<float>("laneWidth", 0.4),
                           config().get<int>("cellsPerLane", 4),
                           config().get<float>("cellLength", 0.1));

    return true;
}
