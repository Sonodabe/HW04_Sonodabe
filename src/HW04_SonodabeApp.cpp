
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Starbucks_Sonodabe.h"
#include <iostream>
#include <fstream>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_SonodabeApp : public AppBasic {
public:
    int count;
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    Entry* createArray();
};

void HW04_SonodabeApp::setup()
{
    count = 0;
    Entry* first = createArray();
    int n = count;
    Starbucks_Sonodabe* test = new Starbucks_Sonodabe;
    test->build(first, n);
    
}

Entry* HW04_SonodabeApp::createArray(){
    string name;
    double posX, posY;
    ifstream input("../../../resources/Starbucks_2006.csv");
//    ifstream input("../../../resources/Test.csv");
    while(input.good()){
        getline(input, name, ',');
        input >> posX;
        input.get();
        input >> posY;
        input.get();
        count++;
    }
    input.clear();
    input.seekg(0);
    
    Entry* stores  = new Entry[count];
    count = 0;
    
    while(input.good()){
        getline(input, name, ',');
        input >> posX;
        input.get();
        input >> posY;
        input.get();
        (stores+count)->identifier = name;
        (stores+count)->x = posX;
        (stores+count)->y = posY;
        
        count++;
    }
    input.close();
    
    return stores;
}




void HW04_SonodabeApp::mouseDown( MouseEvent event )
{
}

void HW04_SonodabeApp::update()
{
}

void HW04_SonodabeApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04_SonodabeApp, RendererGl )
