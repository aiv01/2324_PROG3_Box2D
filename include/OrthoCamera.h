#pragma once
#include <glm/glm.hpp>

class OrthoCamera 
{
public:
    OrthoCamera(int w, int h, float InOrthoSize) ;
    glm::mat4 GetViewProjMat() const;
    int GetResoWidth() const;
    int GetResoHeight() const;
    float GetOrthoWidth() const;
    float GetOrthoHeight() const;
private:
    glm::mat4 View;
    glm::mat4 Proj;
    glm::mat4 ViewProj;
    int Width;
    int Height;

    float OrthoWidth;
    float OrthoHeight;
};
