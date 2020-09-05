#include "layer.h"
#include "blob.h"

Layer::Layer(){

    loaded = false;
    setup = false;
    contourBool = false;
    hatchBool = false;
    infoBool = false;
    travelBool = false;
    drawLayerBool = false;
    margin = ofGetHeight() / 20;
    //height = ofGetHeight()/2 - margin * 2;
    //height = (ofGetWidth() - (ofGetHeight() - margin * 2) - margin * 4) / 2;
    height = ofGetHeight() - margin * 4;
    width = height;
    xContour = margin * 2 + (ofGetHeight() - margin * 4);
    yContour = margin;
    radius = 10;
    blobSelected = false;
}

//--------------------------------------------------------------

Layer::Layer(ofParameter<int> &thresholdArg,ofParameter<int> &radiusArg,ofParameter<int> &feedrateArg, ofParameter<int> &contourNumberArg){


    loaded = false;
    setup = false;
    contourBool = false;
    hatchBool = false;
    infoBool = false;
    travelBool = false;
    drawLayerBool = false;
    margin = ofGetHeight() / 20;
    //height = ofGetHeight()/2 - margin * 2;
    //height = (ofGetWidth() - (ofGetHeight() - margin * 2) - margin * 4) / 2;
    height = ofGetHeight() - margin * 4;
    width = height;
    xContour = margin * 2 + (ofGetHeight() - margin * 4);
    yContour = margin;
    threshold = thresholdArg;
    radius = radiusArg;
    feedrate = feedrateArg;
    contourNumber = contourNumberArg;



}

//--------------------------------------------------------------
void Layer::loadLayer(int& xArg, int& yArg){

//    ofFileDialogResult result = ofSystemLoadDialog("Load file");
//    if(result.bSuccess) {
//      filePath = result.getPath();
//      image.loadImage(ofToDataPath(filePath));
//      image.resize(xArg, yArg);
//      background.loadImage("background.png");
//      loaded = true;
//    }
//    detectContourSetup();
}

//--------------------------------------------------------------

void Layer::loadLayer2(){

//    ofFileDialogResult result = ofSystemLoadDialog("Load file");
//    if(result.bSuccess) {
//      filePath = result.getPath();
//      image.loadImage(ofToDataPath(filePath));
//      image.resize(33, 44);
//      background.loadImage("background.png");
//      loaded = true;
//    }
}

//--------------------------------------------------------------
void Layer::drawLayer(int &xArg, int &yArg){

}

//--------------------------------------------------------------
bool Layer::isLoaded(){
    if(loaded){
        //ofLog()<< "Layer is loaded";
        return true;
    }else{
        return false;
    }
}

//--------------------------------------------------------------
void Layer::detectContourSetup(){
    if(loaded){
        colorImg.allocate(image.getWidth(), image.getHeight());
        grayImage.allocate(image.getWidth(), image.getHeight());
        grayBg.allocate(image.getWidth(), image.getHeight());
        grayDiff.allocate(image.getWidth(), image.getHeight());

        bLearnBackground = true;
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
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        contourFinder.findContours(grayDiff, radius * 2, height * width, contourNumber, true);
        ofLog() << "Detect contour update executed";
        }
    }

