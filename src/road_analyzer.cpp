#include "road_analyzer.h"

bool RoadAnalyzer::initialize() {
    line = readChannel<lms::math::polyLine2f>("LINE");
    obstacles = readChannel<street_environment::EnvironmentObjects>("OBSTACLES");
    roadMatrix = writeChannel<street_environment::RoadMatrix>("ROADMATRIX");
    return true;
}

bool RoadAnalyzer::deinitialize() {
    return true;
}

bool RoadAnalyzer::cycle() {
    roadMatrix->aroundRoad(*line,config().get<int>("widthSteps",2),config().get<float>("stepWidth",0.2),config().get<float>("stepLength",0.4));
    float deltaBadness =config().get<float>("deltaBadness",1);
    for(street_environment::EnvironmentObjectPtr ptr:obstacles->objects){
        if(ptr->getType() == street_environment::Obstacle::TYPE){
            std::shared_ptr<street_environment::Obstacle> obst = std::dynamic_pointer_cast<street_environment::Obstacle>(ptr);
            for(const lms::math::vertex2f &v: obst->points()){
                int x,y;
                if(roadMatrix->checkBadPosition(v,x,y,deltaBadness)){
                    /*
                    logger.error("Inside: ")<<v.x<<" "<<v.y;
                    logger.error("box:")<<roadMatrix->cell(x,y).points[0].x<<" "<<roadMatrix->cell(x,y).points[0].y;
                    logger.error("box:")<<roadMatrix->cell(x,y).points[1].x<<" "<<roadMatrix->cell(x,y).points[1].y;
                    logger.error("box:")<<roadMatrix->cell(x,y).points[2].x<<" "<<roadMatrix->cell(x,y).points[2].y;
                    logger.error("box:")<<roadMatrix->cell(x,y).points[3].x<<" "<<roadMatrix->cell(x,y).points[3].y;
                    */
                }

            }
        }
    }
    return true;
}

void RoadAnalyzer::configsChanged(){}
