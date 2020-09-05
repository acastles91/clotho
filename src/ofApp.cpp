#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(ofColor::lightGray);
    fbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.begin();
    fbo.clear();
    fbo.end();
    layerHeight = ofGetHeight() - margin * 4;
    isLoaded = false;
    contourDraw = false;
    pointsDraw = false;
    infoDraw = false;
    travelDraw = false;
    buildHatch = false;
    buildContour = false;
    drawGcodeParameter = false;
    selectedBlob = 999999;
    setupGui(canvasTest);
}

//--------------------------------------------------------------
void ofApp::update(){

//    if(isLoaded){
//    layers.back()->detectContourUpdate();
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    //fbo.begin();
    //fbo.clear();
    ofSetColor(ofColor::white);
    ofDrawRectangle(canvasTest.rect);

    if (drawInfoParameter){
        drawInfo();
    }

    if (isLoaded){
        //if(layers.back()->drawLayerBool){
        if(drawLayerParameter){
            ofSetColor(ofColor::white);
//            layers.back()->image.draw(canvasTest.rect.x, canvasTest.rect.y, canvasTest.rect.width, canvasTest.rect.height);
              layers.back()->image.draw(canvasTest.rect.x, canvasTest.rect.y);
        }

        //if (layers.back()->hatchBool){
        if (drawHatchParameter){
            layers.back()->drawHatch(canvasTest.xCanvas, canvasTest.yCanvas);
        }

        if (drawContourParameter){
        //if (layers.back()->contourBool){
            layers.back()->drawContour(canvasTest.xCanvas, canvasTest.yCanvas);
        }

        if (drawTravelParameter){
        //if (layers.back()->travelBool){
            layers.back()->drawTravel(canvasTest.xCanvas, canvasTest.yCanvas);
        }

        if (drawGcodeParameter){
            layers.back()->drawGcode(canvasTest.xCanvas, canvasTest.yCanvas);
        }

        if (layers.back()->blobSelected == true){
            layers.back()->drawSelectedBlob(canvasTest.xCanvas, canvasTest.yCanvas);
        }

//        if (layers.back()->hatchLines.size() > 0){
//            for (int i = 0; i < layers.back()->gCodePoints.size(); i++){
//                 ofSetColor(ofColor::red);
//                 ofFill();
//                 ofDrawCircle(layers.back()->pointsTest[i]->x, layers.back()->pointsTest[i]->y,
//                              20);
//            }

        }

//
    }

    //fbo.end();
