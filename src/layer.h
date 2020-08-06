#pragma once

#include "ofMain.h"

class Layer {

public:

    Layer();

    string  filePath;
    ofFile  file;
    ofFbo buffer;
    ofImage image;
    ofBuffer buff;
    bool loaded;

    bool isLoaded();
    void loadLayer();
    void drawLayer();


}
;
