#ifndef GUI_H
#define GUI_H
#include <irrlicht.h>
#include <ostream>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Gui {
    public :
        Gui( IVideoDriver* driver,ISceneManager* smgr,gui::IGUIEnvironment* env,IrrlichtDevice* device, int score);
        void loadingScreen();
        void stopLoadingScreen();
        void setHUD();
        void displayScore();
        void menu();
        void incrementScore();
        //void 

    private:
        IVideoDriver* driver;
        ISceneManager* smgr;
        gui::IGUIEnvironment* env;
        IrrlichtDevice* device;
        IGUIImage *load;
        IGUIStaticText* scoreTextBox;
        IGUIStaticText* winTextBox;
        IGUIFont *font;
        IGUISkin* skin;
        int score;


};
#endif