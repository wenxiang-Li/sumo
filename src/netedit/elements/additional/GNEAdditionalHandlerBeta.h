/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2021 German Aerospace Center (DLR) and others.
// This program and the accompanying materials are made available under the
// terms of the Eclipse Public License 2.0 which is available at
// https://www.eclipse.org/legal/epl-2.0/
// This Source Code may also be made available under the following Secondary
// Licenses when the conditions for such availability set forth in the Eclipse
// Public License 2.0 are satisfied: GNU General Public License, version 2
// or later which is available at
// https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
/****************************************************************************/
/// @file    GNEAdditionalHandlerBeta.h
/// @author  Pablo Alvarez Lopez
/// @date    Nov 2015
///
// Builds additional objects for netedit
/****************************************************************************/
#pragma once
#include <config.h>

#include <utils/common/SUMOVehicleClass.h>
#include <utils/additionals/AdditionalHandler.h>



// ===========================================================================
// class declarations
// ===========================================================================

class GNENet;
class GNEEdge;
class GNELane;
class GNEAdditional;
class GNEShape;
class GNETAZElement;
class GNEDemandElement;

// ===========================================================================
// class definitions
// ===========================================================================

/// @class GNEAdditionalHandlerBeta
/// @brief Builds additional objects for GNENet (busStops, chargingStations, detectors, etc..)
class GNEAdditionalHandlerBeta : public AdditionalHandler {
public:

    /// @brief Constructor
    GNEAdditionalHandlerBeta(const std::string& file, GNENet* net, GNEAdditional* additionalParent = nullptr);

    /// @brief Destructor
    ~GNEAdditionalHandlerBeta();

    /// @name build functions
    /// @{
    /**@brief Builds a bus stop
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The id of the bus stop
     * @param[in] laneID The lane the bus stop is placed on
     * @param[in] startPos Begin position of the bus stop on the lane
     * @param[in] endPos End position of the bus stop on the lane
     * @param[in] name Name of busStop
     * @param[in] lines Names of the bus lines that halt on this bus stop
     * @param[in] friendlyPos enable or disable friendly position
     * @param[in] parameters generic parameters
     */
    void buildBusStop(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const std::string &laneID,
                      const std::string &startPos, const std::string &endPos, const std::string& name, const std::vector<std::string>& lines, 
                      const int personCapacity, const double parkingLength, const bool friendlyPosition, const std::map<std::string, std::string> &parameters);

    /**@brief Builds an Access
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] busStop GNEAdditional of this Access belongs
     * @param[in] laneID The lane the Access is placed on
     * @param[in] pos position of the Access on the lane
     * @param[in[ length length of the Access
     * @param[in] friendlyPos enable or disable friendly position
     * @param[in] parameters generic parameters
     */
    void buildAccess(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string &laneID, const double pos, 
                     const std::string& length, const bool friendlyPos, const std::map<std::string, std::string> &parameters);

    /**@brief Builds a container stop
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The id of the container stop
     * @param[in] laneID The lane the container stop is placed on
     * @param[in] startPos Begin position of the container stop on the lane
     * @param[in] endPos End position of the container stop on the lane
     * @param[in] name Name of container stop
     * @param[in] lines Names of the bus lines that halt on this container stop
     * @param[in] friendlyPos enable or disable friendly position
     * @param[in] parameters generic parameters
     */
    void buildContainerStop(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const std::string &laneID, 
                            const std::string &startPos, const std::string &endPos, const std::string& name, const std::vector<std::string>& lines, 
                            const bool friendlyPosition, const std::map<std::string, std::string> &parameters);

