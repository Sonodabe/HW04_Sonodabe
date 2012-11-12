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

static const int appWidth = 700;
static const int appHeight = 700;
static const int textureSize = 1024;

class HW04_SonodabeApp : public AppBasic {
public:
    int count;
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    void prepareSettings(Settings* settings);
    void drawMap(TreeNode* root, uint8_t* data_array);
    void colorMap(uint8_t* data_array);
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
    count = 0;
    uint8_t* data_array = (*mySurface).getData();
    colorMap(data_array);
    drawMap(test->tree->root, data_array);

}

void HW04_SonodabeApp::colorMap(uint8_t* data_array){
    Entry_Sonodabe* closest;
    double cx, cy;
    int index;
    for(int posX = 0; posX < appWidth; posX++){
        for(int posY = 0; posY < appHeight; posY++){
            cx = (double)posX/appWidth;
            cy = 1-(double)posY/appHeight;
            closest = (Entry_Sonodabe*)test->getNearest(cx, cy);
            index = 3*(posY*textureSize+posX);
            if(index>=0 && index < textureSize*textureSize*3){
                data_array[index] = closest->r;
                data_array[index+1] = closest->g;
                data_array[index+2] = closest->b;
            } 
        }
        
    }
}

void HW04_SonodabeApp::drawMap(TreeNode* root, uint8_t* data_array){
    if(root == NULL)
        return;
    
    drawMap(root->left, data_array);
    
    int tempX = (int)(appWidth*(root->data->x));
    int tempY = appHeight-(int)(appHeight*(root->data->y));
    int index = 3*(tempY*textureSize+tempX);
    if(index>=0 && index < textureSize*textureSize*3){
        data_array[index] = 255;
        data_array[index+1] = 255;
        data_array[index+2] = 255;
    } 
    drawMap(root->right, data_array);
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
    double mouseX, mouseY;
//    uint8_t* data_array = (*mySurface).getData();
    mouseX = 1.0*event.getX()/appWidth;
    mouseY = 1-1.0*event.getY()/appHeight;
    Entry* close= test->getNearest(mouseX, mouseY);
    
//    int tempX = (int)(appWidth*(close->x));
//    int tempY = appHeight-(int)(appHeight*(close->y));
    
    console() << close->identifier << std::endl;
    

     
}

void HW04_SonodabeApp::update()
{

}

void HW04_SonodabeApp::draw()
{
    gl::draw(*mySurface);

}

CINDER_APP_BASIC( HW04_SonodabeApp, RendererGl )
