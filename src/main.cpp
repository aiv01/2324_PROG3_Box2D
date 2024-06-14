#include <iostream>
#include "OGLWindow.h"
#include "PlatformScene.h"
#include "ServiceRegistry.h"
#include "physics/Physics2D.h"

int main() {
	std::cout << "It' Working" << std::endl;

	OGLWindow* Win = new OGLWindow(800, 600, "OpenGL Window");
	
	float FixedDeltaTime = 0.016f;
	Physics2D Physics{glm::vec2{0, -9.81f}, FixedDeltaTime};

	ServiceRegistry::GetInstance().SetPhysics(&Physics);

	float TimeElapsed = 0.f;

	PlatformScene Scene{*Win};


	Scene.Start();
	// till Window is not in closing
	while (Win->IsOpened())
	{
		// update fps 1 sec
		TimeElapsed += Win->GetDeltaTime();
		if (TimeElapsed >= 1.f)
		{
			TimeElapsed -= 1.f;
			int Fps = 1.f / Win->GetDeltaTime();
			char Title[50];
			sprintf_s(Title, sizeof(Title), "OpenGL App | DeltaTime: %f - FPS: %d", Win->GetDeltaTime(), Fps);

			Win->SetTitle(Title);
		}

		static float FixedTimeElapsed = 0.f;
		FixedTimeElapsed += Win->GetDeltaTime();
		if (FixedTimeElapsed >= FixedDeltaTime) 
		{
			FixedTimeElapsed -= FixedDeltaTime;
			Scene.FixedUpdate();
			Physics.Step();
		}
	
		Scene.Update();
		Win->Update();
	}

	Scene.Destroy();
	delete Win;
	return 0;	
}

