#pragma once
#include <glm/glm.hpp>

class OrthoCamera 
{
public:
    OrthoCamera(int w, int h) ;
    glm::mat4 GetViewProjMat() const;
    int GetWidth() const;
    int GetHeight() const;
private:
    glm::mat4 View;
    glm::mat4 Proj;
    glm::mat4 ViewProj;
    int Width;
    int Height;
};
