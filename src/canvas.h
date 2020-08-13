#pragma once

#include "ofMain.h"

class Canvas {

public:

    Canvas();

    int xCanvas;
    int yCanvas;
    int width;
    int height;
    int margin;
    ofColor color;
    bool visible;
    ofRectangle rect;



    bool isVisible();
    void setVisible();
    void drawCanvas();
//    void drawLayer();
private:


}
;
