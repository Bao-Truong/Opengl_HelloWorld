#include"IndexBuffer.h"
#include"Renderer.h"
IndexBuffer::IndexBuffer(const unsigned int*data, unsigned int count)
	:m_Count(count)
{
	GLCall(glGenBuffers(1, &m_RendererID)); //create 1 buffer and signed to buffer var
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); //purpose of this buffer, blind this buffer to use gldrawarray; or mean choose this buffer to do thing (draw thing)
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind()const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
