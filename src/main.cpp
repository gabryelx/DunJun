#include <iostream>
#include <Dunjun/Common.hpp>
#include <gl/glew.h>
#include <GLFW/glfw3.h>

GLOBAL const int g_windowWidth = 854;
GLOBAL const int g_windowHeight = 480;

void glfwHints()
{
	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);
}

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

	glewInit();

	float vertices[] = {
		0.0f, 0.5f,  // vertex 1
		-0.5f, -0.5f, // vertex 2
		0.5f, -0.5f  //vertex 3
	};

	GLuint vbo;  //vertex buffer object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	const char * vertexShaderText = {
		"#version 120\n"
		"\n"
		"attribute vec2 position;"
		"void main()"
		"{"
		"   gl_Position = vec4(position, 0.0, 1.0);"
		"}"
	};

	const char * fragmentShaderText{
		"#version 120\n"
		"\n"
		"void main()"
		"{"
		"   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
		"}"
	};

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader); 

	glBindAttribLocation(shaderProgram, 0, "position");

	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);



	//loop until the use closes the window
	bool running = true;
	bool fullscreen = false;
	while (running)
	{
		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw things
		{
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glDisableVertexAttribArray(0);
		}

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