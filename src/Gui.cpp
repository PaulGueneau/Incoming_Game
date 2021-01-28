#include "Gui.hpp"

#include <iostream>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Gui::Gui(IVideoDriver* driver,ISceneManager* smgr,gui::IGUIEnvironment* env,IrrlichtDevice* device, int score)  {
    this->score = score;
    this->driver= driver;
    this->smgr = smgr;
    this->env = env;
    this->device = device;
}

void Gui::loadingScreen() {
    //env->addStaticText(L"Dummy Lobby", rect<s32>(150,20,350,40), true);

    irr::core::dimension2du screenSize = device->getVideoDriver()->getScreenSize();
    this->load = env->addImage(rect<s32>(0, 0, screenSize.Width, screenSize.Height), 0, 101, L"");
    this->load->setImage(env->getVideoDriver()->getTexture("new_data/loading/loading2.png"));
    this->load->setScaleImage(true);
    driver->beginScene(true, true, SColor(255,155,155,155));
    smgr->drawAll();
    env->drawAll();
    driver->endScene();

}

void Gui::stopLoadingScreen() {
    this->load->remove();
}



void Gui::setHUD() {
    this->font = this->device->getGUIEnvironment()->getFont("irrlicht-1.8.4/media/bigfont.png");
    this->skin = this->env->getSkin(); 
    irr::core::dimension2du screenSize = device->getVideoDriver()->getScreenSize();
    IGUIImage *loadSight = env->addImage(rect<s32>(screenSize.Width/2.0f-30, screenSize.Height/2.0f-30, screenSize.Width/2.0f+30, screenSize.Height/2.0f+35), 0, 101, L"");
    loadSight->setImage(env->getVideoDriver()->getTexture("new_data/gui/sight.png"));
    loadSight->setScaleImage(true);
    core::rect<s32> imp1(349,15,385,78);
    core::rect<s32> imp2(387,15,423,78);


    this->driver->beginScene(true, true, video::SColor(255, 100, 101, 140));
    this->smgr->drawAll();
    this->env->drawAll();
}

void Gui::displayScore() {
    this->scoreTextBox = this->env->addStaticText(L"Score", rect<s32>(10,10,350,150), false);
    this->scoreTextBox->setOverrideFont(this->font);
    this->scoreTextBox->setOverrideColor(video::SColor(255, 255, 255, 255));
    irr::core::stringw str = L"Score : ";
    str += this->score;
    this->scoreTextBox->setText(str.c_str());
}

void Gui::incrementScore() {
    this->score += 100;
    irr::core::stringw str = L"Score : ";
    str += this->score;
    this->scoreTextBox->setText(str.c_str());


        if (this->score >= 1000) {
        irr::core::dimension2du screenSize = device->getVideoDriver()->getScreenSize();
        this->winTextBox = this->env->addStaticText(L"YOU WIN", rect<s32>(screenSize.Width/2.0f-100, screenSize.Height/2.0f-50, screenSize.Width/2.0f+100, screenSize.Height/2.0f+50), false);
        this->winTextBox->setOverrideFont(this->font);
        this->winTextBox->setOverrideColor(video::SColor(255, 255, 255, 255));

    }

}
