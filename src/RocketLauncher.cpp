#include "RocketLauncher.hpp"
#include "Rocket.hpp"
#include <iostream>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

RocketLauncher::RocketLauncher()  {
    this->position= core::vector3df(0,0,0);
}

RocketLauncher::RocketLauncher(core::vector3d<f32>& pos,ISceneManager* smgr,IVideoDriver* driver,IrrlichtDevice* device)  {
    this->driver = driver;
    this->position= pos;
    this->smgr = smgr;
    this->device = device;
    initialiseObject();
}

void RocketLauncher::setPosition(core::vector3df& pos){
    position = pos;
}


IAnimatedMeshSceneNode* RocketLauncher::getNode() {
    return this->rockerLauncherNode;
}

void RocketLauncher::initialiseObject(){
    
    auto mesh = smgr->getMesh ( "new_data/rocketlauncher/PAC3.obj" );
    rockerLauncherNode = smgr->addAnimatedMeshSceneNode(mesh);
    core::vector3d<f32> factorEscalate(scale_launcher,scale_launcher,scale_launcher);    
    rockerLauncherNode->setScale(factorEscalate);
    rockerLauncherNode->setPosition(position);
    rockerLauncherNode->setMaterialTexture(0,driver->getTexture("new_data/rocketlauncher/pac_3_launcher_d.jpg"));
    rockerLauncherNode->setMaterialFlag(EMF_LIGHTING,false);

}

void RocketLauncher::firing(){
    if (this->rocketAuthorizeToFire) {
    this->rocketAuthorizeToFire = false;
    this->explosionCanon();
    std::cout << fireTime << std::endl;
    core::vector3d<f32> posFire(8536,595,7580);
    Rocket r1 = Rocket(posFire,this->smgr, this->driver);
    }


}
bool RocketLauncher::getCanonActivated(){
    return this->rocketActivated;
}

void RocketLauncher::setCanonActivated(bool canonAct) {
    this->rocketActivated = canonAct;
}
scene::IParticleSystemSceneNode* RocketLauncher::getParticuleSystem(){
    return this->ps;
}

void RocketLauncher::updateParticleEmitter() {
    irr::u32 tps = this->device->getTimer()->getTime();
    if (this->rocketActivated) {
        if (tps - this->fireTime > this->timeFiringParticles) {
                //this->ps->setEmitter(0);
                this->rocketActivated = false;
                 this->ps->setEmitter(0); 
        }
    }
    if (tps - this->fireTime > this->reloadTime) {
        this->rocketAuthorizeToFire = true;
    }
   
}

irr::u32 RocketLauncher::getTimeFiring() {
    return this->fireTime;

}
void RocketLauncher::explosionCanon() {
    if (!rocketActivated) {
            core::vector3d<f32> posFire(8539,595,7592);

            this->ps = smgr->addParticleSystemSceneNode(false);
            scene::IParticleEmitter* em = this->ps->createBoxEmitter(
                irr::core::aabbox3d<irr::f32>(-2,0,-2,2,1,2),
                irr::core::vector3df(0.f,0.06f,0.f),250,200,
                irr::video::SColor(0,255,255,255),
                irr::video::SColor(0,255,255,255),400,700,180,
                irr::core::dimension2df(5.f,5.f),
                irr::core::dimension2df(2.f,2.f));

            this->ps->setEmitter(em); // this grabs the emitter
            em->drop(); // so we can drop it here without deleting it

            scene::IParticleAffector* paf = this->ps->createFadeOutParticleAffector();

            this->ps->addAffector(paf); // same goes for the affector
            paf->drop();

            this->ps->setPosition(posFire);
            this->ps->setScale(core::vector3df(2,2,2));
            this->ps->setMaterialFlag(video::EMF_LIGHTING, false);
            this->ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
            this->ps->setMaterialTexture(0, driver->getTexture("irrlicht-1.8.4/media/fire.bmp"));
            this->ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

            this->fireTime =this->device->getTimer()->getTime();
            this->rocketActivated = true;
        } 
    }
