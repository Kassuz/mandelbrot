#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Timer.h"
#include "Shader.h"

const unsigned int SCREEN_WIDTH  = 1400;
const unsigned int SCREEN_HEIGHT = 1400;
const float PI = 3.14159265359f;
const float TWO_PI = 2.0f * 3.14159265359f;

float a = 0.0f;
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP)
	{
		a += 0.01f;
		if (a > TWO_PI)
			a -= TWO_PI;
	}
	
	if (key == GLFW_KEY_DOWN)
	{
		a -= 0.01f;
		if (a < 0.0f)
			a += TWO_PI;
	}
}
// void MouseCallback(GLFWwindow* window, double xpos, double ypos);
// void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

Shader* LoadShaderFromFile(const std::string& vertex, const std::string& fragment)
{
	// 1. retrieve shader code from filepath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		vShaderFile.open(vertex);
		std::stringstream vShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "VERTEX SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        // std::cout << strerror(errno) << std::endl;
		return nullptr;
	}

    try
	{
		fShaderFile.open(fragment);
		std::stringstream fShaderStream;
		fShaderStream << fShaderFile.rdbuf();
		fShaderFile.close();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "FRAGMENT SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return nullptr;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	Shader* s = new Shader;
	s->Compile(vShaderCode, fShaderCode);
	return s;
}

int main(int argc, char* argv[])
{
	// ---------------------------------------
	// -     Init GLFW and GLAD (OpenGL)     -
	// ---------------------------------------

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mandelbrot", NULL, NULL);

	if (window == NULL)
	{
		// Debug::LogError("Failed to create window!");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);


	// glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetKeyCallback(window, KeyCallback);
	// glfwSetMouseButtonCallback(window, MouseButtonCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		// Debug::LogError("Failed to initialize GLAD");
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


    // --------------------------------
	// -        VBOS and stuff        -
	// --------------------------------

    GLuint VBO, VAO;
	GLfloat vertices[] = {
		// Pos      // Tex
	   -1.0f,  1.0f, 0.0f, 1.0f,
	   -1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f,

		1.0f,  1.0f, 1.0f, 1.0f,
	   -1.0f,  1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
    // Shader* shader = LoadShaderFromFile("Vertex.vert", "Fragment.frag");
    Shader* shader = LoadShaderFromFile("Vertex.vert", "JuliaFrag.frag");
    if (shader == nullptr)
    {
        // shader = LoadShaderFromFile("bin/Vertex.vert", "bin/Fragment.frag"); // Purkka vs code build taskeihin, koska tässä hakee eri paikasta tiedostoja
        shader = LoadShaderFromFile("bin/Vertex.vert", "bin/JuliaFrag.frag"); // Purkka vs code build taskeihin, koska tässä hakee eri paikasta tiedostoja
        if (shader == nullptr)
        {
            system("pause");
            return 1;
        }
    }
    shader->Use();
    
    // -------------------------------
	// -          Main loop          -
	// -------------------------------

	while (!glfwWindowShouldClose(window))
	{
        Timer::Update();
		// Rendering
		glClearColor(0.35f, 0.35f, 0.35f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model;
		// model = glm::scale(model, glm::vec3(1.5f));
        // model = glm::translate(model, glm::vec3(-1.22f, 0.145f, 0.0f));
        // glm::mat4 scaleMat;
        // glm::vec3 scale((Timer::GetTime() * 0.1f));
        // scaleMat = glm::scale(scaleMat, scale);
        // model *= glm::inverse(scaleMat);
        shader->SetMat4("model", model);

		float a = std::fmod(Timer::GetTime() / 5.0f, 2.0f * glm::pi<float>());
		float sin = std::sin(a);
		float cos = std::cos(a);
		shader->SetVec2("c", glm::vec2(cos * 0.7885f, sin * 0.7885f));
		shader->SetFloat("time", Timer::GetTime());

        glDrawArrays(GL_TRIANGLES, 0, 6);

		// Swap buffers
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
    
    // Delete shader
    delete shader;

	glfwTerminate();
	return 0;
}