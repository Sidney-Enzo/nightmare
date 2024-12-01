#include "headers/nightmare.h"

#include <stdio.h>
#include <iostream>

Nightmare::Nightmare(const char* TITLE, int WINDOW_X, int WINDOW_Y, int WINDOW_WIDTH, int WINDOW_HEIGHT, int FLAGS)
{
    if (!SDL_WasInit(SDL_INIT_EVERYTHING)) 
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
        {
            fprintf(stderr, "[ERROR!] SDL2 couldn't be initialized: %S\n", SDL_GetError());
            return;
        }
    }
    m_window = SDL_CreateWindow(TITLE, WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, FLAGS);
    if (m_window == nullptr)
    {
        fprintf(stderr, "[ERROR!] window couldn't be created: %S\n", SDL_GetError());
        return;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (m_renderer == nullptr)
    {
        fprintf(stderr, "[ERROR!] renderer couldn't be created: %S\n", SDL_GetError());
        return;
    }
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
    
    m_isRunning = true;
}

Nightmare::~Nightmare()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Nightmare::clear(Uint8 RED, Uint8 GREEN, Uint8 BLUE, float OPACITY)
{ 
    SDL_SetRenderDrawColor(m_renderer, RED, GREEN, BLUE, OPACITY*255);
    SDL_RenderClear(m_renderer);
}

void Nightmare::present()
{ SDL_RenderPresent(m_renderer); }

void Nightmare::setFPS(int FPS) 
{ m_fpsCap = 1000.0/FPS; }

void Nightmare::quit()
{ m_isRunning = false; }

void Nightmare::event()
{
    SDL_Event eventHandler;
    SDL_PollEvent(&eventHandler);
    switch (eventHandler.type)
    {
    case SDL_QUIT:
        m_isRunning = false;
        break;
    } 
}

void Nightmare::frameDraw()
{
    clear();
    render();
    present();
}

void Nightmare::frameUpdate()
{
    m_frameEnd = SDL_GetTicks();
    int deltaTime = m_frameEnd - m_frameStart;
    m_frameStart = m_frameEnd; // tring to get better precission
    // FPS CAP
    if (deltaTime < m_fpsCap) {
        SDL_Delay(m_fpsCap - deltaTime);
        deltaTime = m_fpsCap;
    }
    // std::cout << "FPS: " << 1000/deltaTime << std::endl;
    event();
    update(deltaTime/1000.0);
    m_amountDeltaTime += deltaTime;
    while (m_amountDeltaTime > m_fpsCap)
    {
        fixedUpdate(1000/m_fpsCap);
        m_amountDeltaTime -= deltaTime;
    }
}

int Nightmare::run(int argc, char* argv[]) // just the basical to make it render a black window
{
    setUp(argc, argv);
    m_frameStart = SDL_GetTicks(); // first frame
    while (m_isRunning) 
    {
        frameDraw();
        frameUpdate();
    }
    frameDraw(); // make EVERY single frame be rendered
    shutDown();
    delete this; // self destroy
    return 0;
}