#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    camWidth 		= 320;	// try to grab at this size. 
	camHeight 		= 240;
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	//videoInverted 	= new unsigned char[camWidth*camHeight*3];
	//videoTexture.allocate(camWidth,camHeight, GL_RGB);
    
    videoImage = new simpleImage(camWidth, camHeight);
    backgroundImage = new simpleImage(camWidth, camHeight);
    imageBW = new simpleImage(camWidth, camHeight);
    
	threshold = 10;
    
    center = new int[2];
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);
	
	vidGrabber.grabFrame();
	
	if (vidGrabber.isFrameNew()){
		unsigned char * pixels = vidGrabber.getPixels();
		for (int i = 0; i < camWidth; i++){
            for (int j = 0; j < camHeight; j++) {
                videoImage->setPixel(i, j, pixels[(i+j*camWidth)*3]);
            }
        }
		//videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(0xffffff);
	//vidGrabber.draw(20,20);
	//videoTexture.draw(20+camWidth,20,camWidth,camHeight);

    videoImage->draw(20, 20);
    
    if (backgroundImage != NULL) {
        compareImages(videoImage, backgroundImage, imageBW);
        imageBW->draw(20+camWidth, 20);
        setAxes(imageBW);
        
        
        char theThresh[255];
        
        sprintf(theThresh, "Threshold: %i", threshold);
        
        ofDrawBitmapString(theThresh, 840, 450);
        
        
        
        ofSetColor(255, 0, 0);
        //    ofCircle(center[0], center[1], 5);
        ofPushMatrix();
        ofTranslate(20+camWidth, 20);
        ofCircle(center[0], center[1], 5);
        ofLine(center[0]+(100*cos(major) ), center[1] + (100*sin(major)), center[0]-(100*cos(major) ), center[1] - (100*sin(major)));
        ofSetColor(0, 255, 0);
        ofLine(center[0]+(100*sin(minor) ), center[1] + (100*cos(minor)), center[0]-(100*sin(minor) ), center[1] - (100*cos(minor)));
        ofPopMatrix();
        
        ofSetColor(0, 0, 0);
        char centroid[255];
        
        
        
        sprintf(centroid, "Centroid: x: %i y: %i, Major: %f, Minor: %f", center[0], center[1], major, minor);
        
        ofDrawBitmapString(centroid, 840, 460);
    }
    
}

void testApp::compareImages( simpleImage* image1, simpleImage* image2, simpleImage* imageBW ){
	for (int i = 0; i < image1->width; i++) {
		for (int j = 0; j < image1->height; j++) {
			int image1Pixel, image2Pixel;
			
			image1Pixel = image1->getPixel(i, j);
			image2Pixel = image2->getPixel(i, j);
			
			if(abs(image1Pixel - image2Pixel) > threshold){
				imageBW->setPixel(i, j, 255);
			} else {
				imageBW->setPixel(i, j, 0);
			}
		}
	}
    
    
    
}

void testApp::getCentroid( simpleImage* image){
    int xSum = 0;
    int ySum = 0;
    int pixelCount = 0;
    
    for (int i = 0; i < image->width; i++) {
        for (int j = 0; j < image->height; j++) {
            if (image->getPixel(i, j) == 255) {
                pixelCount++;
                xSum += i;
                ySum += j;
            }
        }
    }
    
    float avgX, avgY = 0;
    if(pixelCount > 0){        
        avgX = xSum / pixelCount;
        avgY = ySum / pixelCount;
    } else {
        avgX = 0;
        avgY = 0;
    }
    
    center[0] = (int)avgX;
    center[1] = (int)avgY;
}

void testApp::setAxes(simpleImage* image){
    getCentroid(image);
    
    int DX2, DY2, DXDY = 0;
    int pixelCount = 0;
    
    for (int i = 0; i < image->width; i++) {
        for (int j = 0; j < image->height; j++) {
            if (image->getPixel(i, j) == 255) {
                pixelCount++;
                int dX = (i - center[0]);
                int dY = (j - center[1]);
                
                DX2 += (dX*dX);
                DY2 += (dY*dY);
                
                DXDY += (dX*dY);
            }
        }
    }
    
    
    if(pixelCount > 0){
        DX2 /= pixelCount;
        DY2 /= pixelCount;
        DXDY /= pixelCount;
        
        if(DXDY < 0)
            DXDY *= -1;
        
        major = ofRadToDeg(atan2(DY2, DX2));
        
        minor = major + 90;
    }
    
    
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch (key){
            //		case '1': 
            //			onePressed = true;
            //			twoPressed = false;
            //			threePressed = false;
            //			break;
            //		case '2':
            //			onePressed = false;
            //			twoPressed = true;
            //			threePressed = false;
            //			break;
            //		case '3':
            //			onePressed = false;
            //			twoPressed = false;
            //			threePressed = true;
            //			break;
		case OF_KEY_UP:
			threshold++;
			break;
		case OF_KEY_DOWN:
			threshold--;
			break;
            
	} 
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    for (int i = 0; i < camWidth; i++) {
        for (int j = 0; j < camHeight; j++) {
            backgroundImage->setPixel(i, j, videoImage->getPixel(i, j));
        }
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

