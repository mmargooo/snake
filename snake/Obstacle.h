#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <glm/glm.hpp>

class Obstacle {
public:
	float angle;
	glm::vec3 position;
	Obstacle(glm::vec3 pos) {
		position = pos;
		angle = 3.14 * (float)rand() / RAND_MAX;
	}
};
#endif
