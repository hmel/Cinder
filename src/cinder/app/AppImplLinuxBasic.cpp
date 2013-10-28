#include <SDL2/SDL.h>
//#include <SDL2/SDL_events.h>

#include "cinder/app/App.h"
#include "cinder/app/AppImplLinuxBasic.h"


#define log std::cout << __PRETTY_FUNCTION__ << std::endl;


namespace cinder { namespace app {

void AppImplLinuxBasic::run()
{
    mFrameRate = mApp->getSettings().getFrameRate();
	mFrameRateEnabled = mApp->getSettings().isFrameRateEnabled();
    
	auto formats = mApp->getSettings().getWindowFormats();
	if( formats.empty() )
		formats.push_back( mApp->getSettings().getDefaultWindowFormat() );
	for( auto format = formats.begin(); format != formats.end(); ++format ) {
		if( ! format->isTitleSpecified() )
			format->setTitle( mApp->getSettings().getTitle() );
		createWindow( *format );
	}

	mApp->privateSetup__();
	mSetupHasBeenCalled = true;
	for( auto windowIt = mWindows.begin(); windowIt != mWindows.end(); ++windowIt )
		(*windowIt)->resize();

	// initialize our next frame time
	mNextFrameTime = getElapsedSeconds();

	// inner loop
	while( ! mShouldQuit ) {
		// update and draw
		mApp->privateUpdate__();
		for( auto windowIt = mWindows.begin(); windowIt != mWindows.end(); ++windowIt )
			(*windowIt)->redraw();

		// get current time in seconds
		double currentSeconds = mApp->getElapsedSeconds();

		// calculate time per frame in seconds
		double secondsPerFrame = 1.0 / mFrameRate;

		// determine if application was frozen for a while and adjust
		// next frame time
        double elapsedSeconds = currentSeconds - mNextFrameTime;
		if( elapsedSeconds > 1.0 ) {
			int numSkipFrames = (int)(elapsedSeconds / secondsPerFrame);
			mNextFrameTime += (numSkipFrames * secondsPerFrame);
		}

        // determine when next frame should be drawn
		mNextFrameTime += secondsPerFrame;

        // sleep and process messages until next frame
		if( ( mFrameRateEnabled ) && ( mNextFrameTime > currentSeconds ) )
			sleep(mNextFrameTime - currentSeconds);
		else {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                dispatchEvent(event);
            }
		}
	}

//	killWindow( mFullScreen );
	mApp->emitShutdown();
	delete mApp;
}

void AppImplLinuxBasic::sleep( double seconds ) {
    //TODO @face Update timeout on each iteration
    SDL_Event event;
    int timeout = seconds * 1000; //to milliseconds
    while (SDL_WaitEventTimeout(&event, timeout)) {
        dispatchEvent(event);
    }
}

void AppImplLinuxBasic::closeWindow (class WindowImplLinux* windowImpl) {
    auto winIt = find( mWindows.begin(), mWindows.end(), windowImpl );
	if( winIt != mWindows.end() ) {
		windowImpl->getWindow()->emitClose();
		windowImpl->privateClose();
		delete windowImpl; // this corresponds to winIt
		mWindows.erase( winIt );
	}
    
	if( mWindows.empty() && mApp->getSettings().isQuitOnLastWindowCloseEnabled() )
		mShouldQuit = true;
}

/*
KeyEvent AppImplLinuxBasic::translateKey(SDL_Event& event) {
    assert( (event.type == SDL_KEYDOWN) || (event.type == SDL_KEYUP) );
    
    
}
*/

void AppImplLinuxBasic::dispatchEvent(SDL_Event& event) {

    switch (event.type)
    {
    case SDL_DOLLARGESTURE:
        break;
    case SDL_DROPFILE:
        break;
    case SDL_FINGERMOTION:
        break;
    case SDL_FINGERDOWN:
        break;
    case SDL_FINGERUP:
        break;
    case SDL_KEYDOWN:
    {
        /*
        KeyEvent event = translateKey(event);
        window = findWindow(event.windowID);
        window->emitKeyDown( &event );
        */
        break;
    }
    case SDL_KEYUP:
    {
        /*
        KeyEvent event = translateKey(event);
        window = findWindow(event.windowID);
        window->emitKeyUp( &event );
        */
        break;
    }
    case SDL_JOYAXISMOTION:
        break;
    case SDL_JOYBALLMOTION:
        break;
    case SDL_JOYHATMOTION:
        break;
    case SDL_JOYBUTTONDOWN:
        break;
    case SDL_JOYBUTTONUP:
        break;
    case SDL_MOUSEMOTION:
    {
        //SDL_Window* window = SDL_GetWindowFromID(event.windowID);
        //std::find_if (mWindows.begin (), mWindows.end(),
        //[](SDL_window
        
//        if (window) {
        SDL_MouseMotionEvent* mme = (SDL_MouseMotionEvent*)&event;
        WindowRef window ((*mWindows.begin())->mWindowRef);
        MouseEvent e (window, MouseEvent::LEFT_DOWN, mme->x, mme->y, 0, 0.0, 0);
        ///getWindow()->emitMouseMove(&e);
        getWindow()->emitMouseDrag(&e);
        break;
    }
    case SDL_MOUSEBUTTONDOWN:
        break;
    case SDL_MOUSEBUTTONUP:
        break;
    case SDL_MOUSEWHEEL:
        break;
    case SDL_MULTIGESTURE:
        break;
    case SDL_QUIT:
        mShouldQuit = true;
        break;
    case SDL_SYSWMEVENT:
        break;
    case SDL_TEXTEDITING:
        break;
    case SDL_TEXTINPUT:
        break;
    case SDL_USEREVENT:
        break;
    case SDL_WINDOWEVENT:
        break;
    }
}

WindowRef AppImplLinuxBasic::getWindowIndex( size_t index ) {
    if( index >= mWindows.size() )
		return cinder::app::WindowRef();
	
	auto iter = mWindows.begin();
	std::advance( iter, index );
	return (*iter)->mWindowRef;
}

void AppImplLinuxBasic::quit() {
    mShouldQuit = true;
}

WindowRef AppImplLinuxBasic::createWindow( Window::Format format ) {
    log;
    if( ! format.getRenderer() )
		format.setRenderer( mApp->getDefaultRenderer()->clone() );
    
	mWindows.push_back( new WindowImplLinuxBasic( format, mApp->findSharedRenderer( format.getRenderer() ), this ) );
    
	// emit initial resize if we have fired setup
	if( mSetupHasBeenCalled )
		mWindows.back()->getWindow()->emitResize();

	return mWindows.back()->getWindow();


}
    

} } //cinder::app
