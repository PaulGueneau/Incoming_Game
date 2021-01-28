#ifndef WAVE_H
#define WAVE_H
#include <irrlicht.h>
#include <ostream>
#include "Flying_saucer.hpp"
#include "Gui.hpp"
#include <list>
#include <map>
#include <iterator>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Wave {
    public :
        Wave(ISceneManager* smgr,IVideoDriver* driver);
        Wave(ISceneManager* smgr,IVideoDriver* driver, std::string formation, uint& numberShips,core::vector3df& position,core::vector3df& destination, float& vitesse,IrrlichtDevice* device,Gui* gui );
        
        const core::vector3df GetPositionFirstShip() const;
        void SetPositionFirstShip(core::vector3df& positionFirstShip);

        const core::vector3df GetDestinationFirstShip() const;
        void SetDestinationFirstShip(core::vector3df& destination);

        const std::map < std::string,Flyingsaucer*> GetFormation() const;
        Flyingsaucer* createFlyingSaucer(core::vector3df& position,core::vector3df& destination, float& vitesse);

        void SetFormation(std::map < std::string,Flyingsaucer>& formation);
        void SetVitesse(float& vitesse);
        void createLineFormation();


    private:
        ISceneManager* smgr;
        IVideoDriver* driver;
        IrrlichtDevice* device;
        std::map < std::string,Flyingsaucer*> formation; // key = temps ou debute l'explosion , car la fumée reste en l'air plusieurs secondes
        //std::list<Flyingsaucer> formation;
        core::vector3df positionFirstShip;
        uint numberShips;
        core::vector3df destinationFirstShip;
        float vitesse;
        Gui* gui;

};
#endif