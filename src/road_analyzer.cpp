#include "road_analyzer.h"

bool RoadAnalyzer::initialize() {
    centerLine = readChannel<lms::math::polyLine2f>("CENTER_LINE");
    obstacles =
        readChannel<street_environment::BoundingBox2fVector>("OBSTACLES");
    poseHistory = readChannel<lms::math::Pose2DHistory>("POSE2D_HISTORY");
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
    lms::math::Pose2D oldPose, deltaPose;
    if (poseHistory->getPose(lastUpdate.toFloat<std::milli, double>(),
                             oldPose)) {
        lms::math::CoordinateSystem2D coord(oldPose);
        deltaPose = coord.transformTo(poseHistory->currentPose());
    } else {
        logger.warn("cycle") << "no valid pose found: "
                             << lastUpdate.toFloat<std::milli, double>();
    }
    lastUpdate = lms::Time::now();

    roadMatrix->aroundLine(*centerLine,
                           lms::math::vertex2f(deltaPose.x, deltaPose.y),
                           deltaPose.phi);

    impl->markObstacles(*obstacles, *roadMatrix);
    return true;
}
