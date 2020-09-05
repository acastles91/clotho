#pragma once

#include "ofPolyline.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxFont.h"
#include "ofxClipper.h"
#include "ofPath.h"

class Point {

public:

    Point(float xArg,
          float yArg,
          float zArg = 0,
          float eArg = 0,
          bool travelArg = false);

    int x,
        y,
        z,
        e;

    bool travel;

};
