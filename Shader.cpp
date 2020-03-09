#include "Shader.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "Renderer.h"

ShaderProgramSource Shader::ParseShader(const string &filepath) {
	ifstream stream(filepath);
	enum class ShaderType {
		None = -1, VERTEX = 0, FRAGMENT = 1
	};
	string line;
	stringstream ss[2];
	ShaderType type = ShaderType::None;

	while (getline(stream, line))
	{
		if (line.find("#shader") != string::npos)
		{
			if (line.find("vertex") != string::npos)
			{
				type = ShaderType::VERTEX;

			}
			else if (line.find("fragment") != string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << "\n";

		}
	}
	return{ ss[0].str(),ss[1].str() };
}
unsigned int Shader::CreateShader(const  string& vertexShader, const string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}
unsigned int Shader::CompileShader(unsigned int type, const string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	cout << src;
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	//error handling
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile" << type << " shader!" << endl;
		cout << message << endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}
Shader::Shader(const string &filepath)
	:m_Filepath(filepath), m_RendererID(0)
{
	ShaderProgramSource src = ParseShader(filepath);
	m_RendererID = CreateShader(src.VertexSource, src.FragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const string&name, int v0)
{
	GLCall(glUniform1i(GetUniformLocation(name), v0));
}

void Shader::SetUniform4f(const string&name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}


void Shader::SetUniformMat4f(const string &name, const glm::mat4& matrix)
{

	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE,&matrix[0][0])); //float array _ fv
}

int Shader::GetUniformLocation(const string &name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	int location;
	GLCall(location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		cout << "Warning: uniform " << name << " doesn't exist!" << endl;
	m_UniformLocationCache[name] = location;
	return location;
}
