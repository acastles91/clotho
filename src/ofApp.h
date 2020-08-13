#pragma once

#include "layer.h"
#include "ofMain.h"
#include "canvas.h"

class ofApp : public ofBaseApp{

	public:

        Layer layerTest;
        Canvas canvasTest;

        bool contourDraw;
        bool pointsDraw;
        bool infoDraw;
        bool buildHatch;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
