#include "PlatformScene.h"
#include "OGLQuadRenderer.h"

void PlatformScene::Start() 
{
    Camera = new OrthoCamera(Win.GetWidth(), Win.GetHeight());

    Quad* Q1 = new Quad(100, 10);
    Q1->Position = glm::vec3{-100, 0, 0};

    Quad* Q2 = new Quad(100, 10);
    Q2->Position = glm::vec3{100, 0, 0};
    
    Quads.push_back(Q1);    
    Quads.push_back(Q2);    
}

void PlatformScene::Update()
{
    Renderer.Draw(Quads, Camera);
}

void PlatformScene::Destroy()
{
    delete Camera;
    for (auto* Each : Quads) delete Each;
}
