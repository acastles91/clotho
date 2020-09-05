#include "ofApp.h"

void ofApp::setupGui(Canvas &canvasArg){


    ofSetFrameRate(120);
    ofBackground(235, 235, 235);
    margin = 50;



////    //ofxGuiExtended
////    //--------------------------------------------------------------


////    //Project panel
////    //--------------------------------------------------------------

    projectPanel = gui2.addPanel();
    projectPanel->setShowHeader(false);
    projectPanel->setBackgroundColor(ofColor::darkGray);
    projectPanel->setWidth(ofGetWidth() / 7);
    projectPanel->setHeight(ofGetHeight() - 2 * margin);
    projectPanel->setPosition(ofGetWidth() - margin - projectPanel->getWidth() , margin);

    projectGroup = projectPanel->addGroup(projectParameters);
    projectGroup->setShowHeader(0);
    projectGroup->setConfig(ofJson({{"type", "fullsize"}, {"direction", "vertical"}}));

    layerContainer = projectGroup->addContainer();
    layerContainer->setBackgroundColor(ofColor::pink);
    layerContainer->setWidth(100.0f);
    layerContainer->setPosition(0,0);

    loadLayerButton = layerContainer->add<ofxGuiButton>("Load layer", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    //loadLayerButton->addListener(this, &ofApp::loadLayer(canvasArg.xCanvas, canvasArg.yCanvas));
    loadLayerButton->addListener(this, &ofApp::loadLayer);

    layerString.set("File location", filePath);
    projectGroup->add(layerString);

    backgroundContainer = projectGroup->addContainer();
    backgroundContainer->setBackgroundColor(ofColor::blue);
    backgroundContainer->setWidth(layerContainer->getWidth());
    backgroundContainer->setPosition(0,layerContainer->getHeight());

    loadBackgroundButton = backgroundContainer->add<ofxGuiButton>("Load Background", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));

    loadBackgroundButton->setEnabled(otherParameter);
    backgroundParameters.add(whiteParameter.set("White background", true));
    backgroundParameters.add(blackParameter.set("Black background", false));
    //backgroundParameters.add(otherParameter.set("Other background", false));
    loadBackgroundButton->addListener(this, &ofApp::loadBackground);

    backgroundIsLoaded = true;
    backgroundFilePath = "data/background.png";

    //backgroundString.set("Background location", backgroundFilePath);
    projectGroup->add(backgroundString);

    backgroundGroup = projectGroup->addGroup();
    backgroundSubContainer = backgroundGroup->addContainer();
    backgroundGroup->setShowHeader(0);
    backgroundGroup->setShowName(0);

    //
//    //markersSubContainer->setWidth(containerLeft->getWidth());
//    //markersContainer = markersGroup->addContainer();
//    drawMarkersParameter.set("Draw Markers", false);
//    markersBool = false;
//    //markersContainer->setWidth(markers);
//    //drawMarkersParameter.addListener(this, &ofApp::markersCall);

//    markersParameters.add(parameter720p.set("720p", false));
//    markersParameters.add(parameterCenter.set("Center", false));
    backgroundSubGroup = backgroundGroup->addGroup(backgroundParameters);
//    //markersSubGroup->setWidth(speedControlGroup->getWidth());
//    //markersSubGroup->setWidth(markersGroup->getWidth());
    backgroundSubGroup->setBackgroundColor(ofColor::lightGray);
    backgroundSubGroup->setShowHeader(0);
    backgroundSubGroup->setShowName(0);
    backgroundSubGroup->setConfig(ofJson({{"type", "fullsize"}, {"direction", "vertical"}}));
    backgroundSubGroup->setExclusiveToggles(1);

    projectGroup->add<ofxGuiTextField>(textfieldVal.set("Project Name", "Enter project name"));

    saveContainer = projectGroup->addContainer();
    saveContainer->setBackgroundColor(ofColor::salmon);
    saveContainer->setWidth(layerContainer->getWidth());
    saveContainer->setPosition(0,layerContainer->getHeight());

    saveButton = saveContainer->add<ofxGuiButton>("Save", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    saveButton->addListener(this, &ofApp::loadBackground);
//    projectGroup->add(homingStatus);

    drawContainer = projectGroup->addContainer();
    drawContainer->setBackgroundColor(ofColor::salmon);
    drawContainer->setWidth(layerContainer->getWidth());
    drawContainer->setPosition(0,backgroundContainer->getHeight());
    drawParameters.add(drawContourParameter.set("Draw Contour", true));
    drawParameters.add(drawHatchParameter.set("Draw Hatch Fill", true));
    drawParameters.add(drawLayerParameter.set("Draw Layer", true));
    drawParameters.add(drawTravelParameter.set("Draw Travel", true));
    drawParameters.add(drawInfoParameter.set("Draw Info", true));
    drawParameters.add(drawGcodeParameter.set("Draw G-Code", false));


    drawSubGroup = drawContainer->addGroup(drawParameters);
    //drawSubGroup->addGroup(drawParameters);
    drawSubGroup->setBackgroundColor(ofColor::lightGray);
    drawSubGroup->setWidth(drawContainer->getWidth());
    drawSubGroup->setShowHeader(0);
    drawSubGroup->setShowName(0);
    drawSubGroup->setConfig(ofJson({{"type", "checkbox"}, {"direction", "vertical"}}));
    drawSubGroup->setExclusiveToggles(0);

    slidersContainer = projectGroup->addContainer("horizontal sliders", ofJson({{"direction", "horizontal"}}));
    slidersContainer->setBackgroundColor(ofColor::khaki);
    slidersContainer->setPosition(0, drawContainer->getHeight());
    slidersContainer->add(radius.set("Radius", 25, 50, 1), ofJson({{"width", 120}, {"height", 50}}));
    //radiusListener = radius.newListener([&](float&){return this->updateLayer();});
    //radiusListener = radius.addListener(this, &ofApp::updateLayer);
    //radius.addListener(this, &ofApp::updateLayer);
    slidersContainer->add(threshold.set("Threshold", 254, 254, 1), ofJson({{"width", 120}, {"height", 50}}));
    //thresholdListener = threshold.addListener(this, &ofApp::updateLayer);
    slidersContainer->add(opacity.set("Opacity", 0, 100, 1), ofJson({{"width", 120}, {"height", 50}}));
    slidersContainer->add(feedrate.set("Feedrate", 0, 11000, 1), ofJson({{"width", 120}, {"height", 50}}));
    slidersContainer->add(contourNumber.set("Max number blobs", 1000, 10000, 1), ofJson({{"width", 120}, {"height", 50}}));
    //feedrate.addListener(this, &ofApp::updateLayer);

    gCodeIndividualLabel = "Mambrú se fue a la guerra";
    gCodeTotalLabel = "Qué dolor qué dolor qué pena";
    gCodePanel = projectGroup->addPanel();
    gCodePanel->setShowName(1);
    gCodePanel->setShowHeader(1);
    gCodeGroup = gCodePanel->addGroup("G-Code");
    gCodeGroup->add<ofxGuiLabel>(gCodeIndividualLabel);
    gCodeGroup->add<ofxGuiLabel>(gCodeTotalLabel);

    notificationLabel = "Notification Label";
    notificationPanel = projectGroup->addPanel();
    notificationPanel->setShowName(1);
    notificationPanel->setShowHeader(1);
    notificationGroup = notificationPanel->addGroup("Notification");
    notificationGroup->add<ofxGuiLabel>(notificationLabel);

    buttonsContainer = projectPanel->addContainer();
    //detectContourSetupButton = buttonsContainer->add<ofxGuiButton>("Detect contour setup", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    //detectContourSetupButton->addListener(&layerTest, &Layer::detectContourSetup());
    updateLayerButton = buttonsContainer->add<ofxGuiButton>("Update Layer", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    updateLayerButton->addListener(this, &ofApp::updateLayer);
    //buildContourButton = buttonsContainer->add<ofxGuiButton>("Build contour", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    //drawInfoButton = buttonsContainer->add<ofxGuiButton>("Draw info", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    //drawInfoButton->addListener(this, &ofApp::infoCaller);
    generateGcodeButton = buttonsContainer->add<ofxGuiButton>("Generate G-Code", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    //buildHatchButton = buttonsContainer->add<ofxGuiButton>("Build Hatch Fill", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));



////    //speed Control Panel
////    //--------------------------------------------------------------

////    speedControlPanel = gui2.addPanel();
////    speedControlPanel->setShowHeader(false);
////    speedControlPanel->setBackgroundColor(ofColor::darkGray);


////    speedControlGroup = speedControlPanel->addGroup(speedControlParameters);
////    speedControlGroup->setShowHeader(0);
////    speedControlGroup->setConfig(ofJson({{"type", "fullsize"}, {"direction", "vertical"}}));

////    speedControlContainer = speedControlGroup->addContainer();
////    speedControlContainer->setBackgroundColor(ofColor::lightGray);

//    //speedControlPanel = gui2.addPanel();
//    //speedControlPanel->setShowHeader(false);
//    //speedControlPanel->setBackgroundColor(ofColor::darkGray);


//    speedControlGroup = projectPanel->addGroup(speedControlParameters);
//    speedControlGroup->setShowHeader(0);
//    speedControlGroup->setConfig(ofJson({{"type", "fullsize"}, {"direction", "vertical"}}));

//    speedControlContainer = speedControlGroup->addContainer();
//    speedControlContainer->setBackgroundColor(ofColor::lightGray);
//    //speedControlContainer->add(speedProjector.set("Speed", 1, 1, 4), ofJson({{"precision", 1}}));
//    //speedControlContainer->add<ofxGuiButton>("Change Speed", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));


//    //speedControlContainer->add(speed2.set("Speed 2", 0.5, 0.1, 1), ofJson({{"precision", 1}}));


////    //markers group
////    //--------------------------------------------------------------

////    markersGroup = speedControlPanel->addGroup();
//
//    //markersGroup->setWidth(speedControlGroup->getWidth());

////Notifications
////--------------------------------------------------------------


////    notificationsGroup = speedControlPanel->addGroup("Notifications");
//    notificationsGroup = projectPanel->addGroup("Notifications");
//    //notificationsGroup->isChild(projectPanel);
//    notificationsGroup->setShowHeader(0);
//    projectorNotificationsContainer = notificationsGroup->addContainer();
//    projectorNotificationsContainer->add(projectorNotificationString);
//    captureNotificationsContainer = notificationsGroup->addContainer();
//    captureNotificationsContainer->add(captureNotificationsString);
////    //Stabilization paneln
////    //--------------------------------------------------------------

//    //    stabPanel = gui2.addPanel();
//    //    stabPanel->setShowHeader(false);
//    //    stabPanel->setBackgroundColor(ofColor::darkGray);
//    //    stabPanel->setPosition(projectPanel->getX(), speedControlPanel->getHeight() + 50);


//    //    stabGroup = stabPanel->addGroup(stabParameters);
//    //    stabGroup->setShowHeader(0);
//    //    stabGroup->setConfig(ofJson({{"type", "fullsize"}, {"direction", "vertical"}}));

//    //    stabContainer = stabGroup->addContainer();
//    //    stabContainer->setBackgroundColor(ofColor::lightGray);
//    //    stabContainer->add(stabMin.set("Min", 30.0, 0.0, 300.0), ofJson({{"precision", 1}}));
//    //    stabContainer->add(stabMax.set("Max", 300.0, 0.0, 600.0), ofJson({{"precision", 1}}));
//    //    stabContainer->add(stabThreshold.set("Threshold", 100.0, 0.0, 200.0), ofJson({{"precision", 1}}));
//    //    stabContainer->add(stabHole.set("Hole", false));

//    //Size and layout
//    //--------------------------------------------------------------



//    projectGroup->setWidth(projectPanel->getWidth());
//    notificationsGroup->setWidth(projectGroup->getWidth());
//    markersGroup->setWidth(projectGroup->getWidth());
//    speedControlGroup->setWidth(projectGroup->getWidth());
//    //speedControlPanel->setPosition(projectGroup->getX() + margin, projectGroup->getHeight() + margin + 50);
//    //speedControlPanel->setWidth(projectPanel->getWidth());
//    notificationsGroup->setHeight(projectPanel->getHeight() - notificationsGroup->getY());


////    //Speed selector
////    //--------------------------------------------------------------

//    speedParameters.add(speedParameter1.set("Mode 1", mode));
//    speedParameters.add(speedParameter2.set("Mode 2", !mode));

//    speedPanel = gui2.addPanel();
//    speedPanel->setShowHeader(false);
//    speedPanel->setBackgroundColor(ofColor::darkGray);
//    speedGroup = speedPanel ->addGroup(speedParameters);


//    speedGroup->setShowHeader(0);
//    speedGroup->setExclusiveToggles(true);
//    speedGroup->setConfig(ofJson({{"type", "radio"}, {"direction", "horizontal"}}));

//    //speedGroup->getActiveToggleIndex().addListener(this, &ofApp::setMode);
//    speedGroup->setActiveToggle(0);
////    //Projector control
////    //--------------------------------------------------------------

//    controlPanel = gui2.addPanel();
//    controlPanel->setShowHeader(false);
//    controlPanel->setBackgroundColor(ofColor::darkGray);
//    controlGroup = controlPanel->addGroup(controlParameters);
//    controlGroup->setShowHeader(0);
//    controlGroup->setConfig(ofJson({{"direction", "horizontal"}}));

//    startStopP = controlGroup->addPanel();
//    startStopP->setBackgroundColor(ofColor::lightGray);
//    startStopP->setShowHeader(false);
//    startStopP->setWidth(80.0f);
//    startStopParameter.set("Start", false);
//    startStopP->add(startStopParameter, ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
//    startStopP->setPosition(projectPanel->getX(), projectPanel->getHeight() + 100);
//    //startStopParameter.addListener(this, &ofApp::startStop);

//    directionP = controlGroup->addPanel();
//    directionP->setBackgroundColor(ofColor::lightGray);
//    directionP->setShowHeader(false);
//    directionP->setWidth(80.0f);
//    directionParameter.set("Forward", true);
//    directionP->add(directionParameter, ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
//    directionP->setPosition(startStopP->getX() + startStopP->getWidth(), startStopP->getY());
//    //directionParameter.addListener(this, &ofApp::directionSwitch);

//    homingP = controlGroup->addPanel();
//    homingP->setBackgroundColor(ofColor::lightGray);
//    homingP->setShowHeader(false);
//    homingP->setWidth(80.0f);
//    homingParameter.set("Homing", true);
//    homingP->add(homingParameter, ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
//    homingP->setPosition(directionP->getX() + directionP->getWidth(), directionP->getY());
//    //homingParameter.addListener(this, &ofApp::homingToggle);


//    captureP = controlGroup->addPanel();
//    captureP->setBackgroundColor(ofColor::orange);
//    captureP->setShowHeader(false);
//    captureP->setWidth(80.0f);
//    captureParameter.set("Capture", false);
//    captureP->add(captureParameter, ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
//    captureP->setPosition(homingP->getX() + homingP->getWidth(), homingP->getY());
//    //captureParameter.addListener(this, &ofApp::capture);

//    changeSpeedP = controlGroup->addPanel();
//    changeSpeedP->setBackgroundColor(ofColor::lightGray);
//    changeSpeedP->setShowHeader(false);
//    changeSpeedP->setWidth(80.0f);
//    changeSpeedParameter.set("Change Speed", true);
//    changeSpeedP->add(changeSpeedParameter, ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
//    changeSpeedP->setPosition(captureP->getX() + captureP->getWidth(), captureP->getY());
//    //changeSpeedParameter.addListener(this, &ofApp::setSpeed);


//    changeSpeedSliderP = controlGroup->addPanel();
//    changeSpeedSliderP->setBackgroundColor(ofColor::lightGray);
//    changeSpeedSliderP->setShowHeader(false);
//    changeSpeedSliderP->setWidth(160.0f);
//    changeSpeedSliderP->add(speed1.set("Speed", 4, 1, 4), ofJson({{"precision", 1}}));
//    changeSpeedP->setPosition(changeSpeedP->getX() + changeSpeedP->getWidth(), changeSpeedP->getY());




////    //Size and layout
////    //--------------------------------------------------------------

////    controlPanel->setPosition(ofGetWidth()/2 - controlPanel->getWidth() / 2, ofGetHeight() - 200);
////    speedPanel->setPosition(ofGetWidth()/2 - speedPanel->getWidth() / 2, controlPanel->getY() - 50);


//    camX = ofGetWidth() - 1280 - projectPanel->getX();
//    camY = projectPanel->getY();

//    //controlPanel->setPosition( camX + cam.getWidth() / 2 - (controlPanel->getWidth() / 2) + (1280 / 2), ofGetHeight() - 200);
//    //speedPanel->setPosition( camX + cam.getWidth() / 2 - (speedPanel->getWidth() / 2) + (1280 / 2), controlPanel->getY() - 50);



}
