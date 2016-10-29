#include "road_analyzer.h"

bool RoadAnalyzer::initialize() {
    line = readChannel<lms::math::polyLine2f>("LINE");
    obstacles = readChannel<street_environment::EnvironmentObjects>("OBSTACLES");
    return true;
}

bool RoadAnalyzer::deinitialize() {
    return true;
}

bool RoadAnalyzer::cycle() {
    return true;
}

void RoadAnalyzer::configsChanged(){}
