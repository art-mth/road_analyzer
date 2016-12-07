#include "road_analyzer.h"

bool RoadAnalyzer::initialize() {
    car = readChannel<street_environment::Car>("CAR");
    centerLine = readChannel<lms::math::polyLine2f>("CENTER_LINE");
    obstacles =
        readChannel<street_environment::BoundingBox2fVector>("OBSTACLES");
    roadMatrix = writeChannel<street_environment::RoadMatrix>("ROADMATRIX");

    impl = std::unique_ptr<RoadAnalyzerImpl>(new RoadAnalyzerImpl);
    roadMatrix->initialize(config().get<float>("laneWidth", 0.4),
                          config().get<int>("cellsPerLane", 4),
                          config().get<float>("cellLength", 0.1),
                          config().get<int>("maxCellTranslate", 5));
    return true;
}

bool RoadAnalyzer::deinitialize() { return true; }

bool RoadAnalyzer::cycle() {
    roadMatrix->aroundLine(*centerLine, car->localDeltaPosition(),
                           car->deltaPhi());

    impl->markObstacles(*obstacles, *roadMatrix);
    return true;
}
