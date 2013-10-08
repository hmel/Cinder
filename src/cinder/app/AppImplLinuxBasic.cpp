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

		// determine if application was frozen for a while and adjust next frame time
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
            /*
			MSG msg;
			while( ::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {
				::TranslateMessage( &msg );
				::DispatchMessage( &msg );
			}
            */
            log;
		}
	}

//	killWindow( mFullScreen );
	mApp->emitShutdown();
	delete mApp;
}

WindowRef AppImplLinuxBasic::getWindowIndex( size_t index ) {
    if( index >= mWindows.size() )
		return cinder::app::WindowRef();
	
	auto iter = mWindows.begin();
	std::advance( iter, index );
	return (*iter)->mWindowRef;
}

void AppImplLinuxBasic::quit() {
    log;
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
