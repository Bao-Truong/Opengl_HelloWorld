#pragma once
#include "Renderer.h"
#include<GL/glew.h>
#include<vector>

using namespace std;

struct VertexBufferElement {
	unsigned int count;
	unsigned int type;
	int normalized;

	static unsigned int getTypeSize(unsigned int type) {
		switch (type) {
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		};
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout() : m_Stride(0) {};
	~VertexBufferLayout() {};

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ count, GL_FLOAT, GL_FALSE });
		m_Stride += count * VertexBufferElement::getTypeSize(GL_FLOAT);
	}
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
		m_Stride += count * VertexBufferElement::getTypeSize(GL_UNSIGNED_INT);
	}
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
		m_Stride += count * VertexBufferElement::getTypeSize(GL_UNSIGNED_BYTE);
	}
	inline const vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline const int GetStride() const { return m_Stride; }
};

