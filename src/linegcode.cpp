#include "linegcode.h"

LineGcode::LineGcode(std::vector<PointGcode*> &vectorPointsArg){

    vectorPoints = vectorPointsArg;
    sprayOn = "M106 \n";
    sprayOff = "M107 \n";
}


std::string LineGcode::gCodeString(ofParameter<int> &feedrateArg){

    std::string lineString;

    boost::format   firstPoint = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                  % ofToString(vectorPoints[0]->x)
                                  % ofToString(vectorPoints[0]->y)
                                  % ofToString(vectorPoints[0]->z)
                                  % ofToString(vectorPoints[0]->color.getBrightness())
                                  % ofToString(feedrateArg);

    vector<boost::format> gCodePoints;

    lineString = firstPoint.str() + sprayOn;

    for (int i = 0; i < this->vectorPoints.size() - 1; i++){



        boost::format   gCodePoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                      % ofToString(vectorPoints[i + 1]->x)
                                      % ofToString(vectorPoints[i + 1]->y)
                                      % ofToString(vectorPoints[i + 1]->z)
                                      % ofToString(vectorPoints[i + 1]->color.getBrightness())
                                      % ofToString(feedrateArg);


        ofLog() << ofToString(vectorPoints[i + 1]->color.getBrightness());

        gCodePoints.push_back(gCodePoint);
        lineString += (gCodePoint.str());

    }

    lineString += sprayOff;


//                                               );
    //ofLog() << points;
    //std::string returnGcode;
//    std::ostringstream gCode;
//    gCode << ("G0 X%d Y%d Z%d",
//             vectorPoints[0]->x,
//             vectorPoints[0]->y * -1,
//             vectorPoints[0]->z)  << endl
//            << "M106 1" << endl;
//    for (int i = 0; i < vectorPoints.size() - 1 ; i ++){
//        gCode += ("G1 X%d Y%d Z%d F%d",
//                vectorPoints[i + 1]->x,
//                vectorPoints[i + 1]->y -1,
//                vectorPoints[i + 1]->z,
//                feedrateArg);
//        gCode += "\n";

//    }
//    gCode += "M107 1\n";

    ofLog() << lineString;
    //returnGcode = "Holi";
    //returnGcode = gCode.str();
    return lineString;

}
;