    /**@brief Builds a charging Station
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The id of the charging Station
     * @param[in] laneID The lane the charging Station is placed on
     * @param[in] startPos Begin position of the charging Station on the lane
     * @param[in] endPos End position of the charging Station on the lane
     * @param[in] name Name of charging station
     * @param[in] chargingPower power charged in every timeStep
     * @param[in] efficiency efficiency of the charge
     * @param[in] chargeInTransit enable or disable charge in transit
     * @param[in] chargeDelay delay in the charge
     * @param[in] friendlyPos enable or disable friendly position
     * @param[in] parameters generic parameters
     */
    void buildChargingStation(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const std::string &laneID, 
                              const std::string &startPos, const std::string &endPos, const std::string& name, const double chargingPower, 
                              const double efficiency, const bool chargeInTransit, const SUMOTime chargeDelay, const bool friendlyPosition, 
                              const std::map<std::string, std::string> &parameters);

    /**@brief Builds a Parking Area
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The id of the Parking >Area
     * @param[in] laneID The lane the Parking Area is placed on
     * @param[in] startPos Begin position of the Parking Area on the lane
     * @param[in] endPos End position of the Parking Area on the lane
     * @param[in] name Name of Parking Area
     * @param[in] friendlyPos enable or disable friendly position
     * @param[in] roadSideCapacity road side capacity of ParkingArea
     * @param[in] width ParkingArea's length
     * @param[in] length ParkingArea's length
     * @param[in] angle ParkingArea's angle
     * @param[in] parameters generic parameters
     */
    void buildParkingArea(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const std::string &laneID, 
                          const std::string &startPos, const std::string &endPos, const std::string& name, const bool friendlyPosition, 
                          const int roadSideCapacity, const bool onRoad, const double width, const std::string& length, const double angle, 
                          const std::map<std::string, std::string> &parameters);

    /**@brief Builds a Parking Space
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] pos ParkingSpace's X-Y position
     * @param[in] width ParkingArea's width
     * @param[in] length ParkingArea's length
     * @param[in] angle ParkingArea's angle
     * @param[in] slope ParkingArea's slope (of this space)
     * @param[in] parameters generic parameters
     */
    void buildParkingSpace(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const Position &pos, const double width, const double length, 
                           const double angle, const double slope, const std::map<std::string, std::string> &parameters);

    /**@brief Builds a induction loop detector (E1)
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The id of the detector
     * @param[in] laneID The lane the detector is placed on
     * @param[in] pos position of the detector on the lane
     * @param[in] freq the aggregation period the values the detector collects shall be summed up.
     * @param[in] filename The path to the output file.
     * @param[in] vtypes list of vehicle types to be reported
     * @param[in] name E1 detector name
     * @param[in] friendlyPos enable or disable friendly position
     * @param[in] parameters generic parameters
     */
    void buildE1Detector(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string &id, const std::string &laneId, 
                                 const double position, const SUMOTime frequency, const std::string &file, const std::string &vehicleTypes,
                                 const std::string &name, const bool friendlyPos, const std::map<std::string, std::string> &parameters);

    /**@brief Builds a single-lane Area Detector (E2)
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The id of the detector
     * @param[in] laneID The lane the detector is placed on
     * @param[in] pos position of the detector on the lane
     * @param[in[ length length of the detector
     * @param[in] freq the aggregation period the values the detector collects shall be summed up.
     * @param[in] trafficLight The traffic light that triggers aggregation when switching.
     * @param[in] filename The path to the output file.
     * @param[in] vtypes list of vehicle types to be reported
     * @param[in] name E2 detector name
     * @param[in] timeThreshold The time-based threshold that describes how much time has to pass until a vehicle is recognized as halting
     * @param[in] speedThreshold The speed-based threshold that describes how slow a vehicle has to be to be recognized as halting
     * @param[in] jamThreshold The minimum distance to the next standing vehicle in order to make this vehicle count as a participant to the jam
     * @param[in] friendlyPos enable or disable friendly position
     * @param[in] parameters generic parameters
     */
    void buildSingleLaneDetectorE2(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const std::string &laneID, 
                                   const double pos, const double length, const std::string& freq, const std::string& trafficLight, const std::string& filename, 
                                   const std::string& vehicleTypes, const std::string& name, const SUMOTime timeThreshold, const double speedThreshold,
                                   const double jamThreshold, const bool friendlyPos, const std::map<std::string, std::string> &parameters);

