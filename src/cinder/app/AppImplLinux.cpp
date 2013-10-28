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


WindowImplLinux::WindowImplLinux( const Window::Format &format,
                                  RendererRef sharedRenderer, AppImplLinux *appImpl ) :
    mWindowOffset( 0, 0 ), mRenderer(sharedRenderer), mAppImpl( appImpl ), mIsDragging( false ), mHidden( false )
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

bool WindowImplLinux::isFullScreen() {
    Uint64 flags = SDL_GetWindowFlags(mWindow);
    return (flags & SDL_WINDOW_FULLSCREEN) || (flags && SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void WindowImplLinux::setFullScreen( bool fullScreen, const app::FullScreenOptions &options ) {
    if (fullScreen) {
        //maybe SDL_WINDOW_FULLSCREEN
        SDL_SetWindowFullscreen (mWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        SDL_SetWindowFullscreen (mWindow, 0);
    }
}

Vec2i WindowImplLinux::getPos() const {
    int x, y;
    SDL_GetWindowPosition(mWindow, &x, &y);
    return Vec2i(x, y);
}

void WindowImplLinux::setPos( const Vec2i &pos ) {
    SDL_SetWindowPosition(mWindow, pos.x, pos.y);
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
    flags |= (SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    mWindow = SDL_CreateWindow(title.c_str(),
                               0,
                               0,
                               mWindowedSize.x,
                               mWindowedSize.y,
                               flags);
    if (mWindow == nullptr) {
        throw SDL_GetError();
    }

    mRenderer->setup(mAppImpl->getApp(), mWindow, sharedRenderer);
}


void WindowImplLinux::show() {
    SDL_ShowWindow(mWindow);
}

void WindowImplLinux::hide() {
    SDL_HideWindow(mWindow);
}

void WindowImplLinux::privateClose() {
    //mRenderer->kill();

    SDL_DestroyWindow (mWindow);
    mWindow = nullptr;
}

void WindowImplLinux::close() {
    getAppImpl()->closeWindow(this);
}

Vec2i WindowImplLinux::getSize() const {
    return Vec2i(mWindowWidth, mWindowHeight);
}

void* WindowImplLinux::getNative() {
    return mWindow;
}

const std::vector<TouchEvent::Touch>& WindowImplLinux::getActiveTouches() const {
    log;
}

void WindowImplLinux::setTitle( const std::string &title ) {
    SDL_SetWindowTitle(mWindow, title.c_str());
}

std::string	WindowImplLinux::getTitle() const {
    return SDL_GetWindowTitle(mWindow);
}

bool WindowImplLinux::isHidden() const {
    return SDL_GetWindowFlags(mWindow) & SDL_WINDOW_HIDDEN;
}

void WindowImplLinux::setSize( const Vec2i &size ) {
    SDL_SetWindowSize(mWindow, size.x, size.y);
}

DisplayRef	WindowImplLinux::getDisplay() const {
    return mDisplay;
}

void WindowImplLinux::draw() {
    mAppImpl->setWindow( mWindowRef );
	mRenderer->startDraw();
	mWindowRef->emitDraw();
	mRenderer->finishDraw();
}

void WindowImplLinux::redraw() {
    draw();
    //::SDL_GL_SwapWindow(mWindow);
}

}}