void Layer::buildHatch(){

    printf("Executing build hatch");
    for (int i = 0; i < contourFinder.nBlobs; i++){
        if (contourFinder.blobs[i].hole){
            ofPolyline blobPoly;
            ofPolyline contourScaled;
            ofPoint center;
            ofPath blobPath;
            std::vector< std::vector <ofPolyline> > hatchLinesBlob;
            ofRectangle boundingBoxBlob;
            boundingBoxBlob = contourFinder.blobs[i].boundingRect;
            center.set(contourFinder.blobs[i].centroid);
            int heightScale;
            int widthScale;
            heightScale = contourFinder.blobs[i].boundingRect.getHeight() - 2 * radius;
            widthScale = contourFinder.blobs[i].boundingRect.getWidth() - 2 * radius;
            blobPoly.addVertices(contourFinder.blobs[i].pts);
            blobPoly.translate(-center);
            blobPoly.scale(widthScale / contourFinder.blobs[i].boundingRect.getWidth(), heightScale / contourFinder.blobs[i].boundingRect.getHeight());
            blobPoly.translate(ofPoint(center.x, center.y, 0));

            for (int i = 0; i < blobPoly.size(); i++){
                blobPath.lineTo(blobPoly[i]);

            }
            blobPath.setStrokeWidth(5);
            blobPath.close();
            blobPath.setStrokeColor(ofColor::red);
            blobPath.setFilled(false);
            blobs.push_back(blobPoly);
            blobPaths.push_back(blobPath);

            int div;
            div = (int)round(contourFinder.blobs[i].boundingRect.getHeight() / radius);
            //for (int e = 0; e <= contourFinder.blobs[i].boundingRect.getHeight(); e += div)
            for (int e = 0; e <= contourFinder.blobs[i].boundingRect.getHeight(); e += radius){
                ofPolyline lineTest;
                ofx::Clipper clipper;
                ofPolyline  secondLineTest;
                std::vector<ofPolyline> linesHatch;

                //auto contourClipper = clipper.toClipper(contourFinder.blobs[i].pts);
                int x1 = (int)contourFinder.blobs[i].boundingRect.getX();
                int y1 = (int)contourFinder.blobs[i].boundingRect.getY() + e;
                int x2 = (int)contourFinder.blobs[i].boundingRect.getWidth() + contourFinder.blobs[i].boundingRect.getX();
                int y2 = (int)contourFinder.blobs[i].boundingRect.getY() + e;

                lineTest.addVertex(x1, y1);
                lineTest.addVertex(x2, y2);
                ofRectangle rectTest(x1, y1, (int)contourFinder.blobs[i].boundingRect.getWidth(), radius);

                //ofRectangle rectTest(x1, y1, (int)contourFinder.blobs[i].boundingRect.getWidth(), div / 2);
                hatchRectangles.push_back(rectTest);
                ofPath pathTest;


                pathTest.rectangle(rectTest);
                clipper.addPath(pathTest, ClipperLib::ptSubject);
                clipper.close(blobPoly);

                //Need to find the way somehow to substract the contour from the hatch

                contourScaled = blobPoly;

                contourScaled.translate(-center);
                contourScaled.scale(0.5, 0.5);
                contourScaled.translate(ofPoint(center.x, center.y, 0));
                clipper.close(contourScaled);

                clipper.addPolyline(blobPoly, ClipperLib::ptClip);
                std::vector<ofPolyline> intersection = clipper.getClipped(ClipperLib::ClipType::ctIntersection);
                std::vector<ofPolyline> intersectionClipped;


                for (int a = 0; a < intersection.size(); a++){
                    secondLineTest = intersection[a].getVertices();
                    ofPolyline thirdLineTest;
                    for (int b = 0; b < secondLineTest.size(); b++){
                        if(contourScaled.inside(secondLineTest[b])){
                            thirdLineTest.addVertex(secondLineTest[b]);
//                        ofLog() << secondLineTest[b];
                        }
                    }

                    intersectionClipped.push_back(thirdLineTest);

                }




                hatchLines.push_back(intersection);
                hatchLinesBlob.push_back(intersection);
                //boundingBoxBlob = rectTest;
                //hatchLines.push_back(lineTest);
//                printf("Line added \t vertex A: x%d, y%d \t vertex B: x%d, y%d \n",
//                       x1,
//                       y1,
//                       x2,
//                       y2);
            }
            Blob* tempBlob = new Blob(blobPoly, boundingBoxBlob, hatchLinesBlob);
            finalBlobs.push_back(tempBlob);
        }
    }
}

