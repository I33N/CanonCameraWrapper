#include "testApp.h"

testApp::testApp() {
	texIsInitialised = false;
}
//--------------------------------------------------------------
void testApp::setup(){
	if (!camera.setup(0))
	{
		ofLogError() << "no camera detected. type 'damn it' and then enter to quit.";
		string dummy;
		cin >> dummy;
		std::exit(1);
	} else {
		camera.openSession();
		camera.beginLiveView();
		camera.setDeleteFromCameraAfterDownload(true);
		camera.enableDownloadOnTrigger();
		ofAddListener(camera.evtImageDownloaded, this, &testApp::imageDownloaded);
	}
}

//--------------------------------------------------------------
void testApp::update(){
	
	if (camera.grabPixelsFromLiveView())
	{
		if (!texIsInitialised && camera.getLiveViewPixelWidth() > 0)
		{
			tex.allocate(camera.getLiveViewPixelWidth(), camera.getLiveViewPixelHeight(), GL_RGB);
			texIsInitialised = true;
		}
		if (texIsInitialised)
			tex.loadData(camera.getLiveViewPixels(), camera.getLiveViewPixelWidth(), camera.getLiveViewPixelHeight(), GL_RGB);
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	tex.draw(0,0,512,360);
	ofDrawBitmapString(ofToString(camera.getLiveViewPixelWidth()), 0, 10);
	ofDrawBitmapString(ofToString(camera.getLiveViewPixelHeight()), 0, 20);

	if (testLoad.isAllocated())
	{
		testLoad.draw(512,0,512,512.0f*2.0f/3.0f);
		ofDrawBitmapString(ofToString(testLoad.getWidth()), 512, 10);
		ofDrawBitmapString(ofToString(testLoad.getHeight()), 512, 20);
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if (key==' ')
		camera.takePicture();

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::imageDownloaded(string &path) {
	testLoad.loadImage(camera.getLastImagePath());
}