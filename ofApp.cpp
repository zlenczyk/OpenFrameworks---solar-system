#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	galaxy.load("galaxy.jpg");
	ofDisableArbTex();
	ofLoadImage(sunny, "sun.jpg");
	ofSetVerticalSync(true);

	sphere.setRadius(20);


	for (int i = 0; i < 7; i++)
	{
		colors.push_back(ofColor(color[i][0], color[i][1], color[i][2]));   // ustaw pierwszy kolor z tabeli
		planets[i].sphereprim.setRadius(ofRandom(2,8));                     // ustaw promieñ planety

		float p1 = ofRandom(1, 2);                   // dziêki zmiennym p1 i p2 mo¿emy ustaliæ odleg³oœæ
		float p2 = ofRandom(1, 2);                   // planet od s³oñca w bardzo okreœlonym zakresie

		if (p1 < 1.5) { planets[i].position.x = ofRandom(-150, -30);}
		else { planets[i].position.x = ofRandom(30,150); }
		if (p2 < 1.5) { planets[i].position.y = ofRandom(-150, -30); }
		else { planets[i].position.y = ofRandom(30, 150);}
		planets[i].position.z = ofRandom(-3, 3);

		planets[i].m = ofRandom(1, 2);
		float r = sqrt(pow(planets[i].position.x, 2) + pow(planets[i].position.y, 2)); // odleglosc planety od slonca
		float dl_cieciwy = sqrt(pow(planets[i].position.x - (r), 2) + pow(planets[i].position.y, 2)); //dlugosc cieciwy miedzy planeta
		// a punktem (x=r, y=0)
		float alpha = asin(dl_cieciwy / (2 * r));
		alpha = alpha * 2;
		if (planets[i].position.y == 0 && planets[i].position.x <0) { alpha = PI; }
		if (planets[i].position.y == 0 && planets[i].position.x>0) { alpha = 0; }
		if (planets[i].position.y < 0) {
			alpha *= 180 / PI;
			alpha = 360 - alpha;
			alpha *= PI / 180;
		}
		float predkosc = sqrt(M_s*G/r);      // I Prêdkoœæ Kosmiczna
		float dl_luku = alpha*r;   
		float czas = dl_luku / predkosc;
		float predkosc_katowa = predkosc / r;
		planets[i].v.z = 10;
		planets[i].v.y = r * predkosc_katowa * cos(alpha);      // obliczam wspó³rzêdne prêdkoœci dla x i y, po to, aby prêdkoœæ
		planets[i].v.x = -r * predkosc_katowa * sin(alpha);     // planety by³a zawsze prostopad³a do œrodka masy s³oñca
		planets[i].D = r;

	}

	ofSetSmoothLighting(true);
	pointLight.setDiffuseColor(ofFloatColor(.85, .85, .55));
	pointLight.setSpecularColor(ofFloatColor(1.f, 1.f, 1.f));

	ofSetSphereResolution(64);
	sphere.setPosition(0,0,0);
	sun.setEmissiveColor(ofColor(205, 55, 0));
	sun.setSpecularColor(ofColor(255, 0, 255, 255));
	sun.setShininess(10);
    planet.setShininess(80);
	planet.setSpecularColor(ofColor(255, 0, 255, 255));
}

void ofApp::update() {

	pointLight.setPosition(0,0,0);
	secondLight.setPosition(0, 0, 20);
	for (int i = 0; i < 7; i++)
	{
		planets[i].vec_t = -1*planets[i].position.getNormalized();
		planets[i].F = G * ((planets[i].m * M_s) / (planets[i].D * planets[i].D)) * planets[i].vec_t;
		planets[i].a = planets[i].F / planets[i].m;
		planets[i].v = planets[i].v + planets[i].a * dt;
		planets[i].position = planets[i].position + planets[i].v * dt;
		planets[i].sphereprim.setPosition(planets[i].position);
	}
}

void ofApp::draw() {

	ofDisableLighting();
	ofDisableDepthTest();
	ofDisableAlphaBlending();
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);
	galaxy.getTexture().bind();
	backdrop.resizeToTexture(galaxy.getTexture());
	backdrop.set(ofGetWidth(), ofGetHeight());
	backdrop.draw();
	galaxy.getTexture().unbind();
	ofPopMatrix();
	ofEnableDepthTest();
	ofEnableLighting();
	ofEnableAlphaBlending();

	camera.setGlobalPosition({ 0,0,400 });
	camera.lookAt({0, 0, 0});
	camera.begin();

	pointLight.enable();

	sun.begin();
	sun.setDiffuseColor(ofColor(205,55,0));
	sunny.bind();
	sphere.draw();
	sunny.unbind();
	sun.end();
	
	for (int i = 0; i < 7; i++)
	{
		planet.begin();
		planet.setDiffuseColor(colors[i]);
		planets[i].sphereprim.draw();
		planet.end();
	}

	camera.end();
	ofDisableLighting();
	ofDisableDepthTest();
	ofDisableAlphaBlending();

}


