#include "road_analyzer.h"

bool RoadAnalyzer::initialize() {
    centerLine = readChannel<lms::math::polyLine2f>("CENTER_LINE");
    newObstacles = readChannel<bool>("NEW_OBSTACLES");
    obstacles =
        readChannel<street_environment::BoundingBox2fVector>("OBSTACLES");
    roadMatrix = writeChannel<street_environment::RoadMatrix>("ROADMATRIX");

    impl = std::unique_ptr<RoadAnalyzerImpl>(new RoadAnalyzerImpl);
    return true;
}

bool RoadAnalyzer::deinitialize() { return true; }

bool RoadAnalyzer::cycle() {
    //TODO centerLine nach hinter verlängern
    /*
    lms::math::polyLine2f line;// = *centerLine;

    //TODO Richtungsänderungs zwischen dem 1. und zweiten Segment nutzen und nicht nur nach hinter verlängern
    line.points().push_back((centerLine->points()[0]-centerLine->points()[1]));
    */
    //TODO Trajektorie nach dem Auto
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
