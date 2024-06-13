#include "PlatformScene.h"
#include "OGLQuadRenderer.h"
#include "OrthoCamera.h"

void PlatformScene::Start() 
{
    Camera = new OrthoCamera(Win.GetWidth(), Win.GetHeight());

    Quad* Q1 = new Quad(100, 10);
    Q1->Position = glm::vec3{300, 300, 0};

    Quad* Q2 = new Quad(100, 10);
    Q2->Position = glm::vec3{500, 300, 0};
    
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
