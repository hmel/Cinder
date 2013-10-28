//-*-c++-*-
#ifndef APPIMPLLINUXBASIC_H
#define APPIMPLLINUXBASIC_H

#include "AppImplLinux.h"

union SDL_Event;

namespace cinder { namespace app {

class WindowImplLinuxBasic;


class AppImplLinuxBasic : public AppImplLinux {
public:
    AppImplLinuxBasic(cinder::app::AppBasic* const app) : AppImplLinux(app),
                                                          mApp (app) {
        mShouldQuit = false;
    }
//    AppImplLinuxBasic() {}
    virtual void run();
    virtual void	quit();
    WindowRef createWindow( Window::Format format );
    virtual void closeWindow (class WindowImplLinux* window) override;
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
    void dispatchEvent(SDL_Event& event);
    void sleep( double seconds );
    WindowRef findWindow(Uint32 windowID);


private:
    class AppBasic	*mApp;
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
