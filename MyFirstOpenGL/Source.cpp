#include "ProgramManager.h"
#include "GLManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"
#include "InputManager.h"

void main()
{
	//Define rand seeds according to time
	srand(static_cast<unsigned int>(time(NULL)));

	GL_MANAGER.WindowsConfiguration();

	//We allow GLEW to use experimental features
	glewExperimental = GL_TRUE;
	GL_MANAGER.ActivateBackCulling();

	// Inicializamos GLEW y controlamos errores
	if (glewInit() == GLEW_OK)
	{
		//We define color to clear the color buffer
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//We define drawing mode for each face
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Compile shaders
		PROGRAM_MANAGER.PushProgram("MyFirstVertexShader.glsl", "MyFirstGeometryShader.glsl", "MyFirstFragmentShader.glsl");
		PROGRAM_MANAGER.PushProgram("MyFirstVertexShader.glsl", "MyFirstGeometryShader.glsl", "FloorFragmentShader.glsl");
		PROGRAM_MANAGER.PushProgram("MyFirstVertexShader.glsl", "MyFirstGeometryShader.glsl", "PrimitiveFragmentShader.glsl");

		//Declare GameObject instance
		OBJECT_MANAGER.CreateSpwanPoint();
		OBJECT_MANAGER.CreateObjects();

		INPUT_MANAGER.registerCallbacks(GL_MANAGER.window);

		//Generate gameloop
		while (!glfwWindowShouldClose(GL_MANAGER.window))
		{
			//We pull the events(buttons, keys, mouse...)
			glfwPollEvents();

			//We clean the buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			//Call Updates
			TIME_MANAGER.Update();
			OBJECT_MANAGER.Update(TIME_MANAGER.GetDeltaTime());

			//We change buffers
			glFlush();
			glfwSwapBuffers(GL_MANAGER.window);
		}
		//Deactivate and delete program
		glUseProgram(0);
		PROGRAM_MANAGER.DeleteAllPrograms();
	}
	else
	{
		std::cout << "Ha petao." << std::endl;
		glfwTerminate();
	}
	//Finalizamos GLFW
	glfwTerminate();
}