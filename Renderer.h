#pragma once
#include<iostream>
#include<GL/glew.h>
#include<GL/glfw3.h>	

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
using namespace std;
#define ASSERT(x) if (!(x)) __debugbreak(); //Tạo cái break point tại vị trí gây lỗi
#define GLCall(x) {GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))}

void GLClearError();
bool GLLogCall(const char* function, const char *file, int line);
class Renderer {
private:

public:
	void Clear();
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};