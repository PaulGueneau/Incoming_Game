#ifndef FLAK_H
#define FLAK_H
#include <irrlicht.h>
#include <ostream>
#include <random>
#include <map>
#include <iterator>
#include <irrKlang.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace irrklang;

class Flak {
    public :
        Flak();
        Flak(core::vector3df& pos, ISceneManager* smgr,IVideoDriver* driver,IrrlichtDevice* device, scene::ITriangleSelector* groudSelector,ISoundEngine* soundEngine);
        const core::vector3df getPosition() const;
        IAnimatedMeshSceneNode* getNode();
        void setPosition(core::vector3df& pos);
        void initialiseObject();
        void firing();
        void explosionCanon();
        void updateParticleEmitter();
        void explosionShell();
        float setMaximumDistanceShell();
        void updateShell();
        void createCollisionFlak();
        void updateCollisionFlak();
        bool updateCollisionShell(ISceneNode* flyingsaucer);
        void playSoundCanon();
        void playSoundExplosionShell();
        void playSoundReloadOnce();


    private:
        irr::u32 fireTime = 0;
        core::vector3df position;
        ISceneManager* smgr;
        IAnimatedMeshSceneNode* flakNode;
        ISceneNode* collisionFlakNode;
        ISceneNode* shellNode;
        float scale_canon = 10.0f;
        IVideoDriver* driver;
        float reloadTime = 700; 
        float timeFiringParticles = 300;
        irr::u32 timeShellSmokeParticles = 10000;
        scene::IParticleSystemSceneNode* ps_canon;
        std::map < irr::u32,scene::IParticleSystemSceneNode*> ps_shell; // key = temps ou debute l'explosion , car la fumée reste en l'air plusieurs secondes
        float maximumDistanceShellbeforeExplode = 3000.0f;
        IrrlichtDevice* device;
        bool canonActivatedFiring = false;
        bool canonAuthorizeToFire = true;
        bool shellInTravel = false;
        bool soundReloadOK = false;
        float shellDistanceExplode;
        std::default_random_engine generator;
        float shellSpeed = 6.0f;
        core::vector3df positionShell;
        scene::ITriangleSelector* groundSelector;
        ISoundEngine* soundEngine;


        float theta_deg_Camera;
        float psi_deg_Camera;
        float theta_deg_shellExplo;
        float psi_deg_shellExplo;

        

};
#endif