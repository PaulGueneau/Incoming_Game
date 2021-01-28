#ifndef FLYINGSAUCER_H
#define FLYINGSAUCER_H
#include <irrlicht.h>
#include "Gui.hpp"
#include <ostream>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Flyingsaucer {
    public :
        Flyingsaucer();
        Flyingsaucer(core::vector3df& pos, ISceneManager* smgr,IVideoDriver* driver,IrrlichtDevice* device,Gui* gui);
        const core::vector3df getPosition() const;
        void setPosition(core::vector3df& pos);
        const float getVitesse() const;
        void setVitesse(float vit);
        void initialiseObject();
        void deleteShip();
        void launchAnimation();
        void setDestination(core::vector3df& destination);
        const core::vector3df getDestination() const;
        const int getTest() const ;
        IAnimatedMeshSceneNode* getNode();
        void getHit();
        void explosionStartship();
        void smokeStarship();
        void updateParticleEmitter();


    private:
        core::vector3df position;
        float vitesse;
        core::vector3df destination;
        ISceneManager* smgr;
        IAnimatedMeshSceneNode* starShipNode;
        float scale_ship = 2.0f;
        IVideoDriver* driver;
        bool starShipHit = false;
        scene::ISceneNodeAnimator* anim;
        scene::IParticleSystemSceneNode* explosionStarship;
        scene::IParticleSystemSceneNode* smokeFall;
        irr::u32 explosionTime = 0;
        IrrlichtDevice* device;
        Gui* gui;


};
#endif