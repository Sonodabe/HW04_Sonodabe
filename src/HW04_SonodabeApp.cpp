#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Starbucks_Sonodabe.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <iostream>
#include <fstream>
#include <time.h>

/**
 Homework 4 Part 3
 Brandon Sonoda
 CSE 274 11:15-12:30
 
 Switch between the map and the rendering by pressing any key (A)
 Magenta dots represent starbucks locations
 
 Click anywhere to locate the nearest starbucks (B)
 
 The rendered map is broken into blocks around the nearest starbucks (C)
 
 The color of the block represents that change of population density for that one starbucks (E? F? EFG? Throw me a bone)
 Red =  negative change in people per starbucks
 Green = positive change in ppl/sbs
 
 
 Coolest idea, 69 minutes til due date: Why don't I compute the crowdedness of each starbucks by taking the
 amount of people per starbucks, and dividing that by the area it covers? Genius. (H)
 Really Crowded = Green
 Sparsely Crowded = Pink
 
 **/


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
    void keyDown(KeyEvent event);
	void update();
	void draw();
    void prepareSettings(Settings* settings);
    void drawMap(TreeNode* root, uint8_t* data_array);
    void colorMap(uint8_t* data_array);
    void colorCrowd(uint8_t* data_array);
    void getData();
    void changeColors(TreeNode* root);
    void findArea(TreeNode* root);
    double maxCrowdedness(TreeNode* root);
    
    Entry* createArray();
    Starbucks_Sonodabe* test; 
    pair<int, int> getMax(TreeNode* root);
    int maxDiff;
    int minDiff;
    
private:
    Surface* popDensityChange;
    Surface* crowdedness;
    float closeX, closeY;
    gl::Texture map;
    int show;
    double maxProp;

};

void HW04_SonodabeApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(appWidth,appHeight);
	(*settings).setResizable(false);
}

void HW04_SonodabeApp::setup()
{
    map = gl::Texture(loadImage("../../../Resources/Map.png"));
    show = 0;
    count = 0;
    closeX = -50;
    closeY = -50;
    
    popDensityChange = new Surface(textureSize, textureSize, false);
    crowdedness = new Surface(textureSize, textureSize, false);
    Entry* first = createArray();

    int n = count;
    test = new Starbucks_Sonodabe;
    test->build(first, n);
    delete [] first; 
    count = 0;
    uint8_t* data_array = (*popDensityChange).getData();
    
    getData();
    pair<int, int> extrema = getMax(test->tree->root);
    maxDiff = extrema.first;
    minDiff = extrema.second;
    changeColors(test->tree->root);
    colorMap(data_array);
    drawMap(test->tree->root, data_array);
    
    maxProp = maxCrowdedness(test->tree->root);
    uint8_t* data_array2 = (*crowdedness).getData();
    colorCrowd(data_array2);
    drawMap(test->tree->root, data_array2);

}

void HW04_SonodabeApp::changeColors(TreeNode* root){
    if(root == NULL)
        return;
    changeColors(root->left);
    changeColors(root->right);
    
    int deltaPop = (root->data->census2) - (root->data->census1);
        
    if(deltaPop <= 0){
        int ratio = (int)((220.0*deltaPop)/minDiff);
        ratio = abs(ratio);
        root->data->r = ratio+35;
        root->data->g = 0;
    }else{
        int ratio = (int)((220.0*deltaPop)/maxDiff);
        root->data->r = 0;
        root->data->g = ratio+35;
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
                closest->pixels++;
            }
        }
    }
}

void HW04_SonodabeApp::colorCrowd(uint8_t* data_array){
    Entry_Sonodabe* closest;
    double cx, cy;
    int index;
    double curProp;
    for(int posX = 0; posX < appWidth; posX++){
        for(int posY = 0; posY < appHeight; posY++){
            cx = (double)posX/appWidth;
            cy = 1-(double)posY/appHeight;
            closest = (Entry_Sonodabe*)test->getNearest(cx, cy);
            index = 3*(posY*textureSize+posX);
            curProp = (double)closest->census2/closest->pixels;
            int colorVal = (int)(255*curProp/400);
            if(index>=0 && index < textureSize*textureSize*3){
                if(colorVal > 255){
                    colorVal = (int)(255*curProp/2500);
                    data_array[index] = 0;
                    data_array[index+1] = colorVal;
                    data_array[index+2] =  0;
                } else{
                    data_array[index] = colorVal;
                    data_array[index+1] = 0;
                    data_array[index+2] =  colorVal/2;
                }
            }
        }
    }
}

double HW04_SonodabeApp::maxCrowdedness(TreeNode* root){
    if(root == NULL)
        return 0;
    
    double meProp = (double)(root->data->census2/(1+root->data->pixels));
    double leftProp = maxCrowdedness(root->left);
    double rightProp = maxCrowdedness(root->right);
    return max(meProp, max(leftProp, rightProp));
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
        data_array[index+1] = 0;
        data_array[index+2] = 255;
    } 
    drawMap(root->right, data_array);
}

pair<int, int> HW04_SonodabeApp::getMax(TreeNode* root){
    if(root == NULL)
        return std::make_pair(0, 0);
    
    
    pair<int, int> leftR = getMax(root->left);
    pair<int, int> rightR = getMax(root->right);
    
    int meMax = root->data->census2 - root->data->census1;
    int meMin = root->data->census1 - root->data->census2;
    
    int maxVal = max(max(leftR.first, rightR.first), meMax);
    int minVal = max(max(leftR.second, rightR.second), meMin);

    return std::make_pair(maxVal, minVal);
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
    mouseX = 1.0*event.getX()/appWidth;
    mouseY = 1-1.0*event.getY()/appHeight;
    Entry* close= test->getNearest(mouseX, mouseY);    
    closeX = (appWidth*(close->x));
    closeY = appHeight-(appHeight*(close->y));
}

void HW04_SonodabeApp::keyDown( KeyEvent event )
{
    show = (++show)%3;
}  

void HW04_SonodabeApp::update()
{

}

void HW04_SonodabeApp::draw()
{
    if(show == 0)
        gl::draw(*popDensityChange);
    else{
        if(show == 1){
            gl::draw(*crowdedness);
        }else
            gl::draw(map  , getWindowBounds());
    }

    gl::drawSolidCircle( Vec2f( closeX, closeY), 5.0f);


}

CINDER_APP_BASIC( HW04_SonodabeApp, RendererGl )