    /**@brief Builds a multi-lane Area Detector (E2)
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The id of the detector
     * @param[in] lanes The lanes the detector is placed on
     * @param[in] pos position of the detector on the first lane
     * @param[in] endPos position of the detector on the last lane
     * @param[in] freq the aggregation period the values the detector collects shall be summed up.
     * @param[in] trafficLight The traffic light that triggers aggregation when switching.
     * @param[in] filename The path to the output file.
     * @param[in] vtypes list of vehicle types to be reported
     * @param[in] name E2 detector name
     * @param[in] timeThreshold The time-based threshold that describes how much time has to pass until a vehicle is recognized as halting
     * @param[in] speedThreshold The speed-based threshold that describes how slow a vehicle has to be to be recognized as halting
     * @param[in] jamThreshold The minimum distance to the next standing vehicle in order to make this vehicle count as a participant to the jam
     * @param[in] friendlyPos enable or disable friendly position
     * @param[in] parameters generic parameters
     */
    void buildMultiLaneDetectorE2(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const std::vector<std::string>& lanes, 
                                  const double pos, const double endPos, const std::string& freq, const std::string& trafficLight, const std::string& filename, 
                                  const std::string& vehicleTypes, const std::string& name, const SUMOTime timeThreshold, const double speedThreshold, const double jamThreshold,
                                  const bool friendlyPos, const std::map<std::string, std::string> &parameters);

    /**@brief Builds a multi entry exit detector (E3)
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The id of the detector
     * @param[in] pos position of the detector in the map
     * @param[in] freq the aggregation period the values the detector collects shall be summed up.
     * @param[in] filename The path to the output file.
     * @param[in] vtypes list of vehicle types to be reported
     * @param[in] name E2 detector name
     * @param[in] timeThreshold The time-based threshold that describes how much time has to pass until a vehicle is recognized as halting
     * @param[in] speedThreshold The speed-based threshold that describes how slow a vehicle has to be to be recognized as halting
     * @param[in] parameters generic parameters
     */
    void buildDetectorE3(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const Position &pos, const SUMOTime freq, 
                         const std::string& filename, const std::string& vehicleTypes, const std::string& name,  SUMOTime timeThreshold, 
                         const double speedThreshold, const std::map<std::string, std::string> &parameters);

    /**@brief Builds a entry detector (E3)
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] laneID The lane in which the entry detector is placed on
     * @param[in] pos position of the entry detector on the lane
     * @param[in] friendlyPos enable or disable friendly position
     */
    void buildDetectorEntry(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string &laneID, const double pos, const bool friendlyPos);

    /**@brief Builds a exit detector (E3)
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] laneID The lane in which the exit detector is placed on
     * @param[in] pos position of the exit detector on the lane
     * @param[in] friendlyPos enable or disable friendly position
     */
    void buildDetectorExit(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string &laneID, const double pos, const bool friendlyPos);

    /**@brief Builds a Instant Induction Loop Detector (E1Instant)
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The id of the detector
     * @param[in] laneID The lane the detector is placed on
     * @param[in] pos position of the detector on the lane
     * @param[in] filename The path to the output file.
     * @param[in] name E2 detector name
     * @param[in] vtypes list of vehicle types to be reported
     * @param[in] friendlyPos enable or disable friendly position
     * @param[in] parameters generic parameters
     */
    void buildDetectorE1Instant(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const std::string &laneID, 
                                double pos, const std::string& filename, const std::string& vehicleTypes, const std::string& name, 
                                const bool friendlyPos, const std::map<std::string, std::string> &parameters);

