#include "VoidRef.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

#define SANDBOX_B

#ifdef SANDBOX_A
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
    float t = (a1.x - b1.x) * (b1.y - b2.y) - (a1.y - b1.y) * (b1.x - b2.x);
    t /= (a1.x - a2.x) * (b1.y - b2.y) - (a1.y - a2.y) * (b1.x - b2.x);

    float pX = a1.x + t * (a2.x - a1.x);
    float pY = a1.y + t * (a2.y - a1.y);

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

        /*
        polygonVertices = new float[15]
        {
            -0.8f, -0.7f, 1.0f,
            -0.5f, -0.9f, 1.0f,
            -0.2f, -0.4f, 1.0f,
            -0.3f, 0.2f, 1.0f,
            -0.5f, 0.4f, 1.0f
        };
        */
        
        return true;
    }

    bool onUpdate() override
    {
        SDL_GetMouseState(&mouseX, &mouseY);
        // mousePos = glm::ortho(0, 0, mouseX, mouseY); // glm::normalize()
        
        // lineRay[3] = mouseX; // mousePos[0][0];
        // lineRay[4] = mouseY; // mousePos[1][0];

        // lineRay[2] += 0.01;
        // lineRay[3] += 0.001;
        lineRay[4] += 0.002;

        p = linesIntersectionPoint({ mirror[0], mirror[1] }, { mirror[3], mirror[4] },
                                   { lineRay[0], lineRay[1] }, { lineRay[3], lineRay[4] });

        lineReflectionRay[0] = p.x;
        lineReflectionRay[1] = p.y;

        VRef::Draw::line(testShaderPurple, 6 * sizeof(float), mirror);

        VRef::Draw::line(testShaderRed, 6 * sizeof(float), lineRay);

        // if (doIntersect({ mirror[0], mirror[1] }, { mirror[3], mirror[4] },
        //                 { lineRay[0], lineRay[1] }, { lineRay[3], lineRay[4] }))
        VRef::Draw::line(testShaderRed, 6 * sizeof(float), lineReflectionRay);

        // VRef::Draw::polygon(testShaderPurple, 15 * sizeof(float), polygonVertices);
        
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

    // float* polygonVertices;
};
#endif

#ifdef SANDBOX_B
class App : public VRef::Program
{
public:
    VRef::Shader shader_0;
    VRef::Shader shader_1;

    float* rectVertices_0;
    float* rectVertices_1;
    unsigned int* rectIndices;

public:
    bool onCreate() override
    {
        shader_0.loadFromFile("C:/Dev/C++/VoidRef/Sandbox/Resources/Shaders/testShader.vert",
                                      "C:/Dev/C++/VoidRef/Sandbox/Resources/Shaders/testShaderPurple.frag");
        shader_1.loadFromFile("C:/Dev/C++/VoidRef/Sandbox/Resources/Shaders/testShader.vert",
                                   "C:/Dev/C++/VoidRef/Sandbox/Resources/Shaders/testShaderRed.frag");

        rectVertices_0 = new float[12]
        {
            -0.6f, -0.6f, 1.0f,
            -0.6f, 0.4f, 1.0f,
            0.4f, 0.4f, 1.0f,
            0.4f, -0.6f, 1.0f
        };
        rectVertices_1 = new float[12]
        {
            -0.4f, -0.4f, 1.0f,
            -0.4f, 0.6f, 1.0f,
            0.6f, 0.6f, 1.0f,
            0.6f, -0.4f, 1.0f
        };
        rectIndices = new unsigned int[6]
        {
            0, 1, 2,
            0, 2, 3
        };

        return true;
    }

    bool onUpdate() override
    {
        VRef::Draw::triangle(shader_0, 12 * sizeof(float), rectVertices_0, 6 * sizeof(float), rectIndices);

        VRef::Draw::triangle(shader_1, 12 * sizeof(float), rectVertices_1, 6 * sizeof(float), rectIndices);
        
        return true;
    }

    void onDestroy() override
    {
        delete[] rectVertices_0;
        delete[] rectVertices_1;
        delete[] rectIndices;
    }
};
#endif

int main(int argc, char** argv)
{
    App app;
    
    if (app.create("Teste", 800, 600))
        app.run();

    return 0;
}
