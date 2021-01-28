#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Battleship {
    public :
        Battleship();
        Battleship(core::vector3df& pos, ISceneManager* smgr,IVideoDriver* driver,IrrlichtDevice* device, uint typeBattleship);
        const core::vector3df getPosition() const;
        IAnimatedMeshSceneNode* getNode();
        void setPosition(core::vector3df& pos);
        void initialiseObject(uint typeBattleship);
        void loadSubmarine();
        void loadKingClassShip();
        void loadMotherShip();

    private:
        core::vector3df position;
        ISceneManager* smgr;
        IAnimatedMeshSceneNode* shipNode;
        IVideoDriver* driver;
        IrrlichtDevice* device;

        

};
#endif