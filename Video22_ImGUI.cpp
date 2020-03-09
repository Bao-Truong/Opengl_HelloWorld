//Project -> Propreties -> C/C++ -> General
//Additional include directories = > Add the \include(.h files)
//Linker->General->Addtional Library Directories->add the.lib files
//Linker->Input: Additional dependencies : call the extract name of the.lib files to use
//C/C++ -> Preprocessor -> add "GLEW_STATIC;" to preprocessor definition

#include<GL/glew.h> // THIS NEED TO BE INCLUDE FIRST
#include <GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "iamgui/imgui.h"
#include "iamgui/imgui_impl_glfw_gl3.h"
using namespace std;

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);;


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(3);
	if (glewInit() != GLEW_OK) {
		cout << "Error!" << endl;
	}
	else {
		cout << glGetString(GL_VERSION) << endl;
	}


	//Square
	float positions[] = {
		100.0f, 100.0f,  0.0f, 0.0f,//0
		200.0f, 100.0f,  1.0f, 0.0f, //1
		200.0f, 200.0f,  1.0f, 1.0f,//2
		100.0f, 200.0f,  0.0f, 1.0f//3
	};

	unsigned int indices[]{
		0,1,2,
		2,3,0,
	};
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA)); //Use when let 2 textures merge together

	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 3 * 2);
	glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 480.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 00, 0)); //move camera to the right 100 units
																		//-> meaning that objec goto the left 100 units
	
	cout << proj[0][0] << endl;
	Shader shader("res/shader/Basic.shader");
	shader.Bind();

	shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);


	Texture texture("res/Textures/unnamed.png");
	texture.Bind(0);
	shader.SetUniform1i("u_Texture", 0);

	va.Unbind();
	shader.Unbind();
	vb.Unbind();
	ib.Unbind();

	Renderer renderer;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
	
	glm::vec3 translation(200, 200, 0);
	
	float r = 0.0f;
	float increment = 0.05f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		/* Render here */
		renderer.Clear(); //clear COLOR_BUFFER_BIT
		
		
		ImGui_ImplGlfwGL3_NewFrame();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mvp = proj * view  * model;

		shader.Bind();
		shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
		shader.SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(va, ib, shader);

		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;
		r += increment;
		{
		        // Display some text (you can use a format string too)
			ImGui::SliderFloat("TranslationX", &translation.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
			ImGui::SliderFloat("TranslationY", &translation.y, 0.0f, 480.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		GLCall(glfwSwapBuffers(window));

		/* Poll for and process events */
		GLCall(glfwPollEvents());
	}
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}