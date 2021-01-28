#include <irrlicht.h>
#include <iostream>

#include "Flying_saucer.hpp"
#include "RocketLauncher.hpp"
#include "Wave.hpp"
#include "Terrain.hpp"
#include "Flak.hpp"
#include <list>
#include "Loader.cpp"
#include "Gui.hpp"
#include "MyEventReceiver.cpp"
#include <irrKlang.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace irrklang;
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
#endif





int main()
{

    // Initialisation
    int score = 0;
    irr::SIrrlichtCreationParameters params;
    params.DriverType=EDT_OPENGL;
    params.WindowSize=core::dimension2d<u32>(1920, 1080);
    params.Fullscreen = true;
    IrrlichtDevice* device = createDeviceEx(params);
    ISoundEngine* soundEngine = createIrrKlangDevice();
    soundEngine->play2D("new_data/sound/intro_music.ogg", false);

    if (!device)
        return 1;
    device->setWindowCaption(L"INCOMING 2021");
    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    gui::IGUIEnvironment* env = device->getGUIEnvironment();
    driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

    Gui* gui = new Gui(driver,smgr,env,device,score);
    gui->loadingScreen(); 


  
    core::vector3d<f32> posTurret(8531,695,8517);
    core::vector3d<f32> posRocketLauncher(8484,505,7593);

    scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0,100.0f,0.0f,-1,0,0,false,0.0f,false,true); 
    core::vector3d<f32> rotaCamBase(352,224,0);
    camera->setPosition(core::vector3d<f32>(posTurret.X+20,posTurret.Y+20,posTurret.Z+20));
    camera->setRotation(rotaCamBase);
    camera->setFarValue(20000.0f);


    // disable mouse cursor
    device->getCursorControl()->setVisible(false);
    
    
    float scale_factor = 0.3f;

    // add terrain scene node
    Terrain terrainSetUp = Terrain(smgr,driver,scale_factor,camera,device);


    // Create battleship;
    core::vector3d<f32> newPosition(2700*1+100,1000,2600*1+1000);
    core::vector3d<f32> destination(2700*6+300,1500,2600*6+1000);
    float vitesse = 0.4f;
    uint numberShips = 20;
    Wave wave1 = Wave(smgr,driver,"line", numberShips, newPosition, destination, vitesse,device,gui);
    int lastFPS = -1;

// Iniatialise Turret
    Flak flak1 = Flak(posTurret,smgr,driver,device,terrainSetUp.getSelectorGround(),soundEngine);
    RocketLauncher rl = RocketLauncher(posRocketLauncher,smgr,driver,device);
    //rl.getNode()->setRotation()


// create event receiver
    MyEventReceiver receiver(terrainSetUp.getTerrainGround(), &flak1, camera, &rl, device);
    device->setEventReceiver(&receiver);

    gui->stopLoadingScreen();
    gui->setHUD();
    gui->displayScore();

// Set Timer to 0 before loading
    device->getTimer()->setTime(0);
    

soundEngine->stopAllSounds();
soundEngine->play2D("new_data/sound/ingame_music.ogg", true);
while(device->run())
    if (device->isWindowActive())
    {
        flak1.updateParticleEmitter();
        flak1.updateShell();
        flak1.updateCollisionFlak();
        rl.updateParticleEmitter();

      
        driver->beginScene(true, true, video::SColor(255, 100, 101, 140));
        smgr->drawAll();
        env->drawAll();
        driver->endScene();



        // display frames per second in window title
        int fps = driver->getFPS();
        core::vector3df v(camera->getAbsolutePosition());
        //printf("camPos XYZ = %f, %f, %f\n", v.X, v.Y, v.Z);
        core::vector3df r(camera->getRotation());
        //printf("CamRota XYZ = %f, %f, %f\n", r.X, r.Y, r.Z);

        if (wave1.GetFormation().size() > 0) {
            for (auto x : wave1.GetFormation())
                    {
                        if(flak1.updateCollisionShell(x.second->getNode())){
                            
                            x.second->getHit();
                        }
                        x.second->updateParticleEmitter();
                    }
        }
        


        if (lastFPS != fps)
        {
            core::stringw str = L"Terrain Renderer - Irrlicht Engine [";
            str += driver->getName();
            str += "] FPS:";
            str += fps;
            // Also print terrain height of current camera position
            // We can use camera position because terrain is located at coordinate origin
            str += " Height: ";
            str += terrainSetUp.getTerrainGround()->getHeight(camera->getAbsolutePosition().X,
                    camera->getAbsolutePosition().Z);

            device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }
        
    }

    device->drop();
    
    return 0;
}