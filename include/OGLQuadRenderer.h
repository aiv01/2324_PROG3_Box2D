#pragma once
#include <glad/glad.h>
#include <vector>

class OGLQuadRender 
{
public:
    OGLQuadRender();
    void Draw(const std::vector<class Quad*>& Quads, const class OrthoCamera* Cam);
private:
    class OGLProgram* Program;
    GLuint Vao;
    GLuint Vbo;
};

