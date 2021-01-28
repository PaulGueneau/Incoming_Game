#include <irrlicht.h>
#include <iostream>
#include "Flak.hpp"
#include "RocketLauncher.hpp"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif
// SOLUTION 6 PARTIE 1 (z pour lancer l'animation)



class MyEventReceiver : public IEventReceiver
{
public:

    MyEventReceiver(scene::ITerrainSceneNode* terrain, Flak* flak, scene::ICameraSceneNode* camera, RocketLauncher* rocket,IrrlichtDevice* device ) : Terrain(terrain), flak(flak), Camera(camera), rocketLauncher(rocket), device(device)
    {

    }

    bool OnEvent(const SEvent& event)
    {
        core::vector3df rotaCamera = Camera->getRotation();    
        core::vector3df posCamera = Camera->getAbsolutePosition();
        scene::ISceneNode* flakNode = flak->getNode(); 

        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT ) {
            core::vector3df rotaFlak = flakNode->getRotation();
            flakNode->setRotation(rotaCamera);
            //  << "you clicked screen coordinates: "<< std::endl;

            if (event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN) {
                flak->firing();
            }



        }

        // check if user presses the key 'W' or 'D'
        if (event.EventType == irr::EET_KEY_INPUT_EVENT )
        {
            switch (event.KeyInput.Key)
            {


                case irr::KEY_KEY_I: // switch wire frame mode
                    Camera->setPosition(core::vector3df(posCamera.X+dtheta,posCamera.Y,posCamera.Z));
                return true;

                case irr::KEY_KEY_K: // switch wire frame mode
                    Camera->setPosition(core::vector3df(posCamera.X-dtheta,posCamera.Y,posCamera.Z));
                return true;
                case irr::KEY_KEY_O: // switch wire frame mode
                    Camera->setPosition(core::vector3df(posCamera.X,posCamera.Y+dtheta,posCamera.Z));
                return true;
                case irr::KEY_KEY_L: // switch wire frame mode
                    Camera->setPosition(core::vector3df(posCamera.X,posCamera.Y-dtheta,posCamera.Z));
                return true;
                case irr::KEY_KEY_P: // switch wire frame mode
                    Camera->setPosition(core::vector3df(posCamera.X,posCamera.Y,posCamera.Z+dtheta));
                return true;
                case irr::KEY_KEY_M: // switch wire frame mode
                    Camera->setPosition(core::vector3df(posCamera.X,posCamera.Y,posCamera.Z-dtheta));
                return true;
                case irr::KEY_SPACE: // switch wire frame mode
                    flak->firing();
                return true;

                case irr::KEY_KEY_W: // switch wire frame mode
                    Terrain->setMaterialFlag(video::EMF_WIREFRAME,
                        !Terrain->getMaterial(0).Wireframe);
                    Terrain->setMaterialFlag(video::EMF_POINTCLOUD, false);
                    return true;
                    
                case irr::KEY_LSHIFT: // switch wire frame mode
                    rocketLauncher->firing();
                    return true;

                case irr::KEY_ESCAPE: // switch wire frame mode
                    this->device->closeDevice();   
                    return true;
                default:
                    break;
            }
        }

        return false;
    }

private:
    scene::ITerrainSceneNode* Terrain;
    Flak* flak;
    RocketLauncher* rocketLauncher;
    scene::ICameraSceneNode* Camera ;
    bool showBox;
    bool showDebug;
    float dtheta = 10.0f;
    IrrlichtDevice* device;
};