#pragma once
#include<string>
#include<unordered_map>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> 
using namespace std;
struct ShaderProgramSource {
	string VertexSource;
	string FragmentSource;
};

class Shader
{
private:
	string m_Filepath;
	unsigned int m_RendererID;
	unordered_map<string, int> m_UniformLocationCache;
public:
	Shader(const string &filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set uniform
	void SetUniform1i(const string&name, int v0);
	void SetUniform4f(const string&name, float v0,float v1, float v2, float v3);
	void SetUniformMat4f(const string &name, const glm::mat4& matrix);

private:
	static ShaderProgramSource ParseShader(const string &filepath);
	static unsigned int CompileShader(unsigned int type, const string& source);
	static unsigned int CreateShader(const  string& vertexShader, const string& fragmentShader);
	 int GetUniformLocation(const string &name);
};

