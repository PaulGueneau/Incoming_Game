#include "Rocket.hpp"
#include <iostream>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Rocket::Rocket()  {
    this->position= core::vector3df(0,0,0);
}

Rocket::Rocket(core::vector3d<f32>& pos,ISceneManager* smgr,IVideoDriver* driver)  {
    this->driver = driver;
    this->position= pos;
    this->smgr = smgr;
    initialiseObject();
}

void Rocket::setPosition(core::vector3df& pos){
    position = pos;
}


IAnimatedMeshSceneNode* Rocket::getNode() {
    return this->rocketNode;
}

void Rocket::initialiseObject(){
    
    auto mesh = smgr->getMesh ( "new_data/rocket/MLRS_Rocket.obj" );
    rocketNode = smgr->addAnimatedMeshSceneNode(mesh);
    core::vector3d<f32> factorEscalate(scale_Rocket,scale_Rocket,scale_Rocket);    
    rocketNode->setScale(factorEscalate);
    rocketNode->setPosition(position);
    rocketNode->setMaterialTexture(0,driver->getTexture("new_data/rocket/MLRS_Rocket_MLRS_Rocket_Mat_BaseColor.png"));
    rocketNode->setMaterialFlag(EMF_LIGHTING,false);
    rocketNode->setRotation( core::vector3d<f32>(306+110,270,0));
}


void Rocket::lockingTarget(){
    
}

void Rocket::updateTrajectory() {

}

/*
void RocketLauncher::explosionCanon() {

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
    //em->drop(); // so we can drop it here without deleting it

    scene::IParticleAffector* paf = this->ps->createFadeOutParticleAffector();

    this->ps->addAffector(paf); // same goes for the affector
    //paf->drop();

    this->ps->setPosition(posFire);
    this->ps->setScale(core::vector3df(2,2,2));
    this->ps->setMaterialFlag(video::EMF_LIGHTING, false);
    this->ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    this->ps->setMaterialTexture(0, driver->getTexture("irrlicht-1.8.4/media/fire.bmp"));
    this->ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);


}*/