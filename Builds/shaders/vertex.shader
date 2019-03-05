#version 330 core

layout(location = 0) in vec4 position;
uniform mat4 m_3d;

void main() {
  gl_Position = m_3d * position;
};