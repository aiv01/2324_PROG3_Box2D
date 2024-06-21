#include "PlatformScene.h"
#include "OGLQuadRenderer.h"
#include "OrthoCamera.h"
#include "physics/RigidBody2D.h"
#include "physics/BoxCollider2D.h"

void PlatformScene::Start()
{
    Camera = new OrthoCamera(Win.GetWidth(), Win.GetHeight(), 10); // for simplicity: 1 OrthoSize = 1 meter

    Quad *Floor = new Quad(Camera->GetOrthoWidth(), 1);
    Floor->Position = glm::vec3{0, -Camera->GetOrthoHeight() * 0.5f + Floor->Scale.y * 0.5f, 0};
    Floor->Collider = new BoxCollider2D(Floor);

    Player = new Quad(1, 1);
    Player->Position = glm::vec3{0, 0, 0};
    Player->Color = Color_Red;
    Player->Collider = new BoxCollider2D(Player);
    Player->RigidBody = new RigidBody2D(Player);

    Quads.push_back(Floor);
    Quads.push_back(Player);
}

void PlatformScene::Update()
{
    Renderer.Draw(Quads, Camera);

    static bool IsJumpPressed = false;

    if (Win.IsKeyPressed(Key::KEY_UP))
    {
        if (!IsJumpPressed)
        {
            Player->RigidBody->AddImpulse(glm::vec2(0, 5));
            IsJumpPressed = true;
        }
    }

    else
    {
        IsJumpPressed = false;
    }

    if (Win.IsKeyPressed(Key::KEY_LEFT))
    {
        Player->RigidBody->AddForce(glm::vec2(-10, 0));
    }

    else if (Win.IsKeyPressed(Key::KEY_RIGHT))
    {
        Player->RigidBody->AddForce(glm::vec2(10, 0));
    }
}

void PlatformScene::FixedUpdate()
{
    for (auto *Each : Quads)
    {
        if (Each->RigidBody)
            Each->RigidBody->Update();
    }
}

void PlatformScene::Destroy()
{
    delete Camera;
    for (auto *Each : Quads)
        delete Each;
}
