#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Starbucks_Sonodabe.h"
#include "cinder/gl/Texture.h"
#include <iostream>
#include <fstream>
#include <time.h>


using namespace ci;
using namespace ci::app;
using namespace std;

static const int appWidth = 500;
static const int appHeight = 500;
static const int textureSize = 1024;

class HW04_SonodabeApp : public AppBasic {
public:
    int count;
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    void prepareSettings(Settings* settings);
    Entry* createArray();
    Starbucks_Sonodabe* test; 
    
private:
    Surface* mySurface;

};

void HW04_SonodabeApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(appWidth,appHeight);
	(*settings).setResizable(false);
}

void HW04_SonodabeApp::setup()
{
    count = 0;
    mySurface = new Surface(textureSize, textureSize, false);
    Entry* first = createArray();
    int n = count;
    test = new Starbucks_Sonodabe;
    test->build(first, n);
    delete [] first;  
    Entry* closest= test->getNearest(.7432, .6105);
    int x;
    
    
    int count = 1;
    int tempX, tempY, index;
    uint8_t* data_array = (*mySurface).getData();
    Node* cur = test->list->sentinel->next;
    int minY = 500;
    while(cur!= test->list->sentinel){
        tempX = (int)(appWidth*(cur->data->x));
        tempY = appHeight-(int)(appHeight*(cur->data->y));
        index = 3*(tempY*textureSize+tempX);
        if(tempY < minY) minY = tempY;
    
        console() << count++ << ": " << tempX << ", " << tempY << std::endl;
        
        if(index>=0 && index < textureSize*textureSize*3){
            data_array[index] = tempX*256/appWidth;
            data_array[index+1] = rand()%256;
            data_array[index+2] = tempY*256/appHeight;
        } 
        cur = cur->next;
    }
    
    console() << minY << std::endl;
    
}



Entry* HW04_SonodabeApp::createArray(){
    string name;
    double posX, posY;
    ifstream input("../../../resources/Starbucks_2006.csv");
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
    gl::draw(*mySurface);

}

void drawPixel(int posX, int posY, uint8_t* data){
    int index = 3*(posY*appWidth+posX);
    if(index>=0 && index <appHeight*appWidth*3){
        data[index] = 0;
        data[index+1] = 0;
        data[index+2] = 0;
    }       
    
}

CINDER_APP_BASIC( HW04_SonodabeApp, RendererGl )
