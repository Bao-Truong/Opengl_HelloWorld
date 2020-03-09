#include"Renderer.h"
#include<iostream>
using namespace std;
void GLClearError() {
	while (glGetError() != GL_NO_ERROR); // clear all the error
}
bool GLLogCall(const char* function, const char *file, int line) {
	while (GLenum error = glGetError())
	{
		cout << "[Opengl error]: " << "( " << error << " ): " << function <<
			" " << file << " inline: " << line << endl;
		return false;
	}
	return true;
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();	
	va.Bind();	
	ib.Bind(); //purpose of this buffer, blind this buffer to use gldrawarray; or mean choose this buffer to do thing (draw thing)

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr); // draw base on the index

}
