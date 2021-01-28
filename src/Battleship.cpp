#include "Battleship.hpp"
#include <iostream>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
#define M_PI 3.14159265358979323846
Battleship::Battleship()  {
    this->position= core::vector3df(0,0,0);
}

Battleship::Battleship(core::vector3d<f32>& pos,ISceneManager* smgr,IVideoDriver* driver,IrrlichtDevice* device, uint typeBattleship)  {
    this->driver = driver;
    this->position= pos;
    this->smgr = smgr;
    this->device = device;
    initialiseObject(typeBattleship);
}

void Battleship::setPosition(core::vector3df& pos){
    position = pos;
}


IAnimatedMeshSceneNode* Battleship::getNode() {
    return this->shipNode;
}

void Battleship::initialiseObject(uint typeBattleship){
    
    if (typeBattleship == 1) {
        loadSubmarine();
    }

    if (typeBattleship == 2) {
        loadKingClassShip();
    }

    if (typeBattleship == 0) {
        loadMotherShip();
    }
    
    
    
    
}

void Battleship::loadKingClassShip() {
    scene::IAnimatedMesh* mesh;
    mesh = smgr->getMesh ( "new_data/battleship/KING_GEORGES_V.obj" );
    this->shipNode = smgr->addAnimatedMeshSceneNode(mesh);
    core::vector3d<f32> factorEscalate(1000.0f,1000.0f,1000.0f);    
    this->shipNode->setScale(factorEscalate);
    this->shipNode->setPosition(position);
    this->shipNode->setMaterialTexture(0,driver->getTexture("new_data/battleship/King_George_V.jpg"));
    this->shipNode->setMaterialFlag(EMF_LIGHTING,false);



}

void Battleship::loadSubmarine() {
    scene::IAnimatedMesh* mesh;
    mesh = smgr->getMesh ( "new_data/battleship/Submarine.obj" );
    this->shipNode = smgr->addAnimatedMeshSceneNode(mesh);
    core::vector3d<f32> factorEscalate(1.0f,1.0f,1.0f);    
    this->shipNode->setScale(factorEscalate);
    this->shipNode->setPosition(position);
    this->shipNode->setMaterialTexture(0,driver->getTexture("new_data/battleship/grey.jpeg"));
    this->shipNode->setMaterialFlag(EMF_LIGHTING,false);

}


void Battleship::loadMotherShip() {
        scene::IAnimatedMesh* mesh;
    mesh = smgr->getMesh ( "new_data/battleship/mothership/drift.3ds" );
    this->shipNode = smgr->addAnimatedMeshSceneNode(mesh);
    core::vector3d<f32> factorEscalate(90.0f,90.0f,90.0f);    
    this->shipNode->setScale(factorEscalate);
    this->shipNode->setPosition(position);
    this->shipNode->setMaterialTexture(0,driver->getTexture("new_data/battleship/mothership/Textures/Circuit/Circuitry_blue.jpg"));
    this->shipNode->setMaterialFlag(EMF_LIGHTING,false);
    core::vector3d<f32> rotaShip(0,0.02f,0);
    scene::ISceneNodeAnimator* anim_vaisseau  = smgr->createRotationAnimator(rotaShip);
    this->shipNode->addAnimator(anim_vaisseau);

}