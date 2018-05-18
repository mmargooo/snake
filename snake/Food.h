#ifndef FOOD_H
#define FOOD_H

#include <glm/glm.hpp>

class Food {
public:
	glm::vec3 position;
	Food(glm::vec3 pos) {
		position = pos;
	}
};
#endif
