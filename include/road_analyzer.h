#ifndef ROAD_ANALYZER_H
#define ROAD_ANALYZER_H

#include <lms/module.h>

/**
 * @brief LMS module road_analyzer
 **/
class RoadAnalyzer : public lms::Module {
public:
    bool initialize() override;
    bool deinitialize() override;
    bool cycle() override;
    void configsChanged() override;

};

#endif // ROAD_ANALYZER_H
