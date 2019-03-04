#include "Robject.h"
#include "indexBuffer.h"

Robject::Robject(float vertecies[], unsigned int verteciesCount, unsigned int indecies[], unsigned int indeciesCount, vertexBufferLayout* layout) {
  Robject::vbo = new vertexBuffer(vertecies, sizeof(*vertecies) * verteciesCount);
  Robject::vblo = layout;
  Robject::ibo = new indexBuffer(indecies, indeciesCount);
  Robject::vao = new vertexArray;
  Robject::vao->addBuffer(*Robject::vbo, *Robject::vblo);
}

Robject::~Robject() {
  delete Robject::vao;
  delete Robject::vblo;
  delete Robject::vbo;
  delete Robject::ibo;
}

void Robject::draw(unsigned int type, int indecies_to_draw, int offset) {
  Robject::vao->bind();
  Robject::ibo->bind();
  GLCall(glDrawElements(type, indecies_to_draw, GL_UNSIGNED_INT, (void*)(offset * sizeof(unsigned int))));
}