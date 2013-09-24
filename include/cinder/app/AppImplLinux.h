//-*-c++-*-
#ifndef APPIMPLLINUX_H
#define APPIMPLLINUX_H

#include "AppBasic.h"

namespace cinder { namespace app {

class AppImplLinux {
 public:
	AppImplLinux( class App *aApp );
	virtual ~AppImplLinux();
	
	class App*		getApp() { assert(0);return nullptr; }

    float			getFrameRate() const { assert(0); return 0; }
	virtual float	setFrameRate( float aFrameRate ) { assert(0);return -1.0f; }
	virtual void	quit() = 0;

    virtual WindowRef	getWindow() const { assert(0);return WindowRef(); }
    void				setWindow( WindowRef window ) { assert(0); }
	
	static void	hideCursor();
	static void	showCursor();
	
	static Buffer	loadResource( int id, const std::string &type );
	
	static fs::path		getAppPath();	
	static fs::path		getOpenFilePath( const fs::path &initialPath, std::vector<std::string> extensions );
	static fs::path		getSaveFilePath( const fs::path &initialPath, std::vector<std::string> extensions );
	static fs::path		getFolderPath( const fs::path &initialPath );
protected:
    App* mApp;
};
        
class WindowImplLinux {
public:
    WindowImplLinux( const Window::Format &format, RendererRef sharedRenderer, AppImplLinux *appImpl );
    WindowImplLinux( RendererRef renderer, RendererRef sharedRenderer, AppImplLinux *appImpl );
    virtual ~WindowImplLinux() {}
    
    virtual bool		isFullScreen();
    virtual void		setFullScreen( bool fullScreen, const app::FullScreenOptions &options );
    virtual Vec2i		getSize() const;
    virtual void		setSize( const Vec2i &size );
    virtual Vec2i		getPos() const;
    virtual void		setPos( const Vec2i &pos );
    virtual void		close();
    virtual std::string	getTitle() const;
    virtual void		setTitle( const std::string &title );
    virtual void		hide();
    virtual void		show();
    virtual bool		isHidden() const;
    virtual DisplayRef	getDisplay() const;
    virtual RendererRef	getRenderer() const;
    virtual const std::vector<TouchEvent::Touch>&	getActiveTouches() const;
    virtual void*		getNative();
    
    void			enableMultiTouch();
    bool			isBorderless() const;
    void			setBorderless( bool borderless );
    bool			isAlwaysOnTop() const;
    void			setAlwaysOnTop( bool alwaysOnTop );
    
    AppImplLinux*				getAppImpl();
    WindowRef				getWindow();
    virtual void			keyDown( const KeyEvent &event );
    virtual void			draw();
    virtual void			redraw();
    virtual void			resize();
    
    void			privateClose();
};

}}

#endif //APPIMPLLINUX_H
