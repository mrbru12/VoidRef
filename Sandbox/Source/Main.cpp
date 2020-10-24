#include "VoidRef.h"

#include <iostream>

#define WIDTH 800
#define HEIGHT 600

class App : public VRef::Program
{
public:
    bool onCreate() override
    {
        testShader.loadFromFile("C:/Dev/C++/VoidRef/Sandbox/Resources/Shaders/testShader.vert", 
                                "C:/Dev/C++/VoidRef/Sandbox/Resources/Shaders/testShader.frag");

        triangleVertices = new float[9]
        {
            -0.6f, -0.5f, 1.0f,
            0.6f, -0.5f, 1.0f,
            0.0f, 0.7f, 1.0f
        };

        rectangleVertices = new float[12]
        {
            -0.5f, -0.5f, 1.0f,
            0.5f, -0.5f, 1.0f,
            -0.5f, 0.5f, 1.0f,
            0.5f, 0.5f, 1.0f
        };

        rectangleIndices = new unsigned int[6]
        {
            0, 1, 2,
            1, 2, 3
        };
        
        return true;
    }

    bool onUpdate() override
    {
        VRef::Draw::triangle(testShader, 9 * sizeof(float), triangleVertices);
        
        VRef::Draw::triangle(testShader, 
                             12 * sizeof(float), rectangleVertices, 
                             6 * sizeof(unsigned int), rectangleIndices);

        return true;
    }

    void onDestroy() override
    {
        delete[] triangleVertices;
        delete[] rectangleVertices;
        delete[] rectangleIndices;
    }

private:
    VRef::Shader testShader;

    float* triangleVertices;

    float* rectangleVertices;
    unsigned int* rectangleIndices;
};

int main(int argc, char** argv)
{
    App app;
    
    if (app.create("Teste", 800, 600))
        app.run();

    return 0;
}