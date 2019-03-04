#pragma once
#include "renderer.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"

class Robject {
  private:
    vertexBuffer* vbo;
    vertexArray* vao;
    vertexBufferLayout* vblo;
    indexBuffer* ibo;

  public:
    Robject(float vertecies[], unsigned int verteciesCount, unsigned int indecies[], unsigned int indeciesCount, vertexBufferLayout* layout);
    ~Robject();
    void draw(unsigned int type, int indecies_to_draw, int offset);
};