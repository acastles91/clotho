#pragma once

#include "ofPolyline.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxFont.h"
#include "ofxClipper.h"
#include "ofPath.h"



class Layer {

public:

    Layer();
    Layer(ofParameter<int> &thresholdArg,ofParameter<int> &radiusArg,ofParameter<int> &feedrateArg);
    std::string  filePath;
    ofFile  file;
    ofFbo buffer;
    ofImage image;
    ofImage background;
    ofBuffer buff;
    bool loaded;
    bool setup;

    int xContour;
    int yContour;
    int width;
    int height;
    int margin;

    bool contourBool;
    bool hatchBool;
    bool infoBool;
    bool travelBool;
    bool drawLayerBool;
    //bool buildHatch;
    //bool buildContour;

    //Contour finder, ofxCV
    //ofxCvColorImageAlpha    colorImgAlpha;
    ofxCvColorImage colorImg;
    ofxCvColorImage colorBg;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    ofxCvContourFinder  contourFinder;
    ofParameter<int> threshold,
                     feedrate,
                     radius;
    int bLearnBackground;
    vector<ofPixels> contour;

    //Hatch & contour

    //std::vector<ofPolyline> hatchLines;
    std::vector< std::vector <ofPolyline> > hatchLines;
    std::vector<ofRectangle> hatchRectangles;
    std::vector<ofPolyline> blobs;
    std::vector<ofPath>     blobPaths;
    std::vector<ofPoint>    centerPoints;
    std::vector<ofPoint>    newCenterPoints;
    std::vector<ofRectangle>    boundingBoxes;
    std::vector<ofRectangle>    boundingBoxes2;
    std::vector<ofPoint>        guide;
    std::vector<ofPolyline>     travelLines;

    //Build & Detect

    void buildContour();
    void buildHatch();
    void detectContourSetup();
    void detectContourUpdate();
    void detectContourDraw(int& xArg, int& yArg);
    void buildTravel();

    //Draw

    void drawHatch(int& xArg, int& yArg);
    void drawContour(int& xArg, int& yArg);
    void drawInfo();
    void drawLayer(int& xArg, int& yArg);
    void drawTravel(int& xArg, int& yArg);


    //Load

    bool isLoaded();
    void loadLayer(int& xArg, int& yArg);
    void loadLayer2();
    void loadBackground();

    //Callers

    void contourDrawCaller();
    void contourUpdateCaller();
    void travelCaller();
    void hatchCaller();





}
;
