#pragma once

#include "ofPolyline.h"
#include "ofMain.h"
#include "ofxOpenCv.h"

class Layer {

public:

    Layer();

    string  filePath;
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

    //Contour finder, ofxCV
    //ofxCvColorImageAlpha    colorImgAlpha;
    ofxCvColorImage colorImg;
    ofxCvColorImage colorBg;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    ofxCvContourFinder  contourFinder;
    int threshold;
    int bLearnBackground;
    vector<ofPixels> contour;

    //Hatch

    int radius;
    vector<ofPolyline> hatchLines;

    bool isLoaded();
    void loadLayer();
    void drawLayer();
    void detectContourSetup();
    void detectContourUpdate();
    void detectContourDraw();
    void drawHatch();
    void drawInfo();
    void buildHatch();

}
;
