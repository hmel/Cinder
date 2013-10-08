//-*-c++-*-
#ifndef APPIMPLLINUXBASIC_H
#define APPIMPLLINUXBASIC_H

#include "AppImplLinux.h"

namespace cinder { namespace app {

class WindowImplLinuxBasic;

class AppImplLinuxBasic : public AppImplLinux {
public:
    AppImplLinuxBasic(cinder::app::AppBasic* const app) : AppImplLinux(app) {}
//    AppImplLinuxBasic() {}
    virtual void run();
    virtual void	quit();
    WindowRef createWindow( Window::Format format );
    WindowRef getWindowIndex( size_t index );
    bool isFrameRateEnabled() const {return mFrameRateEnabled;}
    void disableFrameRate() {
        mFrameRateEnabled = false;
    }
    size_t getNumWindows() const {
        return mWindows.size();
    }
    
    WindowRef getForegroundWindow() const {
        return mForegroundWindow;
    }


private:
    bool mFrameRateEnabled;
    double mNextFrameTime;
    bool mShouldQuit;
    WindowRef mForegroundWindow;
    
    std::list<class WindowImplLinuxBasic*>	mWindows;
};

class WindowImplLinuxBasic : public WindowImplLinux {

public:
    WindowImplLinuxBasic( const Window::Format &format, RendererRef sharedRenderer, AppImplLinuxBasic *appImpl )
		: WindowImplLinux( format, sharedRenderer, appImpl ), mAppImplBasic( appImpl ) {}

protected:
	AppImplLinuxBasic		*mAppImplBasic;
};

}}
            

#endif //APPIMPLLINUXBASIC_H
