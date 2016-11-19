# road_analyzer
Given the center line and a stream of obstacles creates a matrix representation of the road. The module assumes that the given points are accurate.

## Data Channels
- CENTER_LINE(lms::math::polyLine2f)
- OBSTACLES(street_environment::EnvironmentObjects)
- ROADMATRIX(street_environment::RoadMatrix)

## Config values
- laneWidth: The width of a street lane in meters.
- cellsPerLane: The number of cells that the road matrix should have per lane.
- cellLength: The length of cells in meters.

The cell width is calculated by dividing the laneWidth by the number of cells per lane. This way there is always an even number of cells on the road.
