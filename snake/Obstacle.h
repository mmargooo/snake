#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <glm/glm.hpp>

class Obstacle {
public:
	glm::vec3 position;
	Obstacle(glm::vec3 pos) {
		position = pos;
	}
};
#endif