    /**@brief builds a microscopic calibrator over a lane
     * @param[in] id The id of the calibrator
     * @param[in] laneID The lane the calibrator is placed at
     * @param[in] pos The position on the edge the calibrator lies at
     * @param[in] name Calibrator name
     * @param[in] outfile te file in which write results
     * @param[in] parameters generic parameters
     */
    void buildLaneCalibrator(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const std::string &laneID, 
                             const double pos, const std::string& name, const std::string& outfile, const SUMOTime freq, const std::string& routeprobe, 
                             const std::map<std::string, std::string> &parameters);

    /**@brief builds a microscopic calibrator over an edge
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The id of the calibrator
     * @param[in] edgeID The edge the calibrator is placed at
     * @param[in] pos The position on the edge the calibrator lies at
     * @param[in] name Calibrator name
     * @param[in] outfile te file in which write results
     * @param[in] centerAfterCreation center camera after creation
     * @param[in] routeProbe route probe vinculated with this calibrator
     * @param[in] parameters generic parameters
     */
    void buildEdgeCalibrator(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const std::string &edgeID, 
                             const double pos, const std::string& name, const std::string& outfile, const SUMOTime freq, const std::string& routeprobe,
                             const std::map<std::string, std::string> &parameters);

    /**@brief builds a calibrator flow
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] type The id of the vehicle's flow type to use for this vehicle's flow.
     * @param[in] routeID The id of the route the vehicle's flow shall drive along
     * @param[in] vehsPerHour number of vehicles per hour, equally spaced (not together with period or probability)
     * @param[in] speed The speed with which the vehicles shall enter the network. NOTE: this attribute is exclusive of CalibratorFlows!
     * @param[in] color This vehicle's flow's color
     * @param[in] departLane The lane on which the vehicle's flow shall be inserted {} see #departLane. default: "first"
     * @param[in] departPos The position at which the vehicle's flow shall enter the net {} see #departPos. default: "base"
     * @param[in] departSpeed The speed with which the vehicle's flow shall enter the network {} see #departSpeed. default: 0
     * @param[in] arrivalLane The lane at which the vehicle's flow shall leave the network {} see #arrivalLane. default: "current"
     * @param[in] arrivalPos The position at which the vehicle's flow shall leave the network {} see #arrivalPos. default: "max"
     * @param[in] arrivalSpeed The speed with which the vehicle's flow shall leave the network {} see #arrivalSpeed. default: "current"
     * @param[in] line A string specifying the id of a public transport line which can be used when specifying person rides
     * @param[in] personNumber The number of occupied seats when the vehicle's flow is inserted. default: 0
     * @param[in] containerNumber The number of occupied container places when the vehicle's flow is inserted. default: 0
     * @param[in] reroute List of intermediate edges that shall be passed on rerouting.
     * @param[in] via List of intermediate edges that shall be passed on rerouting.
     * @param[in] departPosLat The lateral position on the departure lane at which the vehicle's flow shall enter the net {} see Simulation/SublaneModel. default: "center"
     * @param[in] arrivalPosLat The lateral position on the arrival lane at which the vehicle's flow shall arrive {} see Simulation/SublaneModel. by default the vehicle's flow does not care about lateral arrival position
     * @param[in] begin first vehicle's flow departure time
     * @param[in] end end of departure interval (if undefined, defaults to 24 hours)
     * @param[in] parameters generic parameters
     */
    void buildCalibratorFlow(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string &vTypeID, const std::string &routeID,
                             const std::string& vehsPerHour, const std::string& speed, const RGBColor& color, const std::string& departLane, const std::string& departPos,
                             const std::string& departSpeed, const std::string& arrivalLane, const std::string& arrivalPos, const std::string& arrivalSpeed,
                             const std::string& line, const int personNumber, const int containerNumber, const bool reroute, const std::string& departPosLat,
                             const std::string& arrivalPosLat, const SUMOTime begin, const SUMOTime end, const std::map<std::string, std::string> &parameters);

