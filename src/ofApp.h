#pragma once

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf

#include "layer.h"
#include "ofMain.h"
#include "canvas.h"
#include "ofxGuiExtended.h"
#include "mode.h"


class ofApp : public ofBaseApp{

	public:

        Layer layerTest;
        Canvas canvasTest;
        ofFbo   fbo;

        bool contourDraw;
        bool pointsDraw;
        bool infoDraw;
        bool travelDraw;
        bool hatchDraw;
        bool buildHatch;
        bool buildContour;
        int layerHeight;

        vector<Layer*> layers;
        std::string filePath;
        std::string backgroundFilePath;
        ofFile  file;
        ofFbo buffer;
        ofImage image;
        ofImage background;
        ofBuffer buff;
        bool isLoaded;
        bool backgroundIsLoaded;
        bool setupDone;

        ofFileDialogResult  saveFilePath;


        //GUI

        ofxGuiPanel          *projectPanel,
                             *gCodePanel,
                             *notificationPanel,
                             *panel2,
                             *controlPanel,
                             *speedPanel,
                             *speedControlPanel,
                             //*stabPanel;
                             *startStopP,
                             *directionP,
                             *homingP,
                             *captureP,
                             *changeSpeedP,
                             *changeSpeedSliderP;

        ofxGuiContainer      *layerContainer,
                             *backgroundContainer,
                             *saveContainer,
                             *drawContainer,
                             *buttonsContainer,
                             *slidersContainer,
                             *markersContainer,
                             *backgroundSubContainer,
                             *shutter,
                             *projectorNotificationsContainer,
                             *captureNotificationsContainer;   //check
                          //   *stabContainer;

         ofxGuiGroup        *controlGroup,
                            *speedGroup,
                            *projectGroup,
                            *drawSubGroup,
                            *backgroundGroup,
                            *backgroundSubGroup,
                            *gCodeGroup,
                            *notificationGroup,
                            *filmToggles,
                            *modeToggles;

         std::string        gCodeIndividualLabel,
                            gCodeTotalLabel,
                            notificationLabel;

         ofParameter<string>    intentemos;

         std::stringstream       gCodeExport;

         ofParameter <float> slider1Val, slider2Val, slider3Val, slider4Val;
         ofParameter <float> circularSliderVal;

         ofParameterGroup    controlParameters,
                             speedParameters,
                             projectParameters,
                             drawParameters,
                             backgroundParameters,
                             colorParameters,
                             modeParameters;
                        //     stabParameters;

         ofxGui              gui2, gui3;     //check if gui3 is redundant

         ofxGuiButton        *loadLayerButton,
                             *loadBackgroundButton,
                             *saveButton,
                             *detectContourSetupButton,
                             *updateLayerButton,
                             *buildContourButton,
                             *drawInfoButton,
                             *generateGcodeButton,
                             *generateGcodePointsButton,
                             *generateGcodeLinesButton,
                             *drawGcodePointsButton,
                             *buildHatchButton;  //check drawMarkersB


         ofxGuiToggle           *backwardB,     //check
                                *captureB;//check


         ofParameter<string>    homingStatus,
                                layerString,
                                backgroundString,
                                textfieldVal, //check
                                projectorNotificationString,
                                captureNotificationsString;


         ofParameter<bool>       drawContourParameter,
                                 drawHatchParameter,
                                 drawGcodeParameter,
                                 drawTravelParameter,
                                 drawInfoParameter,
                                 drawLayerParameter,
                                 drawBlurParameter,
                                 drawBufferParameter,
                                 drawGcodePointsParameter,
                                 mode1Parameter,
                                 mode2Parameter,
                                 mode3Parameter,
                                 startStopToggle,   //check
                                 captureParameter,
                                 speedParameter1,
                                 speedParameter2,
                                 whiteParameter,
                                 blackParameter,
                                 otherParameter,
                                 parameter720p,
                                 parameterCenter,
                                 drawMarkersParameter,
                                 changeSpeedParameter,
    //    //check all these
    //    //_______________________________________________

                                 color0,
                                 color1,
                                 color2,
                                 color3,
                                 negative2,
                                 stabilizer2,
                                 dustRemoval2,
                                 mFullscreen2,
                                 loadBool2,
                                 captureBool2,
                                 recording2,
                                 forwardBool2,
                                 homingBool;

         ofParameter<float>     speed2;

         ofParameter<int>       opacity,
                                feedrate,
                                threshold,
                                radius,
                                selectedBlob,
                                contourNumber;



         ofEventListener        radiusListener,
                                thresholdListener,
                                feedrateListener;

         int margin;
         std::string layerPath;
         bool directionBool;
         bool mode;
         bool markersBool;

         int camX;
         int camY;




		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        //GUI

        void setupGui(Canvas &canvasArg);
        void changeDestination();
        void markersCall(bool &);
        void startStop(bool &);
        void directionSwitch(bool &);
        void homingToggle(bool &);
        void capture(bool &);
        void changeMode(bool &);
        void changeSpeedFunction(bool &);
        void drawMarkers(bool &);

        //void loadLayer(int& xArg, int& yArg);
        void loadLayer();
        void updateLayer();

        void loadBackground();
        void drawInfo();
        void saveFile();

        //Callers

        void infoCaller();
        void setDrawContour();
        void setDrawPoints();
        void setDrawHatch();
        void setDrawTravel();
        void generateGcodePointsCaller();
        void generateGcodeLines();

        // seters

        void setRadius();
        void setSelectedBlob();


		
};
