#pragma once

#include <vector>
#include "renderer.h"

struct vertexBufferElement {
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  static unsigned int getSizeOfType(unsigned int type) {
    switch (type) {
      case GL_FLOAT:          return 4;
      case GL_UNSIGNED_INT:   return 4;
      case GL_UNSIGNED_BYTE:  return 1;
    }
    ASSERT(false);
    return false;
  }
};

class vertexBufferLayout {
  private:
    std::vector<vertexBufferElement> m_Elements;
    unsigned int m_Stride;

  public:
    vertexBufferLayout() : m_Stride(0) {};
    const std::vector<vertexBufferElement>& getElements() const;
    inline unsigned int getStride() const {return m_Stride; };
    template<typename T> void push(unsigned int);
};