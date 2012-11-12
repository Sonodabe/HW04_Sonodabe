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
    void getData();
    void changeColors(TreeNode* root);
    Entry* createArray();
    Starbucks_Sonodabe* test; 
    int getMax(TreeNode* root);
    int maxDiff;
    
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
    
    console() << "Built Tree, getting census data..." << std::endl;
    getData();
    maxDiff = getMax(test->tree->root);
    console() << maxDiff << std::endl;
    changeColors(test->tree->root);
    console() << "Got data, coloring map..." << std::endl;
    colorMap(data_array);
    console() << "Colored Map, drawing points..." << std::endl;
    drawMap(test->tree->root, data_array);




    

}

void HW04_SonodabeApp::changeColors(TreeNode* root){
    if(root == NULL)
        return;
    changeColors(root->left);
    changeColors(root->right);
    
    int deltaPop = (root->data->census2) - (root->data->census1);
    
    int ratio = (int)((255.0*deltaPop)/maxDiff);
    console() << deltaPop<< std::endl;
    
    if(ratio < 0){
        ratio = abs(ratio);
        if(ratio > 255)
            ratio = 255;
        root->data->r = ratio;
        root->data->g = 0;
    }else{
        root->data->r = 0;
        root->data->g = ratio;
    }
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
                data_array[index+2] = 0;
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

int HW04_SonodabeApp::getMax(TreeNode* root){
    if(root == NULL)
        return 0;
    
    
    int change = root->data->census2 - root->data->census1;
    int maxLeft = getMax(root->left);
    int maxRight = getMax(root->right);
    
    return max(max(change, maxLeft), maxRight);
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

void HW04_SonodabeApp::getData(){
    int buffer;
    Entry_Sonodabe* closest;
    int population;
    double latX, latY;
    ifstream cen1("../../../resources/Census_2000.csv");
    while(cen1.good()){
        cen1 >> buffer;
        cen1.get();
        cen1 >> buffer;
        cen1.get();
        cen1 >> buffer;
        cen1.get();
        cen1 >> buffer;
        cen1.get();
        cen1 >> population;
        cen1.get();
        cen1 >> latX;
        cen1.get();
        cen1 >> latY;
        cen1.get();
        
        
        closest = (Entry_Sonodabe*)test->getNearest(latX, latY);
        closest->census1 += population;
    }
    cen1.close();
    
    ifstream cen2("../../../resources/Census_2010.csv");
    while(cen2.good()){
        cen2 >> buffer;
        cen2.get();
        cen2 >> buffer;
        cen2.get();
        cen2 >> buffer;
        cen2.get();
        cen2 >> buffer;
        cen2.get();
        cen2 >> population;
        cen2.get();
        cen2 >> latX;
        cen2.get();
        cen2 >> latY;
        cen2.get();

        closest = (Entry_Sonodabe*)test->getNearest(latX, latY);
        closest->census2 += population;

    }
    cen2.close();
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
