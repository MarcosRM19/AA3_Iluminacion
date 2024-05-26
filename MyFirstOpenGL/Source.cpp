#include "ProgramManager.h"
#include "GLManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"

void main()
{
	// Definir semillas del rand según el tiempo
	srand(static_cast<unsigned int>(time(NULL)));

	GL_MANAGER.WindowsConfiguration();
	// Permitimos a GLEW usar funcionalidades experimentales
	glewExperimental = GL_TRUE;
	GL_MANAGER.ActivateBackCulling();

	// Inicializamos GLEW y controlamos errores
	if (glewInit() == GLEW_OK)
	{
		// Definimos color para limpiar el buffer de color
		glClearColor(0.f, 0.6f, 1.f, 1.f);
		// Definimos modo de dibujo para cada cara
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Compilar shaders
		PROGRAM_MANAGER.PushProgram("MyFirstVertexShader.glsl", "MyFirstGeometryShader.glsl", "MyFirstFragmentShader.glsl");
		PROGRAM_MANAGER.PushProgram("MyFirstVertexShader.glsl", "MyFirstGeometryShader.glsl", "PrimitiveFragmentShader.glsl");

		// Declarar instancia de GameObject	
		OBJECT_MANAGER.CreateSpwanPoint();
		OBJECT_MANAGER.CreateObjects();

		// Generamos el game loop
		while (!glfwWindowShouldClose(GL_MANAGER.window))
		{
			// Pulleamos los eventos (botones, teclas, mouse...)
			glfwPollEvents();
			// Limpiamos los buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			TIME_MANAGER.Update();

			OBJECT_MANAGER.Update(TIME_MANAGER.GetDeltaTime());

			// Cambiamos buffers
			glFlush();
			glfwSwapBuffers(GL_MANAGER.window);
		}
		// Desactivar y eliminar programa
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