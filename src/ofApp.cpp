#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(ofColor::lightGray);
    contourDraw = false;
    pointsDraw = false;
    infoDraw = false;
    buildHatch = false;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(ofColor::white);
    ofDrawRectangle(canvasTest.rect);
    if(layerTest.loaded){
        ofSetColor(ofColor::white);
        layerTest.image.draw(canvasTest.xCanvas, canvasTest.yCanvas, canvasTest.width, canvasTest.height);
    }
    if (contourDraw){
        layerTest.detectContourDraw();
    }
    if (pointsDraw){
        layerTest.drawHatch();
    }
    if (infoDraw){
        layerTest.drawInfo();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == 'a'){
        ofLog() << layerTest.image.getImageType();
    }

    if (key == 'n'){
        int s{};
        //ofLog() << "Before loop";
        for (int i = 0; i < layerTest.image.getHeight(); i++) {
            for (int e = 0; e < layerTest.image.getWidth(); e++){
                s += 1;
                printf("X%d, Y%d", i, e);
                }
        }
//        for (int i = 0; i == 5; i++){
//            //s += 1;
            ofLog() << s;
    }
    if (key == 'f'){
        layerTest.loadLayer();
    }
    if (key == 'g'){
        layerTest.detectContourSetup();
    }
    if (key == 'h'){
        layerTest.detectContourUpdate();
    }
    if (key == 'i'){
        contourDraw = !contourDraw;
    }
    if (key == 'j'){
        pointsDraw = !pointsDraw;
    }
    if (key == 'k'){
        infoDraw = !infoDraw;
    }
    if (key == 'l'){
        layerTest.buildHatch();
    }
    if (key == ' '){
        layerTest.bLearnBackground = true;
    }
    if (key == '+'){
        layerTest.threshold ++;
        if (layerTest.threshold > 255){
            layerTest.threshold = 255;
        }
    }
    if (key == '-'){
        layerTest.threshold --;
        if (layerTest.threshold < 0){
            layerTest.threshold = 0;
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
