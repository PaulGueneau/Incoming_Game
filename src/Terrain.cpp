#include "Terrain.hpp"
#include <iostream>
#include "RealisticWater.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Terrain::Terrain(ISceneManager* smgr,IVideoDriver* driver, float& scale_factor, scene::ICameraSceneNode* camera,IrrlichtDevice* device)  {
    this->driver = driver;
    this->scale_factor = scale_factor;
    this->smgr = smgr;
    this->camera = camera;
    this->device = device;
    createTerrain();
    addWater();
}

void Terrain::createTerrain() {

    // add terrain scene node
    this->terrainGround = smgr->addTerrainSceneNode(
        "new_data/terrain/heightmap_2.png",
        0,                  // parent node
        -1,                 // node id
        core::vector3df(0.f, 0.f, 0.f),     // position
        core::vector3df(0.f, 0.f, 0.f),     // rotation
        core::vector3df(40.0f, 25.0f, 40.0f)*scale_factor,  // scale
        video::SColor ( 255, 255, 255, 255 ),   // vertexColor
        5,                  // maxLOD
        scene::ETPS_17,             // patchSize
        4                   // smoothFactor
        );

    this->terrainGround->setMaterialFlag(video::EMF_LIGHTING, false);

    this->terrainGround->setMaterialTexture(0,
            driver->getTexture("new_data/terrain/rock2.jpeg"));
    this->terrainGround->setMaterialTexture(1,
            driver->getTexture("new_data/terrain/rock1.jpeg"));
    
    this->terrainGround->setMaterialType(video::EMT_DETAIL_MAP);

    this->terrainGround->scaleTexture(0.2f, 1.2f);


      // create triangle selector for the terrain 
    this->selectorGround = smgr->createTerrainTriangleSelector(this->terrainGround, 0);
    this->terrainGround->setTriangleSelector( this->selectorGround);
    //this->terrainGround->setMaterialFlag(EMF_FOG_ENABLE , true);

    createCollisionResponse();
    setSkybox();
    addBattleships();
}


 void Terrain::createCollisionResponse() {
    // create collision response animator and attach it to the camera
    scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
        this->selectorGround, this->camera, core::vector3df(60,100,60),
        core::vector3df(0,0,0),
        core::vector3df(0,50,0));
    this->selectorGround->drop();
    camera->addAnimator(anim);
    anim->drop();
    scene::CDynamicMeshBuffer* buffer = new scene::CDynamicMeshBuffer(video::EVT_2TCOORDS, video::EIT_32BIT);
    terrainGround->getMeshBufferForLOD(*buffer, 0);
    video::S3DVertex2TCoords* data = (video::S3DVertex2TCoords*)buffer->getVertexBuffer().getData();
    // Work on data or get the IndexBuffer with a similar call.
    buffer->drop(); // When done drop the buffer again.

 }

void Terrain::setSkybox() {

    // create skybox and skydome
    driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);
    this->skydome=smgr->addSkyDomeSceneNode(driver->getTexture("new_data/terrain/skydome.jpg"),16,8,0.95f,2.0f);

    driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

    this->skydome->setVisible(true);
}





void Terrain::addWater() {

  
    scene::ISceneNode* node = 0;
    scene::IAnimatedMesh* mesh =
    smgr->addHillPlaneMesh("floor",
    core::dimension2d<f32>(4000,4000),
    core::dimension2d<u32>(10,10), 0, 0,
    core::dimension2d<f32>(0,0),
    core::dimension2d<f32>(10,10));


    node = smgr->addWaterSurfaceSceneNode(mesh->getMesh(0), 75.0f, 1000.0f, 400.0f);
    core::vector3df pos = this->terrainGround->getAbsolutePosition();
    irr::core::aabbox3df bbox = this->terrainGround->getBoundingBox();
    pos = bbox.getCenter();
    std::cout << (float)pos.X << std::endl;
    node->setPosition(core::vector3df(pos.X,255,pos.Z));

    node->setMaterialTexture(0, driver->getTexture("new_data/terrain/sand.jpeg"));
    node->setMaterialTexture(1, driver->getTexture("irrlicht-1.8.4/media/water.jpg"));
    node->setMaterialFlag(irr::video::EMF_FOG_ENABLE, false);
    node->setMaterialType(video::EMT_TRANSPARENT_REFLECTION_2_LAYER);
    node->setMaterialFlag(EMF_LIGHTING, false);

}

void Terrain::addBattleships() {
    core::vector3df posb1(4408,120,8533);
    Battleship b1 = Battleship(posb1,this->smgr,this->driver,this->device,1);
    b1.getNode()->setRotation(core::vector3df(0,40,0));

    core::vector3df posb2(5531,300,4746);
    Battleship b2 = Battleship(posb2,this->smgr,this->driver,this->device,2);
    b2.getNode()->setRotation(core::vector3df(270,40,0));

    core::vector3df posb3(5531,4500,4746);
    Battleship ms = Battleship(posb3,this->smgr,this->driver,this->device,0);
    ms.getNode()->setRotation(core::vector3df(270,0,0));
    
    //.getNode()->setRotation(core::vector3df(270,40,0));
}


scene::ISceneNode* Terrain::getSkybox() {
    return this->skybox;
}

scene::ISceneNode* Terrain::getSkydome() {
    return this->skydome;
}

scene::ITerrainSceneNode* Terrain::getTerrainGround() {
    return this->terrainGround;
}

scene::ITriangleSelector* Terrain::getSelectorGround() {
    return this->selectorGround
    ;
}