void Layer::buildTravel(){

    for (int i = 0; i < finalBlobs.size() - 1; i++){
        ofx::Clipper clipper;
        ofPolyline contour1;
        ofPolyline contour2;
        ofPolyline lineTravel;
        ofPoint a;
        ofPoint b;
        int x1;
        int y1;
        int x2;
        int y2;
        ofSetColor(ofColor::magenta);
        ofFill();
        contour1.addVertices(finalBlobs[i]->contour.getVertices());
        clipper.close(contour1);
        contour2.addVertices(finalBlobs[i + 1]->contour.getVertices());
        clipper.close(contour2);
        a.set(contour1[0]);
        b.set(contour2[0]);
        lineTravel.addVertex(a);
        lineTravel.addVertex(b);
        travelLines.push_back(lineTravel);
//        printf("Travel line added \t vertex A: x%d, y%d \t vertex B: x%d, y%d \n",
//               x1,
//               y1,
//               x2,
//               y2);

    }
    printf("Build travel executed");

    }
//    for (int i = 0; i < contourFinder.nBlobs - 1; i++){
//        ofx::Clipper clipper;
//        ofPolyline contour1;
//        ofPolyline contour2;
//        ofPolyline lineTravel;
//        ofPoint a;
//        ofPoint b;
//        int x1;
//        int y1;
//        int x2;
//        int y2;
//        ofSetColor(ofColor::magenta);
//        ofFill();
//        contour1.addVertices(contourFinder.blobs[i].pts);
//        clipper.close(contour1);
//        contour2.addVertices(contourFinder.blobs[i + 1].pts);
//        clipper.close(contour2);
//        a.set(contour1[0]);
//        b.set(contour2[0]);
//        lineTravel.addVertex(a);
//        lineTravel.addVertex(b);
//        travelLines.push_back(lineTravel);
//        printf("Travel line added \t vertex A: x%d, y%d \t vertex B: x%d, y%d \n",
//               x1,
//               y1,
//               x2,
//               y2);

//    }
//    printf("Build travel executed");
//}


void Layer::detectContourDraw(int& xArg, int& yArg){

//    ofSetHexColor(0xffffff);
//    ofSetHexColor(0x000000);
//    ofPushMatrix();
//    ofTranslate(xArg, yArg, 0);
//    for (int i = 0; i < contourFinder.nBlobs; i++){
//        contourFinder.blobs[i].draw();

////        // draw over the centroid if the blob is a hole
////        ofSetColor(255);
////        if(contourFinder.blobs[i].hole){
////            ofDrawBitmapString("hole",
////                contourFinder.blobs[i].boundingRect.getCenter().x,
////                contourFinder.blobs[i].boundingRect.getCenter().y);
////        }
//    }
//    ofTranslate(0,0,0);
//    ofPopMatrix();


}

void Layer::drawHatch(int& xArg, int& yArg){
    ofPushMatrix();
    ofTranslate(xArg, yArg, 0);

    ofSetColor(ofColor::purple);


    for (int i = 0; i < hatchLines.size(); i++){
        for (int e = 0; e < hatchLines[i].size(); e++){
            vectorTest = hatchLines[i][e].getVertices();
            hatchLines[i][e].draw();
            for (int c = 0; c < vectorTest.size(); c++){
                ofDrawCircle(vectorTest[c][0],
                             vectorTest[c][1],
                             15);
            }
////            hatchLines[i][e].draw();
////            printf("Hatchlines sub size: %d \n",
////                   hatchLines[i].size());
        }
////    printf("Hatchlines size: %d \n",
////           hatchLines.size());

    }
    ofPopMatrix();

}

void Layer::drawInfo(){

    if(loaded){
        ofPushMatrix();
        ofTranslate(0, 0, 0);

        ofSetHexColor(0x000000);
        stringstream reportStr;
        reportStr << "bg subtraction and blob detection" << endl
                  << "press ' ' to capture bg" << endl
                  << "threshold " << threshold << " (press: +/-)" << endl
                  << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate()
                  << "Load layer:   f" << endl
                  << "Detect contour setup:     g" << endl
                  << "Detect contour update:    h" << endl
                  << "Draw contour:             i" << endl
                  << "Draw points:              j" << endl
                  << "Draw info:                k" << endl
                  << "Build hatch:              l" << endl
                  << "Build contour:            m" << endl;
        ofDrawBitmapString(reportStr.str(), margin, margin + height);
        ofPopMatrix();
    }
    if (!loaded){
        ofPushMatrix();
        ofTranslate(0, 0, 0);
        ofSetHexColor(0x000000);
        stringstream reportStr;
        reportStr << "No image loaded";
        ofDrawBitmapString(reportStr.str(), margin, margin + height);
        ofPopMatrix();
    }

}




