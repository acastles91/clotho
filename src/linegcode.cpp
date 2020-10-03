#include "linegcode.h"

LineGcode::LineGcode(std::vector<PointGcode*> &vectorPointsArg,
                     int &widthArg,
                     int &heightArg){

    vectorPoints = vectorPointsArg;
    sprayOn = "M106 \n";
    sprayOff = "M107 \n";
    width = widthArg;
    height = heightArg;
    travelSpeed = 5000;
}


std::string LineGcode::gCodeString(ofParameter<int> &feedrateArg){

    std::string lineString;

    //ofLog() << "vector in line size";

    //ofLog() << vectorPoints.size();

    ofLog() << "Y";
    ofLog() << vectorPoints[0]->y;
    ofLog() << height;
    ofLog() << vectorPoints[0]->y - height;


    boost::format   pointZero = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                  % ofToString(vectorPoints[0]->x - 100)
                                  % ofToString((height - vectorPoints[0]->y))
                                  % ofToString(vectorPoints[0]->z)
                                  % ofToString(0)
                                  % ofToString(travelSpeed);

    boost::format   firstPoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                  % ofToString(vectorPoints[0]->x)
                                  % ofToString((height - vectorPoints[0]->y))
                                  % ofToString(vectorPoints[0]->z)
                                  % ofToString(ofMap(vectorPoints[0]->color.getBrightness(), 0, 255, 0, 1))
                                  % ofToString(travelSpeed);

    boost::format   lastPoint = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                  % ofToString(vectorPoints.back()->x + 100)
                                  % ofToString((height - vectorPoints[0]->y))
                                  % ofToString(vectorPoints.back()->z)
                                  % ofToString(0)
                                  % ofToString(travelSpeed);

    vector<boost::format> gCodePoints;

    lineString = pointZero.str();

    for (int i = 0; i < this->vectorPoints.size() - 1; i++){



        boost::format   gCodePoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                      % ofToString(vectorPoints[i + 1]->x)
                                      % ofToString((height - vectorPoints[i + 1]->y))
                                      % ofToString(vectorPoints[i + 1]->z)
                                      % ofToString(ofMap(vectorPoints[i]->color.getBrightness(), 0, 255, 0, 10))
                                      % ofToString(feedrateArg);


        //ofLog() << ofToString(vectorPoints[i + 1]->color.getBrightness());

        gCodePoints.push_back(gCodePoint);
        lineString += (gCodePoint.str());

    }

    lineString += lastPoint.str();


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
