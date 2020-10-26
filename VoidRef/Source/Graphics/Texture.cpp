// -> Headers being implemented here:
#include "Texture.h"
#include "../Main/Program.h"

// -> Not my own headers:
#include <SDL.h>
#include <SDL_image.h>

// -> My own headers:
#include "../Debug/SysLog.h"

namespace VRef
{
    Texture::Texture()
        : width(NULL), height(NULL), rotationAngle(0.0), rotationPoint({ NULL, NULL }), flipMode(SDL_FLIP_NONE), renderer(NULL), texture(NULL)
    {

    }

    Texture::~Texture()
    {
        SDL_DestroyTexture(texture);
    }

    void Texture::load(SDL_Renderer* textureRenderer, const char* path)
    {
        renderer = textureRenderer;

        texture = IMG_LoadTexture(renderer, path);
        System::logOnSdlError(texture == NULL);

        SDL_QueryTexture(texture, NULL, NULL, &width, &height);

        rotationPoint = { width / 2, height / 2 };
    }

    void Texture::render(int x, int y)
    {
        SDL_Rect destinationRect = { x, y, width, height };
        
        SDL_RenderCopyEx(renderer, texture, NULL, &destinationRect, rotationAngle, &rotationPoint, flipMode);
    }

    void Texture::render(SDL_Rect& rect)
    {
        SDL_RenderCopyEx(renderer, texture, NULL, &rect, rotationAngle, &rotationPoint, flipMode);
    }

    /*
    void Texture::scale(double amount)
    {
        width *= amount;
        height *= amount;
    }
    */
}
