#include "road_analyzer.h"

bool RoadAnalyzer::initialize() {
    poseHistory = readChannel<lms::math::Pose2DHistory>("POSE2D_HISTORY");
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
    lms::math::Pose2D oldPose,deltaPose;
    //get old pose
    if(poseHistory->getPose(lastUpdate.toFloat<std::milli,double>(),oldPose)){
        lms::math::CoordinateSystem2D coord(oldPose);
        //if we found a old pose, we have to transform it
        deltaPose = coord.transformTo(poseHistory->currentPose());
    }else{
        logger.warn("cycle")<<"no valid pose found: "<<lastUpdate.toFloat<std::milli,double>();
    }
    lastUpdate = lms::Time::now();
    roadMatrix->aroundLine(*centerLine, lms::math::vertex2f(deltaPose.x,deltaPose.y),
                           deltaPose.phi);

    impl->markObstacles(*obstacles, *roadMatrix);
    return true;
}
