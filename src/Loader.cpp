    #include "irrlicht.h"
    // http://irrlicht.sourceforge.net/forum/viewtopic.php?f=9&t=45645
    using namespace irr;
    using namespace irr::core;
    using namespace irr::gui;
    using namespace irr::io;
    using namespace irr::video;
     
    /** The number of milliseconds to wait before allowing the callback function to
      * draw the next scene. This is required to prevent Irrlicht from pausing code
      * to wait for VSync(if set) when this is operating in a single thread.
      *
      * You can set this to 0 if you don't have VSync on. I couldn't do this in the
      * code because there isn't any way to query whether VSync is turned on or not
      * in Irrlicht.
      *
      * The value should be a rounded down integer = 1000ms / ScreenRefreshRate
      */
    #define LOADER_REFRESH_RATE 16
     
     
    /** The loading screen class **/
    class Loader
    {
    private:
        IrrlichtDevice* _device;
        IVideoDriver*   _driver;
        IGUIFont*       _font;      // font used to draw the message
     
        unsigned int loadSize;      // amount of stuff to load
        unsigned int loadProgress;  // amount of stuff loaded
        unsigned int lastBlitTime;  // time of previous refresh
     
        stringw      loadMessage;   // loading message on loading bar.
       
    public:
        Loader (IrrlichtDevice* device, IGUIFont* font) {
            _device = device;
            _driver = device->getVideoDriver();
            _font   = font;
            loadSize = 0;
            loadProgress = 0;
            lastBlitTime = 0;
        }
       
       
        /* Call this frequently in your loading loop to update the screen. */
        void callback (int loadIncrement)
        {
            loadProgress += loadIncrement;
         
            if (_device->getTimer()->getRealTime() - lastBlitTime > LOADER_REFRESH_RATE) {
                if (_device->run()) {
                    _driver->beginScene(true, false);
                    drawScreen();
                    _driver->endScene();
                   
                    lastBlitTime = _device->getTimer()->getRealTime();
                }
            } else { return; }
        }
       
        /* This is the drawing process. You can modify this to suit your needs. */
        void drawScreen ()
        {
            dimension2du sSize = _driver->getScreenSize();
           
            // loading bar lower layer
            _driver->draw2DRectangle(
                SColor(120,0,0,0),
                recti (8,8,sSize.Width-8,20)
            );
           
            float loadedBarSize = ((float)loadProgress / (float)loadSize) * ((float)sSize.Width - 20.0f);
     
            // loading bar upper layer
            _driver->draw2DRectangle(
                SColor(120,255,255,255),
                recti (10,10,(int)loadedBarSize,18)
            );
           
            // loading bar message
            _font->draw(
                loadMessage,
                recti (0,8,sSize.Width,20),
                SColor(255,255,255,255), true, true
            );
        }
       
        /* Throw an error screen and exit after 5 seconds. You can modify this to suit your needs. */
        void ThrowBSoD (stringw errorMessage)
        {
            unsigned int err = _device->getTimer()->getRealTime();
            unsigned int now = _device->getTimer()->getRealTime();
            dimension2du sSize = _driver->getScreenSize();
     
            while (_device->run())
            {
                now = _device->getTimer()->getRealTime();
               
                _driver->beginScene(true, false);
                drawScreen ();
               
                _driver->draw2DRectangle(
                    SColor(120,0,0,255),
                    recti (0,0,sSize.Width,sSize.Height)
                );
               
                _font->draw(
                    errorMessage,
                    recti (0,0,sSize.Width,sSize.Height),
                    SColor(255,255,255,255), true, true
                );
               
                _font->draw(
                    ((stringc)((now-err)/1000))+L" seconds till exit...",
                    recti(sSize.Width-100,sSize.Height-20,sSize.Width,sSize.Height), true, true
                );
               
                _driver->endScene();
               
                // Exit after 5 seconds
                if (now - err > 5000)
                    _device->closeDevice();
            }
       
        }
       
        /* Call this to change the loadString and reset the loadSize. */
        void reset (stringw loadString, unsigned int loadSize = 0)
        {
            loadMessage = loadString;
           
            if (loadSize != 0) {
                loadProgress  = 0;
                loadSize      = loadSize;
            }
     
            lastBlitTime = _device->getTimer()->getRealTime();
        }
    };