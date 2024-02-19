#include <SDL2/SDL.h>
#include <string>
#ifndef MEDIA_H
#define MEDIA_H

extern SDL_Texture *background;

// Loads media
bool loadMedia(SDL_Renderer *renderer, SDL_Surface *screenSurface);

void destroyMedia();

// Loads individual image
SDL_Surface *loadSurface(std::string path, SDL_Surface *screenSurface);

// Load individual image as texture
SDL_Texture *loadTexture(std::string path, SDL_Renderer *renderer, SDL_Surface *screenSurface);

#endif
