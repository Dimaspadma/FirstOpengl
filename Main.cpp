#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// Vertice coordinates
// object is Equilateral triangle
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner	0
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner	1
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner		2
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner Left		3
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right		4
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down				5
};

GLuint indices[] =
{
	0,3,5, // lower left triangle
	3,2,4, // upper triangle
	5,4,1  // lower right triangle
};

int main()
{
	// TODO: Create window
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // version opengl 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // package core


	// Create a GLFWwindow object of 800 by 800 pixels, naming it "First Opengl"
	GLFWwindow* window = glfwCreateWindow(800, 800, "First Opengl", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the window
	// In this case the viewport goes from x=0, y=0, to x=800, y=800
	glViewport(0, 0, 800, 800);


	// Creates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generate Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generate Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLE primitive
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents(); // input events
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}