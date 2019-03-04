#pragma once

#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class vertexArray {
  private:
    unsigned int m_RendererID;

  public:
    vertexArray();
    ~vertexArray();

    void addBuffer(const vertexBuffer&, const vertexBufferLayout&);
    void bind() const;
    void unbind() const;
};