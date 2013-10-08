//-*-c++-*-
#ifndef APPIMPLLINUX_H
#define APPIMPLLINUX_H

#include "AppBasic.h"

namespace cinder { namespace app {

class AppImplLinux {
 public:
	AppImplLinux( class App *aApp );
	virtual ~AppImplLinux();
	
	class App*		getApp() { return mApp; }

    float			getFrameRate() const { return mFrameRate; }
	virtual float	setFrameRate( float aFrameRate ) { return -1.0f; }
	virtual void	quit() = 0;

    virtual WindowRef	getWindow() const { return mActiveWindow; }
    void				setWindow( WindowRef window ) { mActiveWindow = window; }
	
	static void	hideCursor() {}
	static void	showCursor() {}
	
	static Buffer	loadResource( int id, const std::string &type );
	
	static fs::path		getAppPath() {assert(0); return fs::path();}
	static fs::path		getOpenFilePath( const fs::path &initialPath, std::vector<std::string> extensions );
	static fs::path		getSaveFilePath( const fs::path &initialPath, std::vector<std::string> extensions );
	static fs::path		getFolderPath( const fs::path &initialPath );
protected:
    
    
protected:
    App* mApp;
    float					mFrameRate;
	WindowRef				mActiveWindow;
	bool					mSetupHasBeenCalled;
    bool					mFrameRateEnabled;
};
        
class WindowImplLinux {
public:
    WindowImplLinux( const Window::Format &format, RendererRef sharedRenderer, AppImplLinux *appImpl );
    WindowImplLinux( RendererRef renderer, RendererRef sharedRenderer, AppImplLinux *appImpl );
    virtual ~WindowImplLinux();
    
    virtual bool		isFullScreen() {assert(0); return false;}
    virtual void		setFullScreen( bool fullScreen, const app::FullScreenOptions &options ) {assert(0);}
    virtual Vec2i		getSize() const;
    virtual void		setSize( const Vec2i &size );
    virtual Vec2i		getPos() const {assert(0);}
    virtual void		setPos( const Vec2i &pos ) {assert(0);}
    virtual void		close();
    virtual std::string	getTitle() const {assert(0);}
    virtual void		setTitle( const std::string &title );
    virtual void		hide() {assert(0);}
    virtual void		show();
    virtual bool		isHidden() const;
    virtual DisplayRef	getDisplay() const;
    virtual RendererRef	getRenderer() const { return mRenderer; }
    virtual const std::vector<TouchEvent::Touch>&	getActiveTouches() const;
    virtual void*		getNative();
    
    void			enableMultiTouch();
    bool			isBorderless() const {return mBorderless;}
    void			setBorderless( bool borderless ) {assert(0);}
    bool			isAlwaysOnTop() const {return mAlwaysOnTop;}
    void			setAlwaysOnTop( bool alwaysOnTop ) {assert(0);}
    
    AppImplLinux*				getAppImpl();
    WindowRef				getWindow() { return mWindowRef; }
    virtual void			keyDown( const KeyEvent &event ) {assert(0);}
    virtual void			draw() {assert(0);}
    virtual void			redraw() {log;}
    virtual void			resize() {
        mAppImpl->setWindow( mWindowRef );
        mWindowRef->emitResize();
    }
    
    void			privateClose();

protected:
    void createWindow( const Vec2i &windowSize, const std::string &title, DisplayRef display, RendererRef sharedRenderer );
protected:
    AppImplLinux            *mAppImpl;
	WindowRef				mWindowRef;
  	//HWND					mWnd;
	//HDC						mDC;
	//DWORD					mWindowStyle, mWindowExStyle;
	Vec2i					mWindowOffset;
	bool					mHidden;
	int						mWindowWidth, mWindowHeight;
	bool					mFullScreen, mBorderless, mAlwaysOnTop, mResizable;
	Vec2i					mWindowedPos, mWindowedSize;
	DisplayRef				mDisplay;
	RendererRef				mRenderer;
	//std::map<DWORD,Vec2f>			mMultiTouchPrev;
	//std::vector<TouchEvent::Touch>	mActiveTouches;
	bool					mIsDragging;
    friend class AppImplLinuxBasic;
};

}}

#endif //APPIMPLLINUX_H
