#include"VertexBuffer.h"
#include"Renderer.h"
VertexBuffer::VertexBuffer(const void*data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID)); //create 1 buffer and signed to buffer var
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); //purpose of this buffer, blind this buffer to use gldrawarray; or mean choose this buffer to do thing (draw thing)
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const 
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
