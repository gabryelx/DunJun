#include <iostream>
#include <Dunjun/Common.hpp>
#include <GLFW/glfw3.h>

GLOBAL const int g_windowWidth = 854;
GLOBAL const int g_windowHeight = 480;

int main(int argc, char** argv)
{
	GLFWwindow* window;

	//initialize the library
	if (!glfwInit())
	{
		return EXIT_FAILURE;
	}

	//create a windowed mode and its OpenGL
	window = glfwCreateWindow(854, 480, "Dunjun", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	//make the window's context current
	glfwMakeContextCurrent(window);

	//loop until the use closes the window
	bool running = true;
	bool fullscreen = false;
	while (running)
	{
		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//swap front and back buffers
		glfwSwapBuffers(window);

		//Poll for and process events
		glfwPollEvents();

		if ((glfwWindowShouldClose(window)) || (glfwGetKey(window, GLFW_KEY_ESCAPE)))
		{
			running = false;
		}

		if (glfwGetKey(window, GLFW_KEY_P))
		{
			fullscreen = !fullscreen;
			GLFWwindow * newWindow;

			if (fullscreen)
			{	
				int count;
				const GLFWvidmode* modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);

				newWindow = glfwCreateWindow(modes[count -1].width, modes[count -1].height, "Dunjun", glfwGetPrimaryMonitor(), window);
			}
			else
			{
				newWindow = glfwCreateWindow(g_windowWidth, g_windowHeight, "Dunjun", nullptr, window);					
			}
			glfwDestroyWindow(window);
			window = newWindow;
			glfwMakeContextCurrent(window);
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}