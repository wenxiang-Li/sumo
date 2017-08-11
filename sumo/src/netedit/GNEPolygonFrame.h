/****************************************************************************/
/// @file    GNEPolygonFrame.h
/// @author  Pablo Alvarez Lopez
/// @date    Aug 2017
/// @version $Id: GNEPolygonFrame.h 25295 2017-07-22 17:55:46Z behrisch $
///
// The Widget for add polygons
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright (C) 2001-2017 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This file is part of SUMO.
//   SUMO is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef GNEPolygonFrame_h
#define GNEPolygonFrame_h


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include "GNEFrame.h"

// ===========================================================================
// class declarations
// ===========================================================================
class GNEAttributeCarrier;
class GNENetElement;
class GNEShape;

// ===========================================================================
// class definitions
// ===========================================================================
/**
* @class GNEPolygonFrame
* The Widget for setting internal attributes of additional elements
*/
class GNEPolygonFrame : public GNEFrame {
    /// @brief FOX-declaration
    FXDECLARE(GNEPolygonFrame)

public:

    /// @brief enum with all possible values after try to create an additional using frame
    enum AddShapeResult {
        ADDADDITIONAL_INVALID_ARGUMENTS,    // Parameters of additionals are invalid
        ADDADDITIONAL_INVALID_PARENT,       // NetElement parent is invalid
        ADDADDITIONAL_SUCCESS               // additional was successfully created
    };

    // ===========================================================================
    // class ShapeAttributeSingle
    // ===========================================================================

    class ShapeAttributeSingle : public FXHorizontalFrame {
        /// @brief FOX-declaration
        FXDECLARE(GNEPolygonFrame::ShapeAttributeSingle)

    public:
        /// @brief constructor
        ShapeAttributeSingle(FXComposite* parent);

        /// @brief destructor
        ~ShapeAttributeSingle();

        /// @brief show name and value of attribute of type string
        void showParameter(SumoXMLTag additionalTag, SumoXMLAttr additionalAttr, std::string value);

        /// @brief show name and value of parameters of type int
        void showParameter(SumoXMLTag additionalTag, SumoXMLAttr additionalAttr, int value);

        /// @brief show name and value of parameters of type float/real/time
        void showParameter(SumoXMLTag additionalTag, SumoXMLAttr additionalAttr, double value);

        /// @brief show name and value of parameters of type bool
        void showParameter(SumoXMLTag additionalTag, SumoXMLAttr additionalAttr, bool value);

        /// @brief hide all parameters
        void hideParameter();

        /// @brief return tag
        SumoXMLTag getTag() const;

        /// @brief return Attr
        SumoXMLAttr getAttr() const;

        /// @brief return value
        std::string getValue() const;

        /// @brief returns a empty string if current value is valid, a string with information about invalid value in other case
        const std::string& isAttributeValid() const;

        /// @name FOX-callbacks
        /// @{
        /// @brief called when user set the value of an attribute of type int/float/string
        long onCmdSetAttribute(FXObject*, FXSelector, void*);

        /// @brief called when user change the value of myBoolCheckButton
        long onCmdSetBooleanAttribute(FXObject*, FXSelector, void*);
        /// @}

    protected:
        /// @brief FOX needs this
        ShapeAttributeSingle() {}

    private:
        /// @brief current XML attribute
        SumoXMLTag myShapeTag;

        /// @brief current XML attribute
        SumoXMLAttr myShapeAttr;

        /// @brief lael with the name of the parameter
        FXLabel* myLabel;

        /// @brief textField to modify the default value of int/float/string parameters
        FXTextField* myTextFieldInt;

        /// @brief textField to modify the default value of real/times parameters
        FXTextField* myTextFieldReal;

        /// @brief textField to modify the default value of string parameters
        FXTextField* myTextFieldStrings;

        /// @brief check button to enable/disable the value of boolean parameters
        FXCheckButton* myBoolCheckButton;

        /// @brief string which indicates the reason due current value is invalid
        std::string myInvalidValue;
    };


    // ===========================================================================
    // class ShapeAttributes
    // ===========================================================================

    class ShapeAttributes : public FXGroupBox {
        /// @brief FOX-declaration
        FXDECLARE(GNEPolygonFrame::ShapeAttributes)

    public:
        /// @brief constructor
        ShapeAttributes(GNEViewNet* viewNet, FXComposite* parent);

        /// @brief destructor
        ~ShapeAttributes();

        /// @brief clear attributes
        void clearAttributes();

        /// @brief add attribute
        void addAttribute(SumoXMLTag additionalTag, SumoXMLAttr ShapeAttributeSingle);

        /// @brief show group box
        void showShapeParameters();

        /// @brief hide group box
        void hideShapeParameters();

        /// @brief get attributes and their values
        std::map<SumoXMLAttr, std::string> getAttributesAndValues() const;

        /// @brief check if parameters of attributes are valid
        bool areValuesValid() const;

        /// @brief show warning message with information about non-valid attributes
        void showWarningMessage(std::string extra = "") const;

        /// @brief get number of added attributes
        int getNumberOfAddedAttributes() const;

        /// @name FOX-callbacks
        /// @{
        /// @brief Called when help button is pressed
        long onCmdHelp(FXObject*, FXSelector, void*);
        /// @}

    protected:
        /// @brief FOX needs this
        ShapeAttributes() {}

    private:
        /// @brief pointer to viewNet
        GNEViewNet* myViewNet;

        /// @brief current additional tag
        SumoXMLTag myShapeTag;