void Layer::drawTravel(int& xArg, int& yArg){
    ofPushMatrix();
    ofTranslate(xArg, yArg);
    ofSetColor(ofColor::blue);
    for (int i = 0; i < travelLines.size(); i++){
        //blobPaths[i].draw(8,6);
        travelLines[i].draw();
    }
    ofPopMatrix();
}

void Layer::buildContour(){

//    for (int i = 0; i < contourFinder.nBlobs; i ++){
//        if (contourFinder.blobs[i].hole){
//            ofPolyline blobPoly;
//            ofPath  blobPath;
//            ofPoint center;
//            ofRectangle boundingBox;
//            blobPoly.addVertices(contourFinder.blobs[i].pts);
//            center.set(contourFinder.blobs[i].centroid);
//            centerPoints.push_back(center);
//            boundingBox = contourFinder.blobs[i].boundingRect;

//            int heightScale;
//            int widthScale;
//            heightScale = contourFinder.blobs[i].boundingRect.getHeight() - 2 * radius;
//            widthScale = contourFinder.blobs[i].boundingRect.getWidth() - 2 * radius;

//            blobPoly.translate(-center);
//            blobPoly.scale(widthScale / contourFinder.blobs[i].boundingRect.getWidth(), heightScale / contourFinder.blobs[i].boundingRect.getHeight());
//            //blobPoly.scale(0.5, 0.5);
//            blobPoly.translate(ofPoint(center.x + margin, center.y + margin, 0));


//            for (int i = 0; i < blobPoly.size(); i++){
//                blobPath.lineTo(blobPoly[i]);

//            }
//            blobPath.setStrokeWidth(5);
//            blobPath.close();
//            blobPath.setStrokeColor(ofColor::red);
//            blobPath.setFilled(false);
//            blobs.push_back(blobPoly);
//            blobPaths.push_back(blobPath);

//            ofSetHexColor(0x000000);
//            //string contourString;
//            //contourString = "blobPoly size: ";

//            ofDrawBitmapString("hola", ofGetWidth() / 2, ofGetHeight() / 2);
//            ofLog() << "Detect contour draw executed";
//            ofPopMatrix();
//        }
    }
//            ofPath  blobPath;
//            ofx::Clipper clipper;
//            ofRectangle boundingBox;
//            ofRectangle boundingBox2;
//            ofPoint center;
//            ofPoint newCenter;
//            ofPoint newOrigin;

//            center = contourFinder.blobs[i].centroid;
//            centerPoints.push_back(center);
//            //ofPushMatrix();
//            //ofTranslate(center);

//            blobPoly.addVertices(contourFinder.blobs[i].pts);
//            clipper.close(blobPoly);
//            blobPoly.close();
//            int x;
//            x = -100 + 2 * radius;
//            blobPath.setMode(ofPath::Mode::POLYLINES);

//            boundingBox = blobPoly.getBoundingBox();
//            boundingBoxes.push_back(boundingBox);
//            newCenter.set(boundingBox.x, boundingBox.y);
//            newCenterPoints.push_back(newCenter);

//            blobPoly.scale(0.5, 0.5);

//            ofPoint guidePoint;
//            guidePoint.set(0,0,0);
//            guide.push_back(guidePoint);


//            boundingBox2 = blobPoly.getBoundingBox();
//            blobPoly.translate(ofPoint(contourFinder.blobs[i].boundingRect.x - blobPoly.getBoundingBox().width /2, contourFinder.blobs[i].boundingRect.y - blobPoly.getBoundingBox().height /2));
//            boundingBoxes2.push_back(boundingBox2);
//            newOrigin.set(boundingBox.getX() + boundingBox.getWidth() / 2 - boundingBox2.getWidth() / 2, boundingBox.getY() + boundingBox.getHeight() / 2 - boundingBox2.getHeight() / 2);


