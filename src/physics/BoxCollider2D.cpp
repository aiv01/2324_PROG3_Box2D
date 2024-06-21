#include <box2d/box2d.h>
#include "physics/BoxCollider2D.h"
#include "physics/RigidBody2D.h"
#include "Quad.h"
#include "ServiceRegistry.h"
#include "physics/Physics2D.h"



BoxCollider2D::BoxCollider2D(Quad* InQuad) 
{
    Object = InQuad;

    if(!Object->RigidBody)
    {
        //1. Create Body
        b2BodyDef BodyDef;
        BodyDef.type = b2BodyType::b2_staticBody;
        BodyDef.position.Set(Object->Position.x, Object->Position.y);

        Body = ServiceRegistry::GetInstance().GetPhysics()->CreateBody(&BodyDef);
    }
    else
    {
        Body = Object->RigidBody->Body;
    }

    glm::vec3 BodySize = InQuad->Scale;
    BodySize *= 0.5f;  //extent like

    b2PolygonShape Box;
    Box.SetAsBox(BodySize.x - Box.m_radius, BodySize.y - Box.m_radius);

    b2FixtureDef FixtureDef;
    FixtureDef.shape = &Box;
    FixtureDef.isSensor = false;

    Fixture = Body->CreateFixture(&FixtureDef);
}