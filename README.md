# road_analyzer
Given the center line and a vector of BasicObstacle's creates a matrix representation of the road. The module assumes that the given obstacles are accurate.

## Data Channels
#### Read
- CENTER_LINE(lms::math::polyLine2f)
- NEW_OBSTACLES(bool)
- OBSTACLES(street_environment::BasicObstacleVector)
#### Write
- ROADMATRIX(street_environment::RoadMatrix)

## Config values
- laneWidthMeter(float)
- cellsPerLane(int)
- cellLengthMeter(float)
- maxCellTranslate(int)

The cell width is calculated by dividing the laneWidth by the number of cells per lane. This way there is always an even number of cells on the road.
