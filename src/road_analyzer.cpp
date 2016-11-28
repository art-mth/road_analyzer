#include "road_analyzer.h"

bool RoadAnalyzer::initialize() {
    centerLine = readChannel<lms::math::polyLine2f>("CENTER_LINE");
    newObstacles = readChannel<bool>("NEW_OBSTACLES");
    obstacles = readChannel<street_environment::BoundingBox2fVector>("OBSTACLES");
    roadMatrix = writeChannel<street_environment::RoadMatrix>("ROADMATRIX");

    impl = std::unique_ptr<RoadAnalyzerImpl>(new RoadAnalyzerImpl);
    return true;
}

bool RoadAnalyzer::deinitialize() { return true; }

bool RoadAnalyzer::cycle() {
    roadMatrix->aroundLine(*centerLine, config().get<float>("laneWidth", 0.4),
                           config().get<int>("cellsPerLane", 4),
                           config().get<float>("cellLength", 0.1));

    if (*newObstacles) {
        impl->markNewObstacles(*obstacles, *roadMatrix);
    } else {
        impl->moveExistingObstacles(*roadMatrix);
    }
    return true;
}