        /// @brief vector with the additional parameters
        std::vector<ShapeAttributeSingle*> myVectorOfsingleShapeParameter;

        /// @brief Index for myVectorOfsingleShapeParameter
        int myIndexParameter;

        /// @brief index for myIndexParameterList
        int myIndexParameterList;

        /// @brief max number of parameters (Defined in constructor)
        int maxNumberOfParameters;

        /// @brief max number of parameters (Defined in constructor)
        int maxNumberOfListParameters;

        /// @brief button for help
        FXButton* helpShape;
    };

    // ===========================================================================
    // class NeteditAttributes
    // ===========================================================================

    class NeteditAttributes : public FXGroupBox {
        /// @brief FOX-declaration
        FXDECLARE(GNEPolygonFrame::NeteditAttributes)

    public:
        /// @brief list of the reference points
        enum additionalReferencePoint {
            GNE_ADDITIONALREFERENCEPOINT_LEFT,
            GNE_ADDITIONALREFERENCEPOINT_RIGHT,
            GNE_ADDITIONALREFERENCEPOINT_CENTER,
            GNE_ADDITIONALREFERENCEPOINT_INVALID
        };

        /// @brief constructor
        NeteditAttributes(FXComposite* parent);

        /// @brief destructor
        ~NeteditAttributes();

        /// @brief show length field and reference point
        void showLengthFieldAndReferecePoint();

        /// @brief hide length field
        void hideLengthFieldAndReferecePoint();

        /// @brief get actual reference point
        additionalReferencePoint getActualReferencePoint() const;

        /// @brief get value of length
        double getLength() const;

        /// @brief check if block is enabled
        bool isBlockEnabled() const;

        /// @brief check if current length is valid
        bool isCurrentLengthValid() const;

        /// @name FOX-callbacks
        /// @{
        /// @brief Called when user enters a new length
        long onCmdSetLength(FXObject*, FXSelector, void*);

        /// @brief Called when user enters another reference point
        long onCmdSelectReferencePoint(FXObject*, FXSelector, void*);

        /// @brief Called when user changes the checkbox "set blocking"
        long onCmdSetBlocking(FXObject*, FXSelector, void*);

        /// @brief Called when user press the help button
        long onCmdHelp(FXObject*, FXSelector, void*);
        /// @}

    protected:
        /// @brief FOX needs this
        NeteditAttributes() {}

    private:
        /// @brief match box with the list of reference points
        FXComboBox* myReferencePointMatchBox;

        /// @brief Button for help about the reference point
        FXButton* helpReferencePoint;

        /// @brief actual additional reference point selected in the match Box
        additionalReferencePoint myActualShapeReferencePoint;

        /// @brief Label for length
        FXLabel* myLengthLabel;

        /// @brief textField for length
        FXTextField* myLengthTextField;

        /// @brief Label for block movement
        FXLabel* myBlockLabel;

        /// @brief checkBox for block movement
        FXCheckButton* myBlockMovementCheckButton;

        /// @brief Flag to check if current length is valid
        bool myCurrentLengthValid;
    };


    /**@brief Constructor
    * @brief parent FXHorizontalFrame in which this GNEFrame is placed
    * @brief viewNet viewNet that uses this GNEFrame
    */
    GNEPolygonFrame(FXHorizontalFrame* horizontalFrameParent, GNEViewNet* viewNet);

    /// @brief Destructor
    ~GNEPolygonFrame();

    /**@brief add additional element
    * @param[in] netElement clicked netElement. if user dind't clicked over a GNENetElement in view, netElement will be NULL
    * @param[in] parent AbstractView to obtain the position of the mouse over the lane.
    * @return AddShapeStatus with the result of operation
    */
    AddShapeResult addShape(GNENetElement* netElement, GUISUMOAbstractView* parent);

    /**@brief remove an additional element previously added
    * @param[in] additional element to erase
    */
    void removeShape(GNEShape* additional);

    /// @name FOX-callbacks
    /// @{
    /// @brief Called when the user select another additional Type
    long onCmdSelectShape(FXObject*, FXSelector, void*);
    /// @}

    /// @brief show additional frame and update use selected edges/lanes
    void show();

    /// @brief get list of selecte id's in string format
    static std::string getIdsSelected(const FXList* list);

protected:
    /// @brief FOX needs this
    GNEPolygonFrame() {}

private:
    /// @brief set parameters depending of the new additionalType
    void setParametersOfShape(SumoXMLTag actualShapeType);

    /// @brief generate a ID for an additiona element
    std::string generateID(GNENetElement* netElement) const;

    /// @brief obtain the Start position values of StoppingPlaces and E2 detector over the lane
    double setStartPosition(double positionOfTheMouseOverLane, double lengthOfShape);

    /// @brief obtain the End position values of StoppingPlaces and E2 detector over the lane
    double setEndPosition(double laneLength, double positionOfTheMouseOverLane, double lengthOfShape);

    /// @brief groupBox for Match Box of additionals
    FXGroupBox* myGroupBoxForMyShapeMatchBox;

    /// @brief combo box with the list of additional elements
    FXComboBox* myShapeMatchBox;

    /// @brief additional internal attributes
    GNEPolygonFrame::ShapeAttributes* myadditionalParameters;

    /// @brief Netedit parameter
    GNEPolygonFrame::NeteditAttributes* myEditorParameters;

    /// @brief actual additional type selected in the match Box
    SumoXMLTag myActualShapeType;
};


#endif

/****************************************************************************/
