# include <stdio.h>
# include "../include/scop.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
} 

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, TRUE);
	}
}

int init(t_scop *scop)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	if (!(scop->win = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL)))
	{
		fprintf(stderr,"Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	return (1);
}

int main()
{
	t_scop	scop;
	//GLFWwindow* window;
	if (!init(&scop))
	{
		return(-1);
	}
	// glfwInit();
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);




	glfwMakeContextCurrent(scop.win);

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(scop.win, framebuffer_size_callback);


	printf("Hello World\n");
	while(!glfwWindowShouldClose(scop.win))
	{
		processInput(scop.win);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glfwPollEvents();    
		glfwSwapBuffers(scop.win);
	}
	glfwTerminate();
	return 0;
}