#ifndef ROCKET_H
#define ROCKET_H
#include <irrlicht.h>
#include <ostream>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Rocket {
    public :
        Rocket();
        Rocket(core::vector3df& pos, ISceneManager* smgr,IVideoDriver* driver);
        const core::vector3df getPosition() const;
        IAnimatedMeshSceneNode* getNode();
        void setPosition(core::vector3df& pos);
        void initialiseObject();
        void lockingTarget();
        void updateTrajectory();


    private:
        core::vector3df position;
        ISceneManager* smgr;
        IAnimatedMeshSceneNode* rocketNode;
        float scale_Rocket = 10.0f ;
        IVideoDriver* driver; 
        float timeSmokeParticles = 500;
        scene::IParticleSystemSceneNode* ps;


};
#endif