//-*-c++-*-
#ifndef APPIMPLLINUXRENDERERGL_H
#define APPIMPLLINUXRENDERERGL_H

#include <SDL2/SDL.h>

#include "cinder/Camera.h"

namespace cinder {
namespace app {
    
class AppImplLinuxRendererGl {

public:
    AppImplLinuxRendererGl(App* app, RendererGl* aRenderer) : mApp(app), mRenderer(aRenderer) {        
    }

    ~AppImplLinuxRendererGl() {
        SDL_GL_DeleteContext(mContext);
    }
    
    void makeCurrentContext () {
        SDL_GL_MakeCurrent(mWindow, mContext);
        //glClearColor( 1.0f, 0.0f, 0.0f, 1.0f);
        //glClear (GL_COLOR_BUFFER_BIT);
        //SDL_GL_SwapWindow(mWindow);
    }

    void swapBuffers() const {
        //glClearColor( 0.0f, 1.0f, 0.0f, 0.0f);
        //glClear (GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(mWindow);
    }

    void initialize(SDL_Window* window, RendererRef renderer) {
        mWindow = window;
        //mRenderer = renderer;
        mContext = SDL_GL_CreateContext(mWindow);
    }

    void defaultResize () {
        int width, height;
        SDL_GetWindowSize(mWindow, &width, &height);

        glViewport(0, 0, width, height);
        cinder::CameraPersp cam( width, height, 60.0f );
        
        glMatrixMode( GL_PROJECTION );
        glLoadMatrixf( cam.getProjectionMatrix().m );
        
        glMatrixMode( GL_MODELVIEW );
        glLoadMatrixf( cam.getModelViewMatrix().m );
        glScalef( 1.0f, -1.0f, 1.0f );           // invert Y axis so increasing Y goes down.
        glTranslatef( 0.0f, (float)-height, 0.0f );       // shift origin up to upper-left corner.
    }

    void startDraw() {
    }

    void finishDraw() {
    }



private:
    App* mApp;
    RendererRef mRenderer;
    SDL_Window* mWindow;
    SDL_GLContext mContext;
};

} } //cinder::app

#endif //APPIMPLLINUXRENDERERGL_H
