#pragma once

#include "ofMain.h"

class Canvas {

public:

    Canvas();

    static int xCanvas;
    static int yCanvas;
    static int width;
    static int height;
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
