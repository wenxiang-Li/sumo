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
/// @file    AdditionalHandler.cpp
/// @author  Jakob Erdmann
/// @date    Feb 2015
///
// The XML-Handler for network loading
/****************************************************************************/
#include <config.h>

#include <string>
#include <utils/xml/SUMOXMLDefinitions.h>
#include <utils/xml/SUMOSAXHandler.h>
#include <utils/xml/XMLSubSys.h>
#include <utils/common/MsgHandler.h>
#include <utils/common/StringUtils.h>
#include <utils/common/StringTokenizer.h>
#include <utils/common/RGBColor.h>
#include <utils/geom/GeomConvHelper.h>
#include <utils/iodevices/OutputDevice.h>
#include <utils/common/UtilExceptions.h>
#include <utils/geom/GeoConvHelper.h>
#include <utils/gui/globjects/GUIGlObjectTypes.h>

#include "AdditionalHandler.h"


// ===========================================================================
// method definitions
// ===========================================================================

AdditionalHandler::AdditionalHandler(const std::string& file) :
    SUMOSAXHandler(file) {
}


AdditionalHandler::~AdditionalHandler() {}


void
AdditionalHandler::myStartElement(int element, const SUMOSAXAttributes& attrs) {
    // obtain tag
    const SumoXMLTag tag = static_cast<SumoXMLTag> (element);
    // check tag
    try {
        switch (tag) {
            case SUMO_TAG_E1DETECTOR:
                parseE1Attributes(attrs);
                break;
            /* case SUMO_TAG_BUSSTOP
               case SUMO_TAG_CHARGINGSTATION
               .....
            */
            case SUMO_TAG_PARAM:
                parseParameters(attrs);
                break;
            default:
                break;
        }
    } catch (InvalidArgument& e) {
        WRITE_ERROR(e.what());
    }
}


void
AdditionalHandler::myEndElement(int /*element*/) {
    // just close node
    myCommonXMLStructure.closeTag();
}


void
AdditionalHandler::parseE1Attributes(const SUMOSAXAttributes& attrs) {
    // declare Ok Flag
    bool parsedOk = true;
    // now obtain attributes
    const std::string id = attrs.get<std::string>(SUMO_ATTR_ID, "", parsedOk, false);
    const std::string laneId = attrs.get<std::string>(SUMO_ATTR_LANE, id.c_str(), parsedOk, false);
    const double position = attrs.get<double>(SUMO_ATTR_POSITION, id.c_str(), parsedOk, false);
    const SUMOTime frequency = attrs.get<SUMOTime>(SUMO_ATTR_FREQUENCY, id.c_str(), parsedOk, false);
    const std::string file = attrs.get<std::string>(SUMO_ATTR_FILE, id.c_str(), parsedOk, false);
    const std::string vehicleTypes = attrs.get<std::string>(SUMO_ATTR_VTYPES, id.c_str(), parsedOk, false);
    const std::string name = attrs.get<std::string>(SUMO_ATTR_NAME, id.c_str(), parsedOk, false);
    const bool friendlyPos = attrs.get<bool>(SUMO_ATTR_FRIENDLY_POS, id.c_str(), parsedOk, false);
    // continue if flag is ok
    if (parsedOk) {
        // first open tag
        myCommonXMLStructure.openTag(SUMO_TAG_E1DETECTOR);
        // add all attributes
        myCommonXMLStructure.addAttribute(SUMO_ATTR_ID, id);
        myCommonXMLStructure.addAttribute(SUMO_ATTR_LANE, laneId);
        myCommonXMLStructure.addAttribute(SUMO_ATTR_POSITION, position);
        myCommonXMLStructure.addAttribute(SUMO_ATTR_FREQUENCY, frequency);
        myCommonXMLStructure.addAttribute(SUMO_ATTR_FILE, file);
        myCommonXMLStructure.addAttribute(SUMO_ATTR_VTYPES, vehicleTypes);
        myCommonXMLStructure.addAttribute(SUMO_ATTR_NAME, name);
        myCommonXMLStructure.addAttribute(SUMO_ATTR_FRIENDLY_POS, friendlyPos);
    }
}


void 
AdditionalHandler::parseParameters(const SUMOSAXAttributes& attrs) {

}

/****************************************************************************/