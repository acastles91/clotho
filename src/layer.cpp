#include "layer.h"

Layer::Layer(){

    loaded = false;
    setup = false;
    margin = ofGetHeight() / 20;
    //height = ofGetHeight()/2 - margin * 2;
    //height = (ofGetWidth() - (ofGetHeight() - margin * 2) - margin * 4) / 2;
    height = ofGetHeight() - margin * 4;
    width = height;
    xContour = margin * 2 + (ofGetHeight() - margin * 4);
    yContour = margin;
    radius = 10;

}

//--------------------------------------------------------------
void Layer::loadLayer(){

    ofFileDialogResult result = ofSystemLoadDialog("Load file");
    if(result.bSuccess) {
      filePath = result.getPath();
      image.loadImage(ofToDataPath(filePath));
      background.loadImage("background.png");
      loaded = true;
    }
}

//--------------------------------------------------------------
void Layer::drawLayer(){

}

//--------------------------------------------------------------
bool Layer::isLoaded(){
    if(loaded){
        ofLog()<< "Layer is loaded";
        return true;
    }else{
        return false;
    }
}

//--------------------------------------------------------------
void Layer::detectContourSetup(){
    if(loaded){
        //colorImgAlpha.allocate(image.getWidth(), image.getHeight());

        colorImg.allocate(image.getWidth(), image.getHeight());
        grayImage.allocate(image.getWidth(), image.getHeight());
        grayBg.allocate(image.getWidth(), image.getHeight());
        grayDiff.allocate(image.getWidth(), image.getHeight());

        bLearnBackground = true;
        threshold = 254;
        setup = true;
        ofLog() << "Detect contour setup executed";
        bLearnBackground = true;
    }
}

//--------------------------------------------------------------
void Layer::detectContourUpdate(){

    if (setup){
        colorBg.setFromPixels(background.getPixels());
        colorImg.setFromPixels(image.getPixels());
        grayImage = colorImg;
        grayBg = colorBg;

        //if (bLearnBackground == true){
            //grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
            //bLearnBackground = false;
        //}
            grayDiff.absDiff(grayBg, grayImage);
            grayDiff.threshold(threshold);
            contourFinder.findContours(grayDiff, 10, height * width, 500, true);
            ofLog() << "Detect contour update executed";
        }
    }


void Layer::detectContourDraw(){

    ofSetHexColor(0xffffff);
    //colorImgAlpha.draw(xContour, yContour, width, height);


    //colorImg.draw(xContour, yContour, width, height);
    //grayImage.draw(xContour, yContour + height + margin, width, height);
    //grayBg.draw(xContour + width + margin, yContour, width, height);
    //grayBg.draw(xContour, yContour, width, height);
    //grayDiff.draw(xContour + width + margin, yContour + height + margin, width, height);
    //ofFill();
    //ofSetHexColor(0x333333);
    //ofDrawRectangle(xContour, yContour, width * 2 + margin, height * 2 + margin);
    ofSetHexColor(0x000000);
    //ofDrawRectangle(xContour, yContour, width, height);
    //contourFinder.draw(xContour, yContour, width, height);
    ofTranslate(xContour, yContour, 0);
    for (int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw();

//        // draw over the centroid if the blob is a hole
//        ofSetColor(255);
//        if(contourFinder.blobs[i].hole){
//            ofDrawBitmapString("hole",
//                contourFinder.blobs[i].boundingRect.getCenter().x,
//                contourFinder.blobs[i].boundingRect.getCenter().y);
//        }
    }
    ofTranslate(0,0,0);


}

void Layer::drawHatch(){

    ofTranslate(xContour, yContour, 0);
    ofSetColor(ofColor::green);
    for (int i = 0; i < hatchLines.size(); i++){
        hatchLines[i].draw();
    }
//    for (int i = 0; i < contourFinder.nBlobs; i++){
//        if(contourFinder.blobs[i].hole){
//            //printf("Blob number %d. Setting div. \n", i);
//            int div;
//            div = (int)round(contourFinder.blobs[i].boundingRect.getHeight() / radius);
//            //printf("div = %d \n", div);
//            ofNoFill();
//            ofDrawRectangle(contourFinder.blobs[i].boundingRect.getX(),
//                            contourFinder.blobs[i].boundingRect.getY(),
//                            contourFinder.blobs[i].boundingRect.getWidth(),
//                            contourFinder.blobs[i].boundingRect.getHeight());
//            for (int e = 0; e <= contourFinder.blobs[i].boundingRect.getHeight(); e += div){
////                //ofLog() << (int)round(contourFinder.blobs[i].boundingRect.getHeight() / radius);
//                printf("blob number %i \t line number %d \t div = %i \n",
//                                                        i,
//                                                        e,
//                                                        div);
//                ofDrawLine((int)contourFinder.blobs[i].boundingRect.getX(),
//                (int)contourFinder.blobs[i].boundingRect.getY() + e,
//                (int)contourFinder.blobs[i].boundingRect.getWidth() + contourFinder.blobs[i].boundingRect.getX(),
//                (int)contourFinder.blobs[i].boundingRect.getY() + e);
//            }


//        }
//    }

////Functional
////        for (int e = 0; e < contourFinder.blobs[i].nPts; e++){
////            ofLog () << firstY;
////            ofSetHexColor(0x000000);
////            ofDrawCircle(contourFinder.blobs[i].pts[e].x,
////                         contourFinder.blobs[i].pts[e].y,
////                         3);
//////___________________________________________________________


}

