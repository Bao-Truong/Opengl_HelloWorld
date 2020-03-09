#include "VertexArray.h"
#include "VertexBufferLayout.h"
VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RenderID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteBuffers(1,&m_RenderID));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	const auto& elements = layout.GetElements();

	unsigned int offset = 0;
	
	for (int i = 0; i < elements.size(); i++) {

		const auto &element = elements[i];
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),(const void*) offset));
		GLCall(glEnableVertexAttribArray(i));
		cout << "Size: " << elements.size() << endl;
		cout << "stride: " << layout.GetStride() << endl;
		cout << "offset: " << offset << endl;
		
		offset = element.count * VertexBufferElement::getTypeSize(element.type);
		
	}

}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RenderID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
