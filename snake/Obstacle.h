#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <glm/glm.hpp>

class Obstacle {
public:
	float angle;
	int type;
	glm::vec3 position;
	Obstacle(int t, glm::vec3 pos) {
		type = t;
		position = pos;
		angle = 3.14 * (float)rand() / RAND_MAX;
	}
};
#endif
