////Project -> Propreties -> C/C++ -> General
////Additional include directories = > Add the \include(.h files)
////Linker->General->Addtional Library Directories->add the.lib files
////Linker->Input: Additional dependencies : call the extract name of the.lib files to use
////C/C++ -> Preprocessor -> add "GLEW_STATIC;" to preprocessor definition
//
//#include<GL/glew.h> // THIS NEED TO BE INCLUDE FIRST
//#include <GLFW/glfw3.h>
//
//#include<iostream>
//#include<string>
//#include<fstream>
//#include<sstream>
//#include "VertexBuffer.h"
//#include "IndexBuffer.h"
//#include "VertexBufferLayout.h"
//#include "VertexArray.h"
//
//using namespace std;
//
//#define ASSERT(x) if (!(x)) __debugbreak();
//#define GLCall(x) {GLClearError();\
//	x;\
//	ASSERT(GLLogCall(#x, __FILE__,__LINE__))	}
//
//static void GLClearError() {
//	while (glGetError() != GL_NO_ERROR); // clear all the error
//}
//static bool GLLogCall(const char* function, const char *file, int line) {
//	while (GLenum error = glGetError())
//	{
//		cout << "[Opengl error]: " << "( " << error << " ): " << function <<
//			" " << file << " inline: " << line << endl;
//		return false;
//	}
//	return true;
//}
//struct ShaderProgramSource {
//	string VertexSource;
//	string FragmentSource;
//};
//static ShaderProgramSource ParseShader(const string& filepath) {
//	ifstream stream(filepath);
//	enum class ShaderType {
//		None = -1, VERTEX = 0, FRAGMENT = 1
//	};
//	string line;
//	stringstream ss[2];
//	ShaderType type = ShaderType::None;
//
//	while (getline(stream, line))
//	{
//		if (line.find("#shader") != string::npos)
//		{
//			if (line.find("vertex") != string::npos)
//			{
//				type = ShaderType::VERTEX;
//
//			}
//			else if (line.find("fragment") != string::npos)
//			{
//				type = ShaderType::FRAGMENT;
//			}
//		}
//		else {
//			ss[(int)type] << line << "\n";
//
//		}
//	}
//	return{ ss[0].str(),ss[1].str() };
//}
//static unsigned int CompileShader(unsigned int type, const string& source) {
//	unsigned int id = glCreateShader(type);
//	const char* src = source.c_str();
//
//	GLCall(glShaderSource(id, 1, &src, nullptr));
//	GLCall(glCompileShader(id));
//
//	//error handling
//	int result;
//	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
//	if (result == GL_FALSE)
//	{
//		int length;
//		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//		char *message = new char[length];
//		glGetShaderInfoLog(id, length, &length, message);
//		cout << "Failed to compile" << type << " shader!" << endl;
//		cout << message << endl;
//		glDeleteShader(id);
//		return 0;
//	}
//
//	return id;
//}
//// create my own shader to use, not using the pre implementation shaders
//static unsigned int CreateShader(const  string& vertexShader, const string& fragmentShader) {
//	unsigned int program = glCreateProgram();
//	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//	GLCall(glAttachShader(program, vs));
//	GLCall(glAttachShader(program, fs));
//	GLCall(glLinkProgram(program));
//	GLCall(glValidateProgram(program));
//
//
//	GLCall(glDeleteShader(vs));
//	GLCall(glDeleteShader(fs));
//
//	return program;
//}
//void close_Program() {
//	exit(0);
//}
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	if (key == GLFW_KEY_E && action == GLFW_RELEASE)
//		exit(0);
//	const int xx = glfwGetKeyScancode(GLFW_KEY_X);
//	cout << scancode << endl;
//	cout << xx << endl;
//}
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
//	glfwSetKeyCallback(window, key_callback);
//	/* Make the window's context current */
//	glfwMakeContextCurrent(window);
//	glfwSwapInterval(1);
//	if (glewInit() != GLEW_OK) {
//		cout << "Error!" << endl;
//	}
//	else {
//		cout << glGetString(GL_VERSION) << endl;
//	}
//
//	//Square
//	float positions[] = {
//		-0.5f, -0.5f, //0
//		 0.5f, -0.5f, //1
//		 0.5f,  0.5f, //2
//		-0.5f,  0.5f, //3
//	};
//
//	unsigned int indices[]{
//		0,1,2,
//		2,3,0,
//	};
//
//	VertexArray va;
//	VertexBuffer vb(positions, 2 * 4 * sizeof(float));
//	VertexBufferLayout layout;
//	layout.Push<float>(2);
//	va.AddBuffer(vb, layout);
//
//	IndexBuffer ib(indices, 6);
//
//	ShaderProgramSource src = ParseShader("res/shader/Basic.shader");
//	cout << src.VertexSource << endl;
//	cout << "2nd Shader" << endl;
//	cout << src.FragmentSource << endl;
//	unsigned int shader = CreateShader(src.VertexSource, src.FragmentSource);
//	GLCall(glUseProgram(shader)); //Bind to use this program
//
//	int location = glGetUniformLocation(shader, "u_Color");
//	ASSERT(location != -1);
//	GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));
//
//	GLCall(glBindVertexArray(0));
//	GLCall(glUseProgram(0)); //Bind to use this program
//	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); //purpose of this buffer, blind this buffer to use gldrawarray; or mean choose this buffer to do thing (draw thing)
//	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); //purpose of this buffer, blind this buffer to use gldrawarray; or mean choose this buffer to do thing (draw thing)
//
//
//	float r = 0.0f;
//	float g = 1.0f;
//	float b = 0.0f;
//	float increment = 0.05f;
//	/* Loop until the user closes the window */
//	while (!glfwWindowShouldClose(window))
//	{
//		/* Render here */
//		GLCall(glClear(GL_COLOR_BUFFER_BIT));
//
//		GLCall(glUseProgram(shader)); //Bind to use this program
//		GLCall(glUniform4f(location, r, g, 0.8f, 1.0f));
//
//		va.Bind();
//		ib.Bind();
//
//		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);
//		//Drawing the Index, not the vertices
//		//count: number of index to be drawn
//		// type: type of the index buffer
//		// indices: do ta đã bind ibo cho GL_ELEMENT_ARRAY_BUFFER nên ko cần truyền nữa
//		if (r > 1.0f)
//			increment = -0.05f;
//		else if (r < 0.0f)
//			increment = 0.05f;
//		r += increment;
//		g -= increment;
//		//Error unsigned int -> int
//		//GLCall(glDrawElements(GL_TRIANGLES, 2 * 3, GL_INT, nullptr));
//
//
//		/* Swap front and back buffers */
//		GLCall(glfwSwapBuffers(window));
//
//		/* Poll for and process events */
//		GLCall(glfwPollEvents());
//	}
//	glDeleteProgram(shader);
//	glfwTerminate();
//	return 0;
//}
