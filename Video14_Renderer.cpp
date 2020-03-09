////Project -> Propreties -> C/C++ -> General
////Additional include directories = > Add the \include(.h files)
////Linker->General->Addtional Library Directories->add the.lib files
////Linker->Input: Additional dependencies : call the extract name of the.lib files to use
////C/C++ -> Preprocessor -> add "GLEW_STATIC;" to preprocessor definition
//
//#include<GL/glew.h> // THIS NEED TO BE INCLUDE FIRST
//#include <GLFW/glfw3.h>
//#include<iostream>
//#include<string>
//#include<fstream>
//#include<sstream>
//#include "Renderer.h"
//#include "VertexBuffer.h"
//#include "IndexBuffer.h"
//#include "VertexArray.h"
//#include "Shader.h"
//#include "VertexBufferLayout.h"
//using namespace std;
//
//int main(void)
//{
//	GLFWwindow* window;
//
//	/* Initialize the library */
//	if (!glfwInit())
//		return -1;
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);;
//
//
//	/* Create a windowed mode window and its OpenGL context */
//	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//	if (!window)
//	{
//		glfwTerminate();
//		return -1;
//	}
//
//	/* Make the window's context current */
//	glfwMakeContextCurrent(window);
//	glfwSwapInterval(3);
//	if (glewInit() != GLEW_OK) {
//		cout << "Error!" << endl;
//	}
//	else {
//		cout << glGetString(GL_VERSION) << endl;
//	}
//
//	{
//		//Square
//		float positions[] = {
//			-0.5f, -0.5f, //0
//			 0.5f, -0.5f, //1
//			 0.5f,  0.5f, //2
//			-0.5f,  0.5f, //3
//		};
//
//		unsigned int indices[]{
//			0,1,2,
//			2,3,0,
//		};
//
//		VertexArray va;
//		VertexBuffer vb(positions, 4 * 2 * sizeof(float));
//		VertexBufferLayout layout;
//		layout.Push<float>(2);
//		va.AddBuffer(vb, layout);
//
//		IndexBuffer ib(indices, 3 * 2);
//
//		Shader shader("res/shader/Basic.shader");
//		shader.Bind();
//
//		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
//
//		va.Unbind();
//		shader.Unbind();
//		vb.Unbind();
//		ib.Unbind();
//
//		Renderer renderer;
//
//		float r = 0.0f;
//		float increment = 0.05f;
//		/* Loop until the user closes the window */
//		while (!glfwWindowShouldClose(window))
//		{
//			/* Render here */
//			renderer.Clear();
//
//			shader.Bind();
//			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
//
//			renderer.Draw(va, ib, shader);
//		
//			if (r > 1.0f)
//				increment = -0.05f;
//			else if (r < 0.0f)
//				increment = 0.05f;
//			r += increment;
//
//			/* Swap front and back buffers */
//			GLCall(glfwSwapBuffers(window));
//
//			/* Poll for and process events */
//			GLCall(glfwPollEvents());
//		}
//	}
//	glfwTerminate();
//	return 0;
//}