//            for (int i = 0; i < blobPoly.size(); i++){
//                blobPath.lineTo(blobPoly[i]);

//            }
//            blobPath.setStrokeWidth(5);
//            blobPath.close();
//            blobPath.setStrokeColor(ofColor::red);
//            blobPath.setFilled(false);

//            //}
//            blobPaths.push_back(blobPath);
//            blobs.push_back(blobPoly);
//            //ofPopMatrix();
//        }
//    }
//    ofLog() << "Length of blobs: %d" << blobs.size();


void Layer::drawContour(int& xArg, int& yArg){

    //for (int i = 0; i < blobPaths.size(); i++){
        //blobPaths[i].draw(8,6);
        //blobPaths[i].draw(xArg, yArg);
    ofPushMatrix();
    ofTranslate(xArg, yArg, 0);
    ofSetColor(ofColor::salmon);
        for (int i = 0; i < blobs.size(); i++){
            blobs[i].close();
            blobs[i].draw();
    }
    ofSetColor(ofColor::white);
    ofPopMatrix();

//    for (int i = 0; i < contourFinder.nBlobs - 1; i++){
//        ofPolyline lineTest;
//        ofSetColor(ofColor::magenta);
//        ofFill();
//        lineTest.addVertices(contourFinder.blobs[i].pts);
//        ofDrawCircle(lineTest[1], 15);
//    }
//_____________Magenta and Cyan points
//    for (int i = 0; i < contourFinder.nBlobs - 1; i++){
////        for (int e = 0; e < contourFinder.blobs[i].nPts; e++){

//            ofPolyline blobPoly;
//            ofx::Clipper clipper;
//            blobPoly.addVertices(contourFinder.blobs[i].pts);
//            clipper.close(blobPoly);
//            //std::vector<T>* p = &blobPoly[0];
//            ofSetColor(ofColor::magenta);
//            ofFill();
//            ofDrawCircle(blobPoly[blobPoly.size() - 1], 15);
//            ofSetColor(ofColor::cyan);
//            ofFill();
//            ofDrawCircle(blobPoly[1], 15);
//        //}
//_____________________________
    }


//    for (int i = 0; i < contourFinder.nBlobs; i ++){
//        contourFinder.blobs[i].draw(xArg, yArg);
//    }

//    for (int i = 0; i < contourFinder.nBlobs; i ++){
//        ofSetColor(ofColor::khaki);
//        ofFill();
//        ofDrawCircle(ofPoint(contourFinder.blobs[i].centroid[0] + margin, contourFinder.blobs[i].centroid[1] + margin, 0), 30);
//    }
//    for (int i = 0; i < centerPoints.size(); i++){
//        ofSetColor(ofColor::red);
//        ofDrawCircle(centerPoints[i].x, centerPoints[i].y, 30);
//    }
//    for (int i = 0; i < newCenterPoints.size(); i++){
//        ofSetColor(ofColor::yellow);
//        ofDrawCircle(newCenterPoints[i].x, newCenterPoints[i].y, 5);
//    }
//    for (int i = 0; i < boundingBoxes2.size(); i++){
//        ofSetColor(ofColor::blue);
//        ofNoFill();
//        ofDrawRectangle(boundingBoxes2[i]);
//    }

//    for (int i = 0; i < boundingBoxes.size(); i++){
//        ofSetColor(ofColor::yellow);
//        ofNoFill();
//        ofDrawRectangle(boundingBoxes[i]);
//    }
//    for (int i = 0; i < guide.size(); i++){
//        ofSetColor(ofColor::pink);
//        ofDrawCircle(guide[i].x, guide[i].y, 5);
//    }

//    for (int i = 0; i < blobs.size(); i++){
//        ofSetColor(ofColor::pink);
//        ofFill();

//        blobs[i].draw();
//    }
    //ofTranslate(0, 0, 0);
    //ofPopMatrix();
//}

void Layer::hatchCaller(){

    hatchBool = !hatchBool;
}


void Layer::contourUpdateCaller(){

    contourBool = !contourBool;
}


void Layer::contourDrawCaller(){

    contourBool = !contourBool;
}

