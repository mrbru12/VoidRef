#pragma once

#include <SDL.h>

namespace VRef
{
    class Texture
    {
    public:
        int width, height;
        double rotationAngle;
        SDL_Point rotationPoint;
        SDL_RendererFlip flipMode;

    public:
        Texture();
        ~Texture();

        void load(SDL_Renderer* textureRenderer, const char* path);

        void render(int x, int y);
        void render(SDL_Rect& rect);

        /// <summary>
        /// Scales texture's width and height values, multiplying them by {amount}
        /// </summary>
        // void scale(double amount);

    private:
        SDL_Renderer* renderer;
        SDL_Texture* texture;
    };
}
