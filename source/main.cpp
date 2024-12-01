#include "headers/nightmare.h"

class Game : public Nightmare
{
public: 
    // each function will be called on the main loop in an expecifc order
    // except by the setup function that will be called just once
    void setup(int argc, char* argv[])
    {
        
    };

    void render()
    {
        // just put your draw shit in here
    };

    void update(double deltaTime)
    {
        // this one is called only once every single time the game looping happen
    };

    void fixedUpdate(double fixedDeltaTime) 
    {  
        // this function is called multiples/framerate times in a single
        // looping making it hardware independent
        // generaly used for physics preveting noclipping
    };
};

int main(int argc, char* argv[])
{
    Game engine;
    return engine.run(argc, argv);
}