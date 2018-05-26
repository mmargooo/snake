#ifndef FOOD_H
#define FOOD_H

#include <glm/glm.hpp>

class Food {
public:
	glm::vec3 position;
	float angle;
	Food(glm::vec3 pos) {
		position = pos;
		angle = 3.14 * (float)rand() / RAND_MAX;
	}
};
#endif
