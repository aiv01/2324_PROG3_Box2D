#include "physics/RigidBody2D.h"
#include "physics/BoxCollider2D.h"
#include <box2d/box2d.h>
#include "Quad.h"
#include "ServiceRegistry.h"
#include "physics/Physics2D.h"

RigidBody2D::RigidBody2D(Quad* InQuad) 
{
    Object = InQuad;

    if(!Object->Collider)
    {
        //1. Create Body
        b2BodyDef BodyDef;
        BodyDef.type = b2BodyType::b2_dynamicBody;
        BodyDef.position.Set(Object->Position.x, Object->Position.y);

        Body = ServiceRegistry::GetInstance().GetPhysics()->CreateBody(&BodyDef);
    }
    else
    {
        Body = Object->Collider->Body;
        Body->SetType(b2BodyType::b2_dynamicBody);
    }

    glm::vec3 BodySize = InQuad->Scale;
    BodySize *= 0.5f;  //extent like

    b2PolygonShape Box;
    Box.SetAsBox(BodySize.x, BodySize.y);

    b2FixtureDef FixtureDef;
    FixtureDef.shape = &Box;
    FixtureDef.isSensor = false;
    FixtureDef.density = 1.f;        // Kg/m2   density = mass / volume

    FixtureDef.filter.categoryBits = 0;   //no collision
    FixtureDef.filter.maskBits = 0;       //no collision

    Fixture = Body->CreateFixture(&FixtureDef);
}

void RigidBody2D::AddForce(const glm::vec2& InForce)
{
    Body->ApplyForceToCenter(b2Vec2{InForce.x, InForce.y}, true);
}

void RigidBody2D::AddImpulse(const glm::vec2& InImpulse)
{
    Body->ApplyLinearImpulseToCenter(b2Vec2{InImpulse.x, InImpulse.y}, true);
}

void RigidBody2D::Update() 
{
    b2Vec2 B2Pos = Body->GetPosition();
    Object->Position.x = B2Pos.x;
    Object->Position.y = B2Pos.y;
}