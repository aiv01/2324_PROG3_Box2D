#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "OGLWindow.h"
#include "Common.h"

OGLWindow::OGLWindow(int InWidth, int InHeight, const std::string& InTitle)
 : Width(InWidth), Height(InHeight), Title(InTitle)
{
    DeltaTime = 0.f;
    LastTime = 0.f;
	
	DIE_ON_ERROR(glfwInit(), "Failed to initialize GLFW");

	// hints to init window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	RawWindow = glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL);
	DIE_ON_NULL(RawWindow, "Error: Opening Window");

    // redirect all commands to window
	glfwMakeContextCurrent(RawWindow);

    // load GLAD
	DIE_ON_ERROR(gladLoadGL(), "Error: GLAD Wrapper");
}

OGLWindow::~OGLWindow()
{
    glfwDestroyWindow(RawWindow);
    glfwTerminate();
}

void OGLWindow::SetTitle(const std::string& InTitle)
{
    glfwSetWindowTitle(RawWindow, InTitle.c_str());
}

float OGLWindow::GetDeltaTime() const
{
    return DeltaTime;
}

bool OGLWindow::IsOpened() const
{
    return !glfwWindowShouldClose(RawWindow);
}

void OGLWindow::Update()
{
    float CurrentTime = glfwGetTime();
	DeltaTime = CurrentTime - LastTime;
	LastTime = CurrentTime;
    
    // swap buffers with all draw operations
	glfwSwapBuffers(RawWindow);
	// poll events
	glfwPollEvents();
}

void OGLWindow::PrintInfo() const
{
	printf("GL VERSION: %s\n", glGetString(GL_VERSION));
	printf("GL RENDERER: %s\n", glGetString(GL_RENDERER));
	printf("GL VENDOR: %s\n", glGetString(GL_VENDOR));
	printf("GLSL VERSION: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

glm::vec2 OGLWindow::MousePosition() const 
{	
	//https://www.glfw.org/docs/3.1/group__input.html#ga01d37b6c40133676b9cea60ca1d7c0cc
	//(0,0) e' l'angolo in alto a sinistra della finistra
	//(w,h) e' l'angolo in basso a destra della finestra
	//Fuori della finestra i valori x e y diventano negativi
	double XPos, YPos;
	glfwGetCursorPos(RawWindow, &XPos, &YPos);
	return glm::vec2((int)XPos, (int)YPos);
}

glm::vec2 OGLWindow::Size() const 
{	
	return glm::vec2(Width, Height);
}

bool OGLWindow::IsKeyPressed(Key InKey) const
{
	int state = glfwGetKey(RawWindow, (int)InKey);
	return state == GLFW_PRESS;
}

