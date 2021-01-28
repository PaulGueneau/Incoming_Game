#include "Flak.hpp"
#include <iostream>
#include <math.h>       /* pow */
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace irrklang;

#define M_PI 3.14159265358979323846
Flak::Flak()  {
    this->position= core::vector3df(0,0,0);
}

Flak::Flak(core::vector3d<f32>& pos,ISceneManager* smgr,IVideoDriver* driver,IrrlichtDevice* device, scene::ITriangleSelector* groundSelector,ISoundEngine* soundEngine)  {
    this->driver = driver;
    this->position= pos;
    this->smgr = smgr;
    this->device = device;
    this->groundSelector = groundSelector;
    this->soundEngine = soundEngine;
    initialiseObject();
}

void Flak::setPosition(core::vector3df& pos){
    position = pos;
}

void Flak::playSoundCanon() {
    this->soundEngine->play2D("new_data/sound/gun1.wav", false);
}

void Flak::playSoundExplosionShell() {
    this->soundEngine->play2D("new_data/sound/EXPLODE1.wav", false);
}
void Flak::playSoundReloadOnce() {
    if (this->soundReloadOK) {
        this->soundEngine->play2D("new_data/sound/gun-reload-sound-effect.ogg", false);
        this->soundReloadOK = false;
    }
    
}
IAnimatedMeshSceneNode* Flak::getNode() {
    return this->flakNode;
}

void Flak::initialiseObject(){
    
    auto mesh = smgr->getMesh ( "new_data/turret/canon-origin.obj" );
    this->flakNode = smgr->addAnimatedMeshSceneNode(mesh);
    core::vector3d<f32> factorEscalate(scale_canon,scale_canon,scale_canon);    
    this->flakNode->setScale(factorEscalate);
    this->flakNode->setPosition(position);
    this->flakNode->setMaterialTexture(0,driver->getTexture("new_data/turret/metallic.jpeg"));
    this->flakNode->setMaterialFlag(EMF_LIGHTING,false);
    this->collisionFlakNode = smgr->addEmptySceneNode();
    this->shellNode = smgr->addSphereSceneNode(15);
    

    // TO DO BUG
    //this->createCollisionFlak();


}

void Flak::createCollisionFlak(){
    
    scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
        this->groundSelector, this->collisionFlakNode, core::vector3df(1,10,10),
        core::vector3df(0,0,0),
        core::vector3df(0,0,0));
    this->groundSelector->drop();
    this->collisionFlakNode->addAnimator(anim);
    anim->drop();
    this->flakNode->setParent(this->collisionFlakNode);
    this->flakNode->setVisible(true);
}

void Flak::firing() {
    if (canonAuthorizeToFire) {
        this->explosionCanon();
        this->canonAuthorizeToFire = false;
        this->shellDistanceExplode = setMaximumDistanceShell();
        this->soundReloadOK = true;
    }
}

void Flak::updateCollisionFlak() {
    core::vector3d<f32> cameraRota = this->smgr->getActiveCamera()->getRotation();
    float distanceMuzzleBarrel = 140.0f;
    this->psi_deg_Camera = -(cameraRota.Y + 90);
    this->theta_deg_Camera = cameraRota.X + 90;
    float x = distanceMuzzleBarrel * sin(this->theta_deg_Camera * M_PI/180.0f) * cos(this->psi_deg_Camera * M_PI/180.0f);
    float z = distanceMuzzleBarrel * sin(this->theta_deg_Camera * M_PI/180.0f) * sin(this->psi_deg_Camera * M_PI/180.0f);
    float y = distanceMuzzleBarrel * cos(this->theta_deg_Camera * M_PI/180.0f);
    core::vector3d<f32> posNode(this->position.X - x,this->position.Y + y,this->position.Z - z);
    this->collisionFlakNode->setPosition(posNode);
}

float Flak::setMaximumDistanceShell() {
    float res;
    std::mt19937 gen(this->generator()); 
    std::normal_distribution<float> d(this->maximumDistanceShellbeforeExplode, this->maximumDistanceShellbeforeExplode/10.f); 
    // get random number with normal distribution using gen as random source
    res = d(gen); 
    return res;
}


void Flak::updateShell(){
    irr::u32 tps = this->device->getTimer()->getTime();   


    if (this->shellInTravel) {
    
        float deltaTime = tps - this->fireTime;
        if (deltaTime > this->shellDistanceExplode/this->shellSpeed ) {
            this->explosionShell();
            playSoundExplosionShell();
            this->shellInTravel = false;
            return;
        }
        else {

            float distance = deltaTime * this->shellSpeed;
            float x = distance * sin(this->theta_deg_shellExplo * M_PI/180.0f) * cos(this->psi_deg_shellExplo * M_PI/180.0f);
            float z = distance * sin(this->theta_deg_shellExplo * M_PI/180.0f) * sin(this->psi_deg_shellExplo * M_PI/180.0f);
            float y = distance * cos(this->theta_deg_shellExplo * M_PI/180.0f);
            core::vector3d<f32> posShellUpdate(this->positionShell.X - x,this->positionShell.Y + y,this->positionShell.Z - z);
            this->positionShell = posShellUpdate;
            this->shellNode->setPosition(this->positionShell);
        }

        
    }
    if (this->ps_shell.size() > 0) {
        for (auto x : this->ps_shell)
        {
            if(tps- x.first > this->timeShellSmokeParticles) {
                x.second->setEmitter(0);
            }
        }
    }
   
}


