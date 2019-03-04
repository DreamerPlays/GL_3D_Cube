#include "vertexBufferLayout.h"
#include <GL/glew.h>

template<typename T> void vertexBufferLayout::push (unsigned int count) {
  //static_assert(false);
}
template<> void vertexBufferLayout::push<float> (unsigned int count) {
  vertexBufferLayout::m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
  m_Stride += count * vertexBufferElement::getSizeOfType(GL_FLOAT);
}

template<> void vertexBufferLayout::push<unsigned int> (unsigned int count) {
  vertexBufferLayout::m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  m_Stride += count * vertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template<> void vertexBufferLayout::push<unsigned char> (unsigned int count) {
  vertexBufferLayout::m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
  m_Stride += count * vertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}

const std::vector<vertexBufferElement>& vertexBufferLayout::getElements() const {
  return vertexBufferLayout::m_Elements;
}