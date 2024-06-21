#include "physics/Physics2DContactListener.h"
#include "Quad.h"

void Physics2DContactListener::BeginContact(b2Contact *contact)
{
    b2FixtureUserData &UserDataA = contact->GetFixtureA()->GetUserData();
    b2FixtureUserData &UserDataB = contact->GetFixtureB()->GetUserData();

    if (UserDataA.pointer == 0 || UserDataB.pointer == 0)
    {
        return;
    }

    CollisionCallBack* CBA = reinterpret_cast<CollisionCallBack*>(UserDataA.pointer);
    CollisionCallBack* CBB = reinterpret_cast<CollisionCallBack*>(UserDataB.pointer);
    
    CBA->OnEnter(CBB->Object);
    CBB->OnEnter(CBA->Object);

}

void Physics2DContactListener::EndContact (b2Contact *contact)
{

}
