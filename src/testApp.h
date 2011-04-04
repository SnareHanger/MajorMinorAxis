#pragma once

#include "ofMain.h"
#include "simpleImage.h"

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	void compareImages( simpleImage* image1, simpleImage* image2, simpleImage* imageBW );
    void getCentroid( simpleImage* image );
    void setAxes( simpleImage* image );
		
	simpleImage* videoImage;
    simpleImage* backgroundImage;
    simpleImage* imageBW;
    int* center;
    float major;
    float minor;
	
	bool onePressed, twoPressed, threePressed;
	int threshold;
    
    ofVideoGrabber 		vidGrabber;
    unsigned char * 	videoInverted;
    ofTexture			videoTexture;
    int 				camWidth;
    int 				camHeight;
	
};