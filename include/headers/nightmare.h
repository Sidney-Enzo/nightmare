#ifndef NIGHTMARE_H
#define NIGHTMARE_H

#include <SDL.h>

class Nightmare
{
public:
    Nightmare(const char* TITLE = "Nightmare", int WINDOW_X = SDL_WINDOWPOS_CENTERED, int WINDOW_Y = SDL_WINDOWPOS_CENTERED, int WINDOW_WIDTH = 846, int WINDOW_HEIGHT = 448, int FLAGS = 0);
    virtual ~Nightmare();

    virtual void setUp(int argc, char* argv[]) {};
    virtual void render() {};
    virtual void update(double deltaTime) {};
    virtual void fixedUpdate(double fixedDeltaTime) {};
    virtual void shutDown() {};

    void clear(Uint8 RED = 0, Uint8 GREEN = 0, Uint8 BLUE = 0, float OPACITY = 0.0f);
    void present();
    void setFPS(int FPS);
    void quit();

    void event();
    void frameDraw();
    void frameUpdate();

    int run(int argc, char* argv[]);
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    bool m_isRunning;

    Uint32 m_frameStart = 0, m_frameEnd = 0;
    double m_amountDeltaTime = 0.0, m_fpsCap = 1000.0/60.0;
};

#endif