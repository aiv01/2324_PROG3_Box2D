#include "PlatformScene.h"
#include "OGLQuadRenderer.h"
#include "OrthoCamera.h"

void PlatformScene::Start() 
{
    Camera = new OrthoCamera(Win.GetWidth(), Win.GetHeight(), 10);

    Quad* Floor = new Quad(Camera->GetOrthoWidth(), 1);
    Floor->Position = glm::vec3{0, -Camera->GetOrthoHeight() * 0.5f + Floor->Scale.y * 0.5f, 0};

    Quad* Player = new Quad(1, 1);
    Player->Position = glm::vec3{0, 0, 0};
    Player->Color = Color_Red;
    
    Quads.push_back(Floor);    
    Quads.push_back(Player);    
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
