//-*-c++-*-
#ifndef APPIMPLLINUX_H
#define APPIMPLLINUX_H

namespace cinder { namespace app {
        
class WindowImplLinux {
public:
    WindowImplMsw( const Window::Format &format, RendererRef sharedRenderer, AppImplMsw *appImpl );
    WindowImplMsw( HWND hwnd, RendererRef renderer, RendererRef sharedRenderer, AppImplMsw *appImpl );
    virtual ~WindowImplMsw() {}
    
    virtual bool		isFullScreen() { return mFullScreen; }
    virtual void		setFullScreen( bool fullScreen, const app::FullScreenOptions &options );
    virtual Vec2i		getSize() const { return Vec2i( mWindowWidth, mWindowHeight ); }
    virtual void		setSize( const Vec2i &size );
    virtual Vec2i		getPos() const { return mWindowOffset; }
    virtual void		setPos( const Vec2i &pos );
    virtual void		close();
    virtual std::string	getTitle() const;
    virtual void		setTitle( const std::string &title );
    virtual void		hide();
    virtual void		show();
    virtual bool		isHidden() const;
    virtual DisplayRef	getDisplay() const { return mDisplay; }
    virtual RendererRef	getRenderer() const { return mRenderer; }
    virtual const std::vector<TouchEvent::Touch>&	getActiveTouches() const { return mActiveTouches; }
    virtual void*		getNative() { return mWnd; }
    
    void			enableMultiTouch();
    bool			isBorderless() const { return mBorderless; }
    void			setBorderless( bool borderless );
    bool			isAlwaysOnTop() const { return mAlwaysOnTop; }
    void			setAlwaysOnTop( bool alwaysOnTop );
    
    AppImplMsw*				getAppImpl() { return mAppImpl; }
    WindowRef				getWindow() { return mWindowRef; }
    virtual void			keyDown( const KeyEvent &event );
    virtual void			draw();
    virtual void			redraw();
    virtual void			resize();
    
    void			privateClose();
};

}}

#endif //APPIMPLLINUX_H
