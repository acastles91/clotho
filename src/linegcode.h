#pragma once

#include "ofPolyline.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxFont.h"
#include "ofxClipper.h"
#include "ofPath.h"
#include "pointgcode.h"
#include <boost/format.hpp>

class LineGcode{

public:

    LineGcode(std::vector<PointGcode*> &vectorPointsArg);

    std::vector <PointGcode*> vectorPoints;

    std::string gCodeString(ofParameter<int> &feedrateArg);

    std::string sprayOn;
    std::string sprayOff;



};
