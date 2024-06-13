#pragma once
#include <vector>
#include "Quad.h"
#include "OGLWindow.h"
#include "OGLQuadRenderer.h"


class PlatformScene
{
public:
    PlatformScene(const OGLWindow& InWin) : Win(InWin) { }
    void Start();
    void Update();
    void Destroy();
private:
    std::vector<Quad*> Quads;
    const OGLWindow& Win;
    OGLQuadRender Renderer;
    OrthoCamera* Camera;
};