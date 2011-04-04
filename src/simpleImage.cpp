/*
 *  simpleImage.cpp
 *  SpatialMedia02
 *
 *  Created by Michael Cohen on 2/3/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "simpleImage.h"

simpleImage::simpleImage( int w, int h ){
	width = w;
	height = h;
	
	image = new unsigned char [w*h];
}

void simpleImage::setPixel( int x, int y, int value){
	int index = y*width + x;
	
	image[index] = value;
}

int simpleImage::getPixel(int x, int y){
	if (x < 0 || x >= width || y < 0 || y >= height) {
		printf("Error. GetPixel %d %d out of bounds of the image.\n", x, y);
		return 0;
	}
	int index = y*width + x;
	return image[index];
}

bool simpleImage::read(char* fileName){
	char macFileName[512];
	
	sprintf(macFileName, "../../../data/%s", fileName);
	
	FILE* F = fopen(macFileName, "r");
	
	if(F==NULL){
		printf("ERROR couldn't read file\n");
		exit(0);
	}
	
	fread(image, width*height, sizeof(char), F);
	fclose(F);
}

bool simpleImage::write(char* fileName){
	FILE* F = fopen(fileName, "w");
	
	if(F==NULL){
		printf("ERROR couldn't write file\n");
		exit(0);
	}
	
	fwrite(image, width*height, sizeof(char), F);
	fclose(F);
}


void simpleImage::draw( int x, int y){
	glRasterPos2d(x, y);
	glPixelZoom(1, -1);	
	glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, image);
}
