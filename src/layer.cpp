#include "layer.h"

Layer::Layer(){

    loaded = false;
}

//--------------------------------------------------------------
void Layer::loadLayer(){

    ofFileDialogResult result = ofSystemLoadDialog("Load file");
    if(result.bSuccess) {
      filePath = result.getPath();
      image.loadImage(ofToDataPath(filePath));
      loaded = true;
    }
}

//--------------------------------------------------------------
void Layer::drawLayer(){

}

//--------------------------------------------------------------
bool Layer::isLoaded(){
    if(loaded){
        return true;
    }else{
        return false;
    }

}
