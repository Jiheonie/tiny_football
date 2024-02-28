#include <SDL2/SDL.h>
#include <string>

#ifndef INIT_H
#define INIT_H

#define WIDTH 1280
#define HEIGHT 720

// The window we'll be rendering to
extern SDL_Window *window;

// The window renderer
extern SDL_Renderer *renderer;

// The surface contained by the window
extern SDL_Surface *screenSurface;

// Starts up SDL and creates window
bool init();

// Frees media and shuts down SDL
void close();

#endif