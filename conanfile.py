from conans import ConanFile, CMake

class RoadAnalyzerConan(ConanFile):
    name = "road_analyzer"
    version = "0.1"
    requires = "lms/2.0@lms/stable","lms_math/1.0@lms/stable"
    generators = "cmake"
