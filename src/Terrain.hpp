#ifndef TERRAIN_H
#define TERRAIN_H
#include <irrlicht.h>
#include <ostream>
#include "Battleship.hpp"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Terrain {
    public :
        Terrain(ISceneManager* smgr,IVideoDriver* driver, float& scale_factor, scene::ICameraSceneNode* camera,IrrlichtDevice* device);
        void createTerrain();
        scene::ITerrainSceneNode* getTerrainGround();
        scene::ITriangleSelector* getSelectorGround();
        void createCollisionResponse();
        void setSkybox();
        scene::ISceneNode* getSkybox();
        scene::ISceneNode* getSkydome();
        void addWater();
        void addBattleships();

    private:
        ISceneManager* smgr;
        IVideoDriver* driver;
        float scale_factor;
        scene::ITerrainSceneNode* terrainGround;
        scene::ICameraSceneNode* camera;
        scene::ITriangleSelector* selectorGround;
        ISceneNode* skybox;
        ISceneNode* skydome;
        IrrlichtDevice* device;



};
#endif