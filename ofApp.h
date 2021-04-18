#pragma once

#include "ofMain.h"

struct Planets
{
	ofSpherePrimitive sphereprim;
	float x;
	float y;
	float z;
	ofVec3f v;
	ofVec3f F;
	ofVec3f a;
	float radius;
	float m;    // masa planety
	ofVec3f vec_t;    // wektor kierunku
	ofVec3f position;
	float D;
};

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	ofCamera camera;
	ofSpherePrimitive sphere;
	Planets planets[7];
	ofLight pointLight;
	ofLight secondLight;

	ofImage galaxy;
	ofPlanePrimitive backdrop;
	ofMaterial sun;
	ofTexture sunny;
	ofMaterial planet;
	ofMaterial material;
	float G = 10;          // sta³a grawitacji
	float dt = 0.001;
	float M_s = 10000000;   // masa s³oñca

	vector<ofColor> colors;
	int color[7][3] = {
    {0, 0, 238} ,
    {238 ,118, 33} ,
    {205, 85, 85} ,
    {112, 128, 144} ,
    {221, 160, 221} ,
    {142, 56, 142} ,
	{176, 23, 31} ,
	};
};
