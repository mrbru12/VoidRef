#include "VoidRef.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

struct Point
{
public:
    float x, y;

public:
    Point()
        : x(0.0f), y(0.0f)
    {
    }
    Point(float X, float Y)
        : x(X), y(Y)
    {
    }
};

Point linesIntersectionPoint(Point a1, Point a2, Point b1, Point b2)
{
    float pX = (a1.x * a2.y - a2.x * a1.y) * (b1.x - b2.x) - (b1.x * b2.y - b2.x * b1.y) * (a1.x - a2.x);
    pX /= (a1.x - a2.x) * (b1.y - b2.y) - (b1.x - b2.x) * (a1.y - a2.y);
    
    float pY = (a1.x * a2.y - a2.x * a1.y) * (b1.y - b2.y) - (b1.x * b2.y - b2.x * b1.y) * (a1.y - a2.y);
    pX /= (a1.x - a2.x) * (b1.y - b2.y) - (b1.x - b2.x) * (a1.y - a2.y);

    return Point(pX, pY);
}

class App : public VRef::Program
{
public:
    bool onCreate() override
    {
        testShaderPurple.loadFromFile("C:/Dev/C++/VoidRef/Sandbox/Resources/Shaders/testShader.vert", 
                                "C:/Dev/C++/VoidRef/Sandbox/Resources/Shaders/testShaderPurple.frag");
        testShaderRed.loadFromFile("C:/Dev/C++/VoidRef/Sandbox/Resources/Shaders/testShader.vert",
                                "C:/Dev/C++/VoidRef/Sandbox/Resources/Shaders/testShaderRed.frag");
        
        mirror = new float[6]
        {
            0.5f, 0.5f, 1.0f,
            0.5f, -0.5f, 1.0f
        };

        lineRay = new float[6]
        {
            -0.5f, 0.0f, 1.0f,
            0.7f, -0.3f, 1.0f
        };

        p = linesIntersectionPoint({ mirror[0], mirror[1] }, { mirror[3], mirror[4] },
                                   { lineRay[0], lineRay[1] }, { lineRay[3], lineRay[4] });

        printf("%f %f\n", p.x, p.y);

        lineReflectionRay = new float[6]
        {
            p.x, p.y, 1.0f,
            0.0f, 1.0f, 1.0f
        };
        
        return true;
    }

    bool onUpdate() override
    {
        SDL_GetMouseState(&mouseX, &mouseY);
        // mousePos = glm::ortho(0, 0, mouseX, mouseY); // glm::normalize()
        
        lineRay[3] = mouseX; // mousePos[0][0];
        lineRay[4] = mouseY; // mousePos[1][0];

        p = linesIntersectionPoint({ mirror[0], mirror[1] }, { mirror[3], mirror[4] },
                                   { lineRay[0], lineRay[1] }, { lineRay[3], lineRay[4] });

        VRef::Draw::line(testShaderPurple, 6 * sizeof(float), mirror);

        VRef::Draw::line(testShaderRed, 6 * sizeof(float), lineRay);

        VRef::Draw::line(testShaderRed, 6 * sizeof(float), lineReflectionRay);
        
        return true;
    }
    
    void onDestroy() override
    {
        delete[] mirror;
        delete[] lineRay;
        delete[] lineReflectionRay;
    }

private:
    VRef::Shader testShaderPurple;
    VRef::Shader testShaderRed;

    int mouseX, mouseY;
    // glm::mat<4, 4, int, glm::packed_highp> mousePos;

    Point p;

    float* mirror;

    float* lineRay;
    float* lineReflectionRay;
};

int main(int argc, char** argv)
{
    App app;
    
    if (app.create("Teste", 800, 600))
        app.run();

    return 0;
}
