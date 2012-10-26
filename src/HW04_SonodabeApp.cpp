#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_SonodabeApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void HW04_SonodabeApp::setup()
{
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
