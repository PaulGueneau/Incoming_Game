#ifndef ROCKETLAUNCHER_H
#define ROCKETLAUNCHER_H
#include <irrlicht.h>
#include <ostream>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class RocketLauncher {
    public :
        RocketLauncher();
        RocketLauncher(core::vector3df& pos, ISceneManager* smgr,IVideoDriver* driver,IrrlichtDevice* device);
        const core::vector3df getPosition() const;
        IAnimatedMeshSceneNode* getNode();
        void setPosition(core::vector3df& pos);
        void initialiseObject();
        void  explosionCanon();
        void firing();
        void updateParticleEmitter();
        irr::u32 getTimeFiring();
        scene::IParticleSystemSceneNode* getParticuleSystem();
        bool getCanonActivated();
        void setCanonActivated(bool);

    private:
        irr::u32 fireTime = 0;
        core::vector3df position;
        ISceneManager* smgr;
        IAnimatedMeshSceneNode* rockerLauncherNode;
        float scale_launcher = 10.1f;
        IVideoDriver* driver;
        double reloadTime = 5000;
        double startTimeReload;
        double timeFiringParticles = 1000;
        scene::IParticleSystemSceneNode* ps;
        IrrlichtDevice* device;
        bool rocketActivated = false;
        bool rocketAuthorizeToFire = true;


};
#endif