    /**@brief builds a rerouter
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The id of the rerouter
     * @param[in] pos position of the rerouter in the map
     * @param[in] edgeIDs The edges the rerouter is placed at
     * @param[in] prob The probability the rerouter reoutes vehicles with
     * @param[in] name Calibrator name
     * @param[in] file The file to read the reroute definitions from
     * @param[in] parameters generic parameters
     */
    void buildRerouter(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const Position &pos, 
                       const std::vector<std::string>& edgeIDs, const double prob, const std::string& name, const std::string& file, 
                       const bool off, const SUMOTime timeThreshold, const std::string& vTypes, const std::map<std::string, std::string> &parameters);

    /**@brief builds a rerouter interval
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] begin begin of interval
     * @param[in] end end of interval
     */
    void buildRerouterInterval(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const SUMOTime begin, const SUMOTime end);

    /**@brief builds a closing lane reroute
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] closedLane closed lane
     * @param[in] permissions vClasses disallowed for the lane
     */
    void buildClosingLaneReroute(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string &closedLane, SVCPermissions permissions);

    /**@brief builds a closing edge reroute
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] closedEdgeID closed edge
     * @param[in] permissions vClasses disallowed for the lane
     */
    void buildClosingReroute(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string &closedEdgeID, SVCPermissions permissions);

    /**@brief builds a dest prob reroute
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] newEdgeDestinationID new edge destination ID
     * @param[in] probability rerouting probability
     */
    void buildDestProbReroute(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string &newEdgeDestinationID, const double probability);

    /**@brief builds a parkng area reroute
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] newParkignAreaID new parkingArea ID
     * @param[in] probability rerouting probability
     */
    void buildParkingAreaReroute(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string &newParkignAreaID, const double probability, const bool visible);

    /**@brief builds a route prob reroute
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] newRouteID new route ID
     * @param[in] probability rerouting probability
     */
    void buildRouteProbReroute(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& newRouteID, const double probability);

    /**@brief builds a Route probe
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The id of the routeprobe
     * @param[in] edgeID The edges the routeprobe is placed at
     * @param[in] freq the aggregation period the values the routeprobe collects shall be summed up.
     * @param[in] name Calibrator name
     * @param[in] file The file to read the routeprobe definitions from
     * @param[in] begin The time at which to start generating output
     * @param[in] parameters generic parameters
     */
    void buildRouteProbe(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const std::string &edgeID, const std::string& freq, 
                         const std::string& name, const std::string& file, const SUMOTime begin, const std::map<std::string, std::string> &parameters);

    /**@brief Builds a VariableSpeedSign (lane speed additional)
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The id of the lane speed additional
     * @param[in] destLanes List of lanes affected by this speed additional
     * @param[in] name Calibrator name
     * @param[in] parameters generic parameters
     */
    void buildVariableSpeedSign(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const Position &pos, const std::vector<std::string>& destLaneIDs, 
                                const std::string& name, const std::map<std::string, std::string> &parameters);

    /**@brief Builds a VariableSpeedSign Step
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] VSSParent Variable Speed Sign parent
     * @param[in] time step's time
     * @param[in] speed step's speed
     */
    void buildVariableSpeedSignStep(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const SUMOTime time, const double speed);

    /**@brief Builds a vaporizer (lane speed additional)
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] edgeID edge in which this vaporizer is placed
     * @param[in] startTime time in which this vaporizer start
     * @param[in] endTime time in which this vaporizer ends
     * @param[in] name Vaporizer name
     * @param[in] parameters generic parameters
     */
    void buildVaporizer(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string &edgeID, const SUMOTime start, 
                        const SUMOTime endTime, const std::string& name, const std::map<std::string, std::string> &parameters);

    /**@brief Builds a TAZ (Traffic Assignment Zone)
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id TAZ ID
     * @param[in] shape TAZ shape
     * @param[in] edgeIDs list of edges (note: This will create GNETAZSourceSinks/Sinks with default values)
     * @param[in] parameters generic parameters
     */
    void buildTAZ(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const PositionVector& shape, const RGBColor& color, 
                 const std::vector<std::string>& edgeIDs, const std::map<std::string, std::string> &parameters);

