#pragma once

#include "glm/glm.hpp"

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;

	Vertex() {}
	Vertex(glm::vec3 pos, glm::vec2 texCoord = glm::vec2(0.0f, 0.0f), glm::vec3 normal = glm::vec3(0.0f, 0.0f, 0.0f)) :
		pos(pos), texCoord(texCoord), normal(normal){}
};