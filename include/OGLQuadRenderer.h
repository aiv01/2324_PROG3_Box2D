#pragma once
#include <glad/glad.h>
#include "OGLProgram.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include "Quad.h"

class OrthoCamera 
{
public:
    OrthoCamera(int w, int h) 
    {   
        Width = w;
        Height = h;

        auto Pos = glm::vec3(0);
        auto Dir = glm::vec3(0.f, 0.f, -1.f);
        auto Up = glm::vec3(0.f, 1.f, 0.f);
        View = glm::lookAt(Pos, Pos + Dir, Up);

        float aspect = (float)w / (float)h;
        //float fw = aspect;
       // float fh = 1.f;

        //(0, 0) in the middle of the screen
        float halfW = (float)w * 0.5f;
        float halfH = (float)h * 0.5f;
        
        float left = -halfW;
        float right = halfW;
        float bottom = -halfH;
        float top = halfH;
        Proj = glm::ortho(left, right, bottom, top, 0.f, 100.f);
        //Proj = glm::perspective(glm::radians(60.f), aspect, 0.f, 100.f);

        ViewProj =  Proj * View;
    }

    glm::mat4 GetViewProjMat() const 
    { 
        return ViewProj;
    }

    int GetWidth() const { return Width; }
    int GetHeight() const { return Height; }
private:
    glm::mat4 View;
    glm::mat4 Proj;
    glm::mat4 ViewProj;
    int Width;
    int Height;
};

class OGLQuadRender 
{
public:
    OGLQuadRender() 
    {
         Program = new OGLProgram("resources/shaders/quadcolor.vert", "resources/shaders/quadcolor.frag");

         std::vector<float> Vertices = {
             0.5f, -0.5f, 0.0f, //bottom right
            -0.5f, -0.5f, 0.0f, //bottom left
            -0.5f,  0.5f, 0.0f, //top left

            -0.5f,  0.5f, 0.0f, //top left
             0.5f,  0.5f, 0.0f, //top right
             0.5f, -0.5f, 0.0f  //bottom right
        };

         //1. Create VAO
        glGenVertexArrays(1, &Vao);
        glBindVertexArray(Vao);

        //2. Create VBO to load data
        glGenBuffers(1, &Vbo);
        glBindBuffer(GL_ARRAY_BUFFER, Vbo);

        int DataSize = Vertices.size() * sizeof(float);
        glBufferData(GL_ARRAY_BUFFER, DataSize, Vertices.data(), GL_STATIC_DRAW);

        //3. Link to Vertex Shader
        GLuint Location_0 = 0;
        glVertexAttribPointer(Location_0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(Location_0);

        glClearColor(0, 0, 0, 0);
    }

    void Draw(const std::vector<Quad*>& Quads, const OrthoCamera* Cam) 
    {
        glViewport(0, 0, Cam->GetWidth(), Cam->GetHeight());
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(Vao);
        Program->Bind();
        auto VP = Cam->GetViewProjMat();

        static glm::mat4 uniMat = glm::mat4(1.0f);
        for (size_t i = 0; i < Quads.size(); i++)
        {
            auto* Each = Quads[i];

            glm::mat4 Translate = glm::translate(uniMat, Each->Position);
            glm::mat4 Rotate = glm::mat4_cast(glm::quat( glm::vec3(glm::radians(Each->Rotation.x), glm::radians(Each->Rotation.y), glm::radians(Each->Rotation.z)) ));
            glm::mat4 Scale = glm::scale(uniMat, Each->Scale);
            glm::mat4 Model = Translate * Rotate * Scale;

            glm::mat4 Mvp = VP * Model;

            Program->SetUniform("mvp", Mvp);
            Program->SetUniform("color", Each->Color);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }
private:
    OGLProgram* Program;
    GLuint Vao;
    GLuint Vbo;
};