void Flak::explosionShell() {


        scene::IParticleSystemSceneNode* ps;
        float x = this->shellDistanceExplode * sin(this->theta_deg_shellExplo * M_PI/180.0f) * cos(this->psi_deg_shellExplo * M_PI/180.0f);
        float z = this->shellDistanceExplode * sin(this->theta_deg_shellExplo * M_PI/180.0f) * sin(this->psi_deg_shellExplo * M_PI/180.0f);
        float y = this->shellDistanceExplode * cos(this->theta_deg_shellExplo * M_PI/180.0f);
        core::vector3d<f32> posFire(this->position.X - x,this->position.Y + y,this->position.Z - z);

        ps = smgr->addParticleSystemSceneNode(false);

        scene::IParticleEmitter* em = ps->createBoxEmitter(
            irr::core::aabbox3d<irr::f32>(-2,0,-2,2,1,2),
            irr::core::vector3df(0.0f,0.01f,0.0f),50,150,
            SColor(0,0,0,0),
            SColor(0,128,128,128),400,5000,180,
            irr::core::dimension2df(80.f,80.f),
            irr::core::dimension2df(120.f,120.f));


        ps->setEmitter(em); // this grabs the emitter
        em->drop(); // so we can drop it here without deleting it

        scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();

        ps->addAffector(paf); // same goes for the affector
        paf->drop();

        ps->setPosition(posFire);
        ps->setScale(core::vector3df(2,2,2));
        ps->setMaterialFlag(video::EMF_LIGHTING, false);
        ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        
        ps->setMaterialTexture(0, driver->getTexture("new_data/turret/smoke.png"));
        ps->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL );
        irr::u32 tpsAtExplosion = this->device->getTimer()->getTime();
        this->ps_shell.insert(std::make_pair(tpsAtExplosion,ps));
}


void Flak::updateParticleEmitter() {
    irr::u32 tps = this->device->getTimer()->getTime();
    if (this->canonActivatedFiring) {
        if (tps - this->fireTime > this->timeFiringParticles) {
            this->canonActivatedFiring = false;
            this->ps_canon->setEmitter(0); 
        }
    }
    if (tps - this->fireTime > this->reloadTime) {
        this->canonAuthorizeToFire = true;
        playSoundReloadOnce();
    }
}


void Flak::explosionCanon() {
    if (!canonActivatedFiring) {

        this->ps_canon = smgr->addParticleSystemSceneNode(false);

        scene::IParticleEmitter* em = this->ps_canon->createBoxEmitter(
            irr::core::aabbox3d<irr::f32>(-2,0,-2,2,1,2),
            irr::core::vector3df(0.f,0.06f,0.f),3500,3500,
            irr::video::SColor(0,255,255,255),
            irr::video::SColor(0,255,255,255),400,700,180,
            irr::core::dimension2df(5.f,5.f),
            irr::core::dimension2df(2.f,2.f));


        this->ps_canon->setEmitter(em); // this grabs the emitter
        em->drop(); // so we can drop it here without deleting it

        scene::IParticleAffector* paf = this->ps_canon->createFadeOutParticleAffector();

        this->ps_canon->addAffector(paf); // same goes for the affector
        paf->drop();
        core::vector3df posFire = this->collisionFlakNode->getAbsolutePosition() + core::vector3df(0,0,0);
        this->ps_canon->setPosition(posFire);
        this->ps_canon->setScale(core::vector3df(2,2,2));
        this->ps_canon->setMaterialFlag(video::EMF_LIGHTING, false);
        this->ps_canon->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        this->ps_canon->setMaterialTexture(0, driver->getTexture("irrlicht-1.8.4/media/fire.bmp"));
        this->ps_canon->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
        this->fireTime =this->device->getTimer()->getTime();
        this->canonActivatedFiring = true;
        this->shellInTravel = true;
        this->positionShell = this->collisionFlakNode->getAbsolutePosition();
        this->theta_deg_shellExplo = this->theta_deg_Camera;
        this->psi_deg_shellExplo = this->psi_deg_Camera;
        this->shellNode->setPosition(this->positionShell);
        this->playSoundCanon();

        
    }
}

bool Flak::updateCollisionShell(ISceneNode* one) {
   aabbox3d<f32> b1, b2;

   b1 = one->getBoundingBox ();
   b2 = this->shellNode->getBoundingBox ();

   one->getRelativeTransformation().transformBoxEx( b1 );
   this->shellNode->getRelativeTransformation().transformBoxEx( b2 );
   return b1.intersectsWithBox( b2 );
}