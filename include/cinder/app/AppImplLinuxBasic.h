//-*-c++-*-
#ifndef APPIMPLLINUXBASIC_H
#define APPIMPLLINUXBASIC_H

#include "AppImplLinux.h"


namespace cinder { namespace app {

        
class AppImplLinuxBasic : public AppImplLinux {
public:
    AppImplLinuxBasic(cinder::app::AppBasic* const app) : AppImplLinux(app) {}
//    AppImplLinuxBasic() {}
    virtual void run() {assert(0);}
    virtual void	quit() {assert(0);}
};

}}
            

#endif //APPIMPLLINUXBASIC_H
