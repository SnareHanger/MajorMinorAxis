/*
 *  simpleImage.h
 *  SpatialMedia02
 *
 *  Created by Michael Cohen on 2/3/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"

class simpleImage{

public:
	simpleImage( int w, int h );
	
	void setPixel( int x, int y, int value);
	int getPixel(int x, int y);
	
	bool read(char* fileName);
	bool write(char* fileName);
	
	void draw( int x, int y);
	
	int width, height;
	unsigned char* image;
	
};
