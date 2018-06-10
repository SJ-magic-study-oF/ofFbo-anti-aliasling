/************************************************************
■description
	ofFboの使用時にanit-aliasingを適用するためのtips.
	ついでに、syphonでのsendも入れておいた.
	
■solution
	void ofFbo::allocate(int width, int height, int internalformat, int numSamples=0)
	において、例えば、
		fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 4);
	とする.
	
■考察
	numSamples は、だいたいどのくらいの値なのだろう?
	以下のURLではnumSamples = 4としているが...
		https://qiita.com/y_UM4/items/b03a66d932536b25b51a
		https://www.khronos.org/opengl/wiki/Multisampling
	
	そこで、screen, 及び numsamples = 0, 1, 2, 3, 4, 16 で比較してみた.
	違いが分かり易かったので、ofFill()のTriangleで比較.
		0	: 確かにジャギが目立つが、これでいいケースもあるだろう.
		4	: Screen と同等くらい
		16	: むしろScreenより綺麗.
	概ね、以上のような値の範囲だと言うことがわかった.
		
	むしろ、ofSetLineWidth() により、ofNoFill()でのLineがかすむ(fbo側で)ことの方が気になった.
	ofSetLineWidth() などとも合わせて、調整する必要があるだろう.
	
■結論
	*	numsamples : 0, 1, 2, ...と現物で徐々に調整(むやみにsample数を上げないこと)
	*	ofFill() + alphaで、上手く調整しながら図形描画(線画は、かすみ易いので).
	*	ofSetLineWidth() も現物調整.
	
	調整は、主に以下をcheck
		triangleなどの斜めLine
		circle
		文字
	
■その他 : 参考URL
	oFでのアンチエイリアスとか。
		http://blog.rettuce.com/of/of-anti-aliasing/
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxSyphon.h"

/************************************************************
************************************************************/

class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
		WIDTH = 1000,
		HEIGHT = 1000,
	};
	
	enum SURFACE_TO_DRAW{
		SURFACE_SCREEN,
		SURFACE_FBO_0,
		SURFACE_FBO_1,
		
		NUM_SURFACE_ID,
	};
	
	/****************************************
	****************************************/
	SURFACE_TO_DRAW id_whichSurfaceToDraw;
	
	ofTexture tex;
	
	ofTrueTypeFont font[2];
	
	ofxSyphonServer mainOutputSyphonServer;
	ofxSyphonServer fbo_TextureSyphonServer[2];
	
	// ofxSyphonClient mClient;
	
	ofFbo fbo[2];

public:
	/****************************************
	****************************************/
	void setup();
	void update();
	void draw();
	
	void drawContents();

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