//}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == 'a'){
        ofLog() << layerTest.image.getImageType();
    }

    if (key == 'b'){
        drawGcodeParameter = !drawGcodeParameter;
    }

    if (key == 'n'){
//        int s{};
//        //ofLog() << "Before loop";
//        for (int i = 0; i < layerTest.image.getHeight(); i++) {
//            for (int e = 0; e < layerTest.image.getWidth(); e++){
//                s += 1;
//                printf("X%d, Y%d", i, e);
//                }
//        }
////        for (int i = 0; i == 5; i++){
////            //s += 1;
//            ofLog() << s;
    }

    if (key == 'e'){
        drawLayerParameter = !drawLayerParameter;
    }
    if (key == 'f'){
        //loadLayer(canvasTest.xCanvas, canvasTest.yCanvas);
        loadLayer();
    }
    if (key == 'g'){
        layers.back()->detectContourSetup();
    }
    if (key == 'h'){
        layers.back()->detectContourUpdate();
    }
    if (key == 'i'){
        layers.back()->contourBool = !layers.back()->contourBool;
        drawContourParameter = !drawContourParameter;
    }
    if (key == 'j'){
        //layers.back()->hatchBool = !layers.back()->hatchBool;
        drawHatchParameter = !drawHatchParameter;
    }
    if (key == 'k'){
        drawInfoParameter = !drawInfoParameter;
    }
    if (key == 'l'){
        layers.back()->generateGcode();
    }
    if (key == 'm'){
        layers.back()->buildContour();
    }
    if (key == 'n'){
        layers.back()->buildTravel();
    }
    if (key == 'o'){
        layers.back()->travelBool = !layers.back()->travelBool;
        drawTravelParameter = !drawTravelParameter;
    }
    if (key == 'p'){
        setRadius();
        printf("Radius = %d", layers.back()->radius);
    }

    if (key == ' '){
        layers.back()->bLearnBackground = true;
    }

    if (key == '+'){
        layers.back()->threshold ++;
        if (layers.back()->threshold > 255){
            layers.back()->threshold = 255;
        }
    }
    if (key == '-'){
        layers.back()->threshold --;
        if (layers.back()->threshold < 0){
            layers.back()->threshold = 0;
        }
    }




}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){



}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    //ofLog() << layerTest.image.getColor(x, y);

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (isLoaded){
        for (int i = 0; i < layers.back()->finalBlobs.size(); i ++){
            if (layers.back()->finalBlobs[i]->boundingBox.inside(x, y)){
                layers.back()->selectedBlob = i;
                layers.back()->blobSelected = true;
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
//void ofApp::loadLayer(int& xArg, int& yArg){
void ofApp::loadLayer(){

    ofFileDialogResult result = ofSystemLoadDialog("Load file");
    if(result.bSuccess) {
      Layer* newLayer = new Layer(threshold, radius, feedrate, contourNumber);
      newLayer->filePath = result.getPath();
      newLayer->image.loadImage(ofToDataPath(newLayer->filePath));
      newLayer->image.resize(canvasTest.width, canvasTest.height);
      newLayer->loaded = true;
      layers.push_back(newLayer);
      layerString.set("File location", newLayer->filePath);
      isLoaded = true;
      ofLog() << "Is loaded = true";
    }
    //ofSetColor(ofColor::white);
    //ofDrawRectangle(canvasTest.rect);
    layers.back()->detectContourSetup();
    layers.back()->detectContourUpdate();
    layers.back()->buildHatch();
    layers.back()->buildTravel();
}

void ofApp::updateLayer(){

    isLoaded = false;
    std::string filePath2;

    filePath2 = layers.back()->filePath;
    delete layers.back();

    //layers.erase(layers.back());
    Layer* newLayer = new Layer(threshold, radius, feedrate, contourNumber);
    newLayer->filePath = filePath2;
    newLayer->image.loadImage(ofToDataPath(newLayer->filePath));
    newLayer->image.resize(canvasTest.width, canvasTest.height);
    newLayer->loaded = true;
    layers.push_back(newLayer);
    layerString.set("File location", newLayer->filePath);
    isLoaded = true;
    ofLog() << "Is loaded = true";

    if (layers.back()->loaded){

        //layers.back()->radius = radius;
        //layers.back()->threshold = threshold;
        //layers.back()->feedrate = feedrate;
        layers.back()->detectContourSetup();
        layers.back()->detectContourUpdate();
        layers.back()->buildHatch();
        layers.back()->buildTravel();
    }

}

//--------------------------------------------------------------


//--------------------------------------------------------------
void ofApp::loadBackground(){

    ofFileDialogResult result = ofSystemLoadDialog("Load Background");
    if(result.bSuccess) {
      backgroundFilePath = result.getPath();
      background.loadImage(ofToDataPath(backgroundFilePath));
      backgroundIsLoaded = true;
      backgroundString.set("Background location", backgroundFilePath);
      //Layer* newLayer = new Layer{};
      //layers.push_back(newLayer);
    }
}

void ofApp::drawInfo(){

    if(isLoaded){
        ofPushMatrix();
        ofTranslate(0, 0, 0);
        ofSetHexColor(0x000000);
        stringstream reportStr;
        reportStr << "bg subtraction and blob detection" << endl
                  << "press ' ' to capture bg" << endl
                  << "threshold " << threshold << " (press: +/-)" << endl
                  << "num blobs found " << layers.back()->contourFinder.nBlobs << ", fps: " << ofGetFrameRate()
                  << "Load layer:   f" << endl
                  << "Detect contour setup:     g" << endl
                  << "Detect contour update:    h" << endl
                  << "Draw contour:             i" << endl
                  << "Draw points:              j" << endl
                  << "Draw info:                k" << endl
                  << "Build hatch:              l" << endl
                  << "Build contour:            m" << endl;
        ofDrawBitmapString(reportStr.str(), canvasTest.xCanvas, canvasTest.height + margin * 2);
        ofPopMatrix();
    }
    if (!isLoaded){
        ofPushMatrix();
        ofTranslate(0, 0, 0);
        ofSetHexColor(0x000000);
        stringstream reportStr;
        reportStr << "No image loaded";
        ofDrawBitmapString(reportStr.str(), canvasTest.xCanvas, canvasTest.height + margin * 2);
        ofPopMatrix();
    }

}


void ofApp::infoCaller(){

    infoDraw = !infoDraw;
}

void ofApp::setDrawContour(){

    drawContourParameter = !drawContourParameter;
}

void ofApp::setDrawPoints(){
    drawHatchParameter = !drawHatchParameter;
}

void ofApp::setDrawHatch(){
   hatchDraw = !hatchDraw;
}

void ofApp::setDrawTravel(){
    drawTravelParameter = !drawTravelParameter;
}

void ofApp::setRadius(){

    layers.back()->radius = radius.get();


}