void Layer::travelCaller(){

    travelBool = !travelBool;
}

void Layer::generateGcode(){
    //Hatch is not drawn & contour is not closed
    ofx::Clipper clipper;
    for (int i = 0; i < finalBlobs.size(); i++){
        ofPolyline contourVertices = finalBlobs[i]->contour.getVertices();
        clipper.close(contourVertices);
        contourVertices.close();
            for (int e = 0; e < contourVertices.size(); e++){
                Point* tempPoint = new Point(contourVertices [e][0], contourVertices[e][1]);
                finalBlobs[i]->gCodePoints.push_back(tempPoint);
            }
//            for (int g = 0; g < finalBlobs[i]->hatchLines.size(); g++){
//                for (int h = 0; h < finalBlobs[i]->hatchLines[g].size(); h++){
//                    ofPolyline hatchVertices = finalBlobs[i]->hatchLines[g][h].getVertices();
//                    Point* tempPoint2 = new Point(hatchVertices[h][0], hatchVertices[h][1]);
//                    finalBlobs[i]->gCodePoints.push_back(tempPoint2);
//                    printf("x %d y %d \n",
//                           hatchVertices[h][0],
//                           hatchVertices[h][1]);

//                }



//            }
            ofPolyline hatchVertices;
            for (int a = 0; a < hatchLines.size(); a++){
                for (int b = 0; b < hatchLines[a].size(); b++){
                    for (int c = 0; c < hatchLines[a][b].size(); c++){
                        Point* tempPoint = new Point(hatchLines[a][b][c][0],
                                                     hatchLines[a][b][c][1]);
                        printf("Test point x %d y %d \n",
                               tempPoint->x,
                               tempPoint->y);
                        finalBlobs[i]->gCodePoints.push_back(tempPoint);

                    }

                }
            }
        }

//            for (int a = 0; a < hatchLines.size(); a++){

//                for (auto& line: hatchLines[a]){

//                     hatchVertices = line.getVertices();
//                     hatchLines2.push_back(hatchVertices);
////                     for (int f = 0; f < hatchVertices.size(); f++){
////                         Point* tempPoint2 = new Point(hatchVertices [f][0], hatchVertices[f][1]);
////                         finalBlobs[i]->gCodePoints.push_back(tempPoint2);
////                     }
//                }
//            }


//    }
//    for (int e = 0; e < finalBlobs.size(); e++){
//        for (int a = 0; a < finalBlobs[e]->gCodePoints.size(); a++){
//            printf("x %d y %d z %d e %d",
//                   finalBlobs[e]->gCodePoints[a][0],
//                   finalBlobs[e]->gCodePoints[a][1],
//                   finalBlobs[e]->gCodePoints[a][2],
//                   finalBlobs[e]->gCodePoints[a][3]);
//        }
//    }




    ofLog() << "G-code generated";

}

void Layer::drawGcode(int& xArg, int& yArg){
//    ofSetColor(ofColor::red);
//    ofFill();
//    ofDrawCircle(100,
//                 100,
//                 20);
    ofPushMatrix();
    ofTranslate(xArg, yArg, 0);
    for (int e = 0; e < finalBlobs.size(); e++){
        for (int a = 0; a < finalBlobs[e]->gCodePoints.size(); a++){
            ofSetColor(ofColor::red);
            ofFill();
            ofDrawCircle(float(finalBlobs[e]->gCodePoints[a]->x),
                         float(finalBlobs[e]->gCodePoints[a]->y),
                         20);
//            printf("x = %d, y = %d \n",
//                   finalBlobs[e]->gCodePoints[a]->x,
//                   finalBlobs[e]->gCodePoints[a]->y);
        }
    }
    ofPopMatrix();
    //ofLog() << "Draw Gcode called";

}

void Layer::drawSelectedBlob(int& xArg, int& yArg){
    ofPushMatrix();
    ofTranslate(xArg, yArg, 0);
    ofSetColor(ofColor::magenta);
    ofNoFill();
    ofDrawRectangle(finalBlobs[selectedBlob]->boundingBox);
    ofLog() << "Draw selected blob called";
    ofPopMatrix();

}
