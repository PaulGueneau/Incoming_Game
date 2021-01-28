#include "Wave.hpp"
#include <iostream>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// On crée une liste de vaisseau grâce à une liste , nous n'avons  que besoin des coordonnées du premier vaisseau

Wave::Wave(ISceneManager* smgr,IVideoDriver* driver)  {
}

Wave::Wave(ISceneManager* smgr,IVideoDriver* driver, std::string formation, uint& numberShips,core::vector3df& position,core::vector3df& destination, float& vitesse,IrrlichtDevice* device,Gui* gui )  {
    this->numberShips = numberShips;
    this->destinationFirstShip = destination;
    this->positionFirstShip = position;
    this->driver = driver;
    this->smgr = smgr;
    this->vitesse = vitesse;
    this->device = device;
    this->gui = gui;
    if (formation == "line") {
        createLineFormation();
    }
    else {
        std::cerr << "Bad formation argument";
    }
}

void Wave::createLineFormation(){

    for (int k=0; k<numberShips ; k++) {
        core::vector3df position = this->positionFirstShip;
        position+= core::vector3df(k*300.0f,0.0f,0.0f);
        core::vector3df destination = this->destinationFirstShip;
        destination+= core::vector3df(k*300.0f,0.0f,0.0f);
        Flyingsaucer* fs =createFlyingSaucer(position,destination,vitesse);
        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        formation.insert(std::make_pair(boost::uuids::to_string(uuid),fs));
    }
    
}

Flyingsaucer* Wave::createFlyingSaucer(core::vector3df& position,core::vector3df& destination, float& vitesse){
    Flyingsaucer* ship =  new Flyingsaucer(position,smgr,driver,device,gui);
    ship->setVitesse(vitesse);
    ship->setDestination(destination);
    ship->launchAnimation();
    std::cout << ship << std::endl;
    return ship;

}


const core::vector3df Wave::GetPositionFirstShip() const {
    return positionFirstShip;
}

void Wave::SetPositionFirstShip(core::vector3df& positionFirstShip) {
    positionFirstShip = positionFirstShip;
}


const core::vector3df Wave::GetDestinationFirstShip() const {
    return destinationFirstShip;
}

void Wave::SetDestinationFirstShip(core::vector3df& destination) {
    destinationFirstShip = destination;
}



const  std::map < std::string,Flyingsaucer*> Wave::GetFormation() const {
    return formation;
}

void Wave::SetFormation(std::map < std::string,Flyingsaucer>& formation) {
    formation = formation;
}