void Layer::drawInfo(){

    ofSetHexColor(0x000000);
    stringstream reportStr;
    reportStr << "bg subtraction and blob detection" << endl
              << "press ' ' to capture bg" << endl
              << "threshold " << threshold << " (press: +/-)" << endl
              << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
    ofDrawBitmapString(reportStr.str(), margin, margin * 2 + height);
    ofLog() << "Detect contour draw executed";

}

void Layer::buildHatch(){

    printf("Executing build hatch");
    for (int i = 0; i < contourFinder.nBlobs; i++){
        if (contourFinder.blobs[i].hole){
            int div;
            div = (int)round(contourFinder.blobs[i].boundingRect.getHeight() / radius);
            for (int e = 0; e <= contourFinder.blobs[i].boundingRect.getHeight(); e += div){
                ofPolyline lineTest;
                int x1 = (int)contourFinder.blobs[i].boundingRect.getX();
                int y1 = (int)contourFinder.blobs[i].boundingRect.getY() + e;
                int x2 = (int)contourFinder.blobs[i].boundingRect.getWidth() + contourFinder.blobs[i].boundingRect.getX();
                int y2 = (int)contourFinder.blobs[i].boundingRect.getY() + e;
//                vector<ofVec3f> verts = {
//                    {x1, y1, 0.f},
//                    {x2, y2, 0.f}
//                };
                lineTest.addVertex(x1,y1);
                lineTest.addVertex(x2, y2);
                clipL
                hatchLines.push_back(lineTest);
                printf("Line added \t vertex A: x%d, y%d \t vertex B: x%d, y%d \n",
                       x1,
                       y1,
                       x2,
                       y2);
            }
            printf("Length of hatchLines = %d",
                   hatchLines.size());
        }
    }










    //    ofSetColor(ofColor::black);
//    ofTranslate(xContour, yContour, 0);
//    int firstPointX;
//    int firstPointY;
//    int nextPointX;
//    int nextPointY;


//    for (int i = 0; i < contourFinder.nBlobs; i++){
////        ofDefaultVec3 *findPoint;
////        findPoint = std::find(std::begin(contourFinder.blobs[i].pts),
////                              std::end(contourFinder.blobs[i].pts),
////                              )

//        ofSetColor(ofColor::blue);
//        firstPointX = contourFinder.blobs[i].pts[1].x;
//        firstPointY = contourFinder.blobs[i].pts[1].y + radius;
//        ofDrawCircle(firstPointX,
//                     firstPointY,
//                     20);
//        contourFinder.blobs[i].draw();
//        std::vector<ofDefaultVec3> chosenPoints;
//        int tolerance;
//        tolerance = 10;
//        for(int e = 0; e < contourFinder.blobs[i].nPts; e++){
//            if (chosenPoints.size() < 1){
//                if (contourFinder.blobs[i].pts[e].y == firstPointY + tolerance ||
//                    contourFinder.blobs[i].pts[e].y == firstPointY - tolerance){
//                    chosenPoints.push_back(contourFinder.blobs[i].pts[e]);
//                    ofLog() << chosenPoints.size();
//                    ofSetColor(ofColor::salmon);
//                    if (contourFinder.blobs[i].pts[e].x < firstPointX){
//                        ofDrawCircle(contourFinder.blobs[i].pts[e].x + radius,
//                                     firstPointY,
//                                     10);
//                    }else if(contourFinder.blobs[i].pts[e].x > firstPointX){
//                        ofDrawCircle(contourFinder.blobs[i].pts[e].x - radius,
//                                     firstPointY,
//                                     10);
//                    }
//                    ofLog() << chosenPoints[0];
//                }
//        }
//    }
//    }
}
