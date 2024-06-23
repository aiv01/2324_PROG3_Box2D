#include "PlatformScene.h"
#include "OGLQuadRenderer.h"
#include "OrthoCamera.h"
#include "physics/RigidBody2D.h"
#include "physics/BoxCollider2D.h"
#include "iostream"
//#include "physics/Physics2DContactListener.h"
//#include <functional>

static glm::vec2 _SelectedJumpForce{0, 0};
static glm::vec2 _SelectedMoveForce{0, 0};

void PlatformScene::Start()
{
    Camera = new OrthoCamera(Win.GetWidth(), Win.GetHeight(), 10); // for simplicity: 1 OrthoSize = 1 meter

    Quad *Floor = new Quad(Camera->GetOrthoWidth(), 1);
    Floor->Position = glm::vec3{0, -Camera->GetOrthoHeight() * 0.5f + Floor->Scale.y * 0.5f, 0};
    Floor->Collider = new BoxCollider2D(Floor);
    Floor->Name = "Floor";

    Platform = new Quad(3,.5f);
    Platform->Position = glm::vec3{4, 0, 0};
    Platform->Color = Color_Yellow;
    Platform->Collider = new BoxCollider2D(Platform);
    Platform->RigidBody = new RigidBody2D(Platform, RigidBodyType::Kinematic);
    Platform->Name = "Platform";

    Player = new Quad(1, 1);
    Player->Position = glm::vec3{0, 0, 0};
    Player->Color = Color_Red;
    Player->Name = "Player";

    CollisionCallBack PlayerCB;
    PlayerCB.OnEnter = [](Quad* Other){
        std::cout << "OnEnter: " << Other->Name << std::endl;
    };

    Player->Collider = new BoxCollider2D(Player, PlayerCB);
    Player->RigidBody = new RigidBody2D(Player, RigidBodyType::Dynamic);

    Quads.push_back(Floor);
    Quads.push_back(Player);
    Quads.push_back(Platform);
}

void PlatformScene::Update()
{
    Renderer.Draw(Quads, Camera);

    static bool IsJumpPressed = false;
    static float PlatformSpeed = -1.f;
    
    //Eventually could be done only when velocity is changed
    Platform->RigidBody->SetVelocity(glm::vec2{PlatformSpeed, 0});

    if (Platform->Position.x < -4 && PlatformSpeed < 0) 
    {
        PlatformSpeed *= -1.f;
    }
    if (Platform->Position.x > 4 && PlatformSpeed > 0) 
    {
        PlatformSpeed *= -1.f;
    }      


    if (Win.IsKeyPressed(Key::KEY_UP))
    {
        if (!IsJumpPressed)
        {
            //Player->RigidBody->AddImpulse(glm::vec2(0, 5));
            _SelectedJumpForce = glm::vec2(0, 5);
            IsJumpPressed = true;
        }
    }
    else
    {
        IsJumpPressed = false;
    }

    if (Win.IsKeyPressed(Key::KEY_LEFT))
    {
        //Player->RigidBody->AddForce(glm::vec2(-1, 0));
        _SelectedMoveForce = glm::vec2(-10, 0);
    }

    else if (Win.IsKeyPressed(Key::KEY_RIGHT))
    {
        //Player->RigidBody->AddForce(glm::vec2(1, 0));
        _SelectedMoveForce = glm::vec2(10, 0);
    }
}

void PlatformScene::FixedUpdate()
{
    
    Player->RigidBody->AddImpulse(_SelectedJumpForce);
    _SelectedJumpForce = glm::vec2{0, 0};
    

    Player->RigidBody->AddForce(_SelectedMoveForce);
    _SelectedMoveForce = glm::vec2{0, 0};


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
