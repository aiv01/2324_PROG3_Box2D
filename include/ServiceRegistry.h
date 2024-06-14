#pragma once

class ServiceRegistry 
{
public:
    static ServiceRegistry& GetInstance() 
    {
        static ServiceRegistry Instance{};
        return Instance;
    }

    void SetPhysics(class Physics2D* InPhysics) { Physics = InPhysics; }
    class Physics2D* GetPhysics() { return Physics; }

private:
    class Physics2D* Physics;
};