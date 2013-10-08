#include <SDL2/SDL.h>

#include "cinder/app/AppImplLinux.h"

#include <iostream>

namespace cinder { namespace app {

#define log std::cout << __PRETTY_FUNCTION__ << std::endl;

AppImplLinux::AppImplLinux(cinder::app::App* app) : mApp(app)
{
    log;
}

AppImplLinux::~AppImplLinux () {
    log;
}


/*
    virtual bool		WindowImplLinux::isFullScreen();
    virtual void		WindowImplLinux::setFullScreen( bool fullScreen, const app::FullScreenOptions &options );
    virtual Vec2i		WindowImplLinux::getSize() const;
    virtual void		WindowImplLinux::setSize( const Vec2i &size );
    virtual Vec2i		WindowImplLinux::getPos() const;
    virtual void		WindowImplLinux::setPos( const Vec2i &pos );
    virtual void		WindowImplLinux::close();
    virtual std::string	WindowImplLinux::getTitle() const;
    virtual void		WindowImplLinux::setTitle( const std::string &title );
    virtual void		WindowImplLinux::hide();
    virtual void		WindowImplLinux::show();
    virtual bool		WindowImplLinux::isHidden() const;
    virtual DisplayRef	WindowImplLinux::getDisplay() const;
    virtual RendererRef	WindowImplLinux::getRenderer() const;
    virtual const std::vector<TouchEvent::Touch>&	WindowImplLinux::getActiveTouches() const;
    virtual void*		WindowImplLinux::getNative();
*/

WindowImplLinux::WindowImplLinux( const Window::Format &format,
                                  RendererRef sharedRenderer, AppImplLinux *appImpl ) :
    mWindowOffset( 0, 0 ), mAppImpl( appImpl ), mIsDragging( false ), mHidden( false )
{
    log;
	mFullScreen = format.isFullScreen();
	mDisplay = format.getDisplay();
	mRenderer = format.getRenderer();
	mResizable = format.isResizable();
	mAlwaysOnTop = format.isAlwaysOnTop();
	mBorderless = format.isBorderless();

	mWindowedSize = format.getSize();
	mWindowWidth = mWindowedSize.x;
	mWindowHeight = mWindowedSize.y;
	if( format.isPosSpecified() )
		mWindowOffset = mWindowedPos = format.getPos();
	else {
		Vec2i displaySize = mDisplay->getSize();
		mWindowOffset = mWindowedPos = ( displaySize - mWindowedSize ) / 2;
	}

	createWindow( Vec2i( mWindowWidth, mWindowHeight ), format.getTitle(), mDisplay, sharedRenderer );
	// set WindowRef and its impl pointer to this
	mWindowRef = Window::privateCreate__( this, mAppImpl->getApp() );

    mAppImpl->setWindow(mWindowRef);
	
	//completeCreation();
}

WindowImplLinux::WindowImplLinux( RendererRef renderer, RendererRef sharedRenderer,
                                  AppImplLinux *appImpl ) {
    log;
}

WindowImplLinux::~WindowImplLinux() {
    log;
}

void WindowImplLinux::createWindow( const Vec2i &windowSize, const std::string &title,
                                  const DisplayRef display, RendererRef sharedRenderer ) {
    log;
    Uint32 flags = 0;
    if (mFullScreen)
        flags |= SDL_WINDOW_FULLSCREEN;
    //flags |= SDL_WINDOW_HIDDEN;
    if (mBorderless)
        flags |= SDL_WINDOW_BORDERLESS;
    if (mResizable)
        flags |= SDL_WINDOW_RESIZABLE;
    //flags |= SDL_WINDOW_MINIMIZED;
    //what matches SDL_WINDOW_MAXIMIZED?
    //what matches SDL_WINDOW_FULLSCREEN_DESKTOP?
    //what matches SDL_WINDOW_INPUT_GRABBED?
    //what matches SDL_WINDOW_ALLOW_HIGHDPI?
    
    SDL_Window* window = SDL_CreateWindow(title.c_str(),
                                          0,
                                          0,
                                          mWindowedSize.x,
                                          mWindowedSize.y,
                                          flags);
    if (window == nullptr) {
        throw SDL_GetError();
    }
}


void WindowImplLinux::show() {
    log;
}

void WindowImplLinux::close() {
    log;
}

Vec2i WindowImplLinux::getSize() const {
}

void* WindowImplLinux::getNative() {
    log;
}

const std::vector<TouchEvent::Touch>& WindowImplLinux::getActiveTouches() const {
    log;
}

void WindowImplLinux::setTitle( const std::string &title ) {
    log;
}

bool WindowImplLinux::isHidden() const {
    log;
}

void WindowImplLinux::setSize( const Vec2i &size ) {
    log;
}

DisplayRef	WindowImplLinux::getDisplay() const {
    log;
}

}}
