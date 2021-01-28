#include "Flying_saucer.hpp"
#include <iostream>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Flyingsaucer::Flyingsaucer()  {
    this->position= core::vector3df(0,0,0);
    this->vitesse=0.0f;
}

Flyingsaucer::Flyingsaucer(core::vector3d<f32>& pos,ISceneManager* smgr,IVideoDriver* driver,IrrlichtDevice* device,Gui* gui)  {
    this->driver = driver;
    this->position= pos;
    this->smgr = smgr;
    this->device = device;
    this->vitesse = 0.0f;
    this->gui =gui;
    initialiseObject();
}

void Flyingsaucer::setPosition(core::vector3df& pos){
    position = pos;
}

IAnimatedMeshSceneNode* Flyingsaucer::getNode() {
 return this->starShipNode;
}

const core::vector3df Flyingsaucer::getPosition() const {
    return position;
}

void Flyingsaucer::setVitesse(float vit){
    this->vitesse = vit;
}


void Flyingsaucer::setDestination(core::vector3df& destination){
    this->destination = destination;
}


void Flyingsaucer::launchAnimation() {
    float time = abs(position.getLength()-destination.getLength())/vitesse;
    this->anim = smgr->createFlyStraightAnimator(this->position,this->destination, time, true);
    this->starShipNode->addAnimator(this->anim);
    anim->drop();
}


void Flyingsaucer::deleteShip() {
    this->starShipNode->drop();
}

const float Flyingsaucer::getVitesse() const {
    return vitesse;
}

const core::vector3df Flyingsaucer::getDestination() const {
    return destination;
}

void Flyingsaucer::explosionStartship() {
    this->explosionStarship = smgr->addParticleSystemSceneNode(false);

    scene::IParticleEmitter* em = this->explosionStarship->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(-2,0,-2,2,1,2),
        irr::core::vector3df(0.f,0.5f,0.f),15000,30000,
        irr::video::SColor(0,255,255,255),
        irr::video::SColor(0,255,255,255),700,1500,180,
        irr::core::dimension2df(25.f,25.f),
        irr::core::dimension2df(25.f,25.f));


        this->explosionStarship->setEmitter(em); // this grabs the emitter
        em->drop(); // so we can drop it here without deleting it

        scene::IParticleAffector* paf = this->explosionStarship->createFadeOutParticleAffector();

        this->explosionStarship->addAffector(paf); // same goes for the affector
        paf->drop();
        core::vector3df posFire = this->starShipNode->getAbsolutePosition();
        this->explosionStarship->setPosition(posFire);
        this->explosionStarship->setScale(core::vector3df(2,2,2));
        this->explosionStarship->setMaterialFlag(video::EMF_LIGHTING, false);
        this->explosionStarship->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        this->explosionStarship->setMaterialTexture(0, driver->getTexture("irrlicht-1.8.4/media/fire.bmp"));
        this->explosionStarship->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
        this->explosionTime =this->device->getTimer()->getTime();
        //this->explosionStarship->setEmitter(0);

}

void Flyingsaucer::smokeStarship() {
    this->smokeFall = smgr->addParticleSystemSceneNode(false);
        scene::IParticleEmitter* em = this->smokeFall->createBoxEmitter(
            irr::core::aabbox3d<irr::f32>(-2,0,-2,2,1,2),
            irr::core::vector3df(0.0f,0.01f,0.0f),50,150,
            SColor(0,0,0,0),
            SColor(0,128,128,128),400,5000,180,
            irr::core::dimension2df(80.f,80.f),
            irr::core::dimension2df(120.f,120.f));

        this->smokeFall->setEmitter(em); // this grabs the emitter
        em->drop(); // so we can drop it here without deleting it

        scene::IParticleAffector* paf = this->smokeFall->createFadeOutParticleAffector();

        this->smokeFall->addAffector(paf); // same goes for the affector
        paf->drop();
        core::vector3df posFire = this->starShipNode->getAbsolutePosition();
        this->smokeFall->setPosition(posFire);
        this->smokeFall->setScale(core::vector3df(2,2,2));
        this->smokeFall->setMaterialFlag(video::EMF_LIGHTING, false);
        this->smokeFall->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        this->smokeFall->setMaterialTexture(0, driver->getTexture("new_data/turret/smoke.png"));
        this->smokeFall->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL );
        //this->explosionStarship->setEmitter(0);

}




void Flyingsaucer::getHit() {
    explosionStartship();
    smokeStarship();
    core::vector3d<f32> posHit = this->starShipNode->getAbsolutePosition();
    core::vector3d<f32> posHitDestination(posHit.X,0,posHit.Z);
    this->starShipNode->removeAnimator(this->anim);
    this->anim = smgr->createFlyStraightAnimator(posHit,posHitDestination, 10000, false);
    this->starShipNode->addAnimator(this->anim);
    core::vector3d<f32> rot(0,0,1.2f);
    ISceneNodeAnimator* rotaAnim=smgr->createRotationAnimator(rot);
    this->starShipNode->addAnimator(rotaAnim);
    this->starShipHit = true;
    this->gui->incrementScore();
    
}



void Flyingsaucer::updateParticleEmitter() {
    if (this->starShipHit) {
        irr::u32 tps = this->device->getTimer()->getTime();
        
        if (tps - this->explosionTime > 300) {
            this->explosionStarship->setEmitter(0); 
        }
        
        if (tps - this->explosionTime > 5000) {
            this->smokeFall->setEmitter(0); 
        } else {
            this->smokeFall->setPosition(this->starShipNode->getAbsolutePosition());
        }

    }
    

}

void Flyingsaucer::initialiseObject(){
    
    auto mesh = smgr->getMesh ("new_data/ufo/test.obj" );
    this->starShipNode = smgr->addAnimatedMeshSceneNode(mesh);
    core::vector3d<f32> factorEscalate(scale_ship,scale_ship,scale_ship);    
    this->starShipNode->setScale(factorEscalate);
    this->starShipNode->setMaterialTexture(0,driver->getTexture("new_data/ufo/ufo_diffuse.png"));

    this->starShipNode->setPosition(position);
    this->starShipNode->setMaterialFlag(EMF_LIGHTING,false);
    core::vector3d<f32> rotaShip(0,1.2f,0);
    scene::ISceneNodeAnimator* anim_vaisseau  = smgr->createRotationAnimator(rotaShip);
    this->starShipNode->addAnimator(anim_vaisseau);

}