    /**@brief Builds a TAZSource (Traffic Assignment Zone)
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] TAZ Traffic Assignment Zone in which this TAZSource is palced
     * @param[in] edgeID edge in which TAZSource is placed
     * @param[in] departWeight depart weight of TAZSource
     * @param[in] parameters generic parameters
     */
    void buildTAZSource(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string &edgeID, 
                        const double departWeight, const std::map<std::string, std::string> &parameters);

    /**@brief Builds a TAZSink (Traffic Assignment Zone)
     * @param[in] net net in which element will be inserted
     * @param[in] allowUndoRedo enable or disable remove created additional with ctrl + Z / ctrl + Y
     * @param[in] TAZ Traffic Assignment Zone in which this TAZSink is palced
     * @param[in] edgeID edge in which TAZSink is placed
     * @param[in] arrivalWeight arrival weight of TAZSink
     * @param[in] parameters generic parameters
     */
    void buildTAZSink(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string &edgeID, 
                      const double arrivalWeight, const std::map<std::string, std::string> &parameters);

    /**@brief Builds a polygon using the given values
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The name of the polygon
     * @param[in] type The (abstract) type of the polygon
     * @param[in] color The color of the polygon
     * @param[in] layer The layer of the polygon
     * @param[in] angle The rotation of the polygon
     * @param[in] imgFile The raster image of the polygon
     * @param[in] relativePath set image file as relative path
     * @param[in] shape The shape of the polygon
     * @param[in] geo specify if shape was loaded as GEO coordinate
     * @param[in] fill Whether the polygon shall be filled
     * @param[in] lineWidth Line width when drawing unfilled polygon
     * @param[in] parameters generic parameters
     */
    void buildPolygon(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const std::string& type, 
                      const RGBColor& color, double layer, double angle, const std::string& imgFile, bool relativePath, 
                      const PositionVector& shape, bool geo, bool fill, double lineWidth, const std::map<std::string, std::string> &parameters);

    /**@brief Builds a POI using the given values
     * @param[in] sumoBaseObject sumo base object used for build
     * @param[in] id The name of the POI
     * @param[in] type The (abstract) type of the POI
     * @param[in] color The color of the POI
     * @param[in] pos The position of the POI
     * @param[in[ geo use GEO coordinates (lon/lat)
     * @param[in] lane The Lane in which this POI is placed
     * @param[in] posOverLane The position over Lane
     * @param[in] posLat The position lateral over Lane
     * @param[in] layer The layer of the POI
     * @param[in] angle The rotation of the POI
     * @param[in] imgFile The raster image of the POI
     * @param[in] relativePath set image file as relative path
     * @param[in] width The width of the POI image
     * @param[in] height The height of the POI image
     * @param[in] parameters generic parameters
     */
    void buildPOI(const CommonXMLStructure::SumoBaseObject* sumoBaseObject, const std::string& id, const std::string& type, 
                  const RGBColor& color, const Position& pos, bool geo, const std::string& lane, double posOverLane, double posLat, 
                  double layer, double angle, const std::string& imgFile, bool relativePath, double width, double height,
                  const std::map<std::string, std::string> &parameters);
    /// @}


    /// @brief check if a GNEAccess can be created in a certain Edge
    static bool accessCanBeCreated(GNEAdditional* busStopParent, GNEEdge* edge);

    /// @brief check if an overlapping is produced in rerouter if a interval with certain begin and end is inserted
    static bool checkOverlappingRerouterIntervals(GNEAdditional* rerouter, SUMOTime newBegin, SUMOTime newEnd);

protected:
    

private:
    /// @brief pointer to net
    GNENet* myNet;

    /// @brief invalidate copy constructor
    GNEAdditionalHandlerBeta(const GNEAdditionalHandlerBeta& s) = delete;

    /// @brief invalidate assignment operator
    GNEAdditionalHandlerBeta& operator=(const GNEAdditionalHandlerBeta& s) = delete;
};

