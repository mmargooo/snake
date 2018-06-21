#ifndef  SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "Food.h"
#include "Obstacle.h"

class Snake {
private:
	char direction = 'u';
	int head = 0;
	bool ateFood = false;
	bool died = false;
	glm::vec3 tailPos;
public:
	std::vector<glm::vec3> elem;
	Snake() {
		elem.push_back(glm::vec3(0.0f, 1.0f, -1.0f));
		elem.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
		elem.push_back(glm::vec3(2.0f, 1.0f, -1.0f));
		elem.push_back(glm::vec3(3.0f, 1.0f, -1.0f));
	}
	void move() {
		if (!ateFood && !died) {
			int prevHead = head;

			head--;

			if (head < 0) {
				head = elem.size() - 1;
			}

			glm::vec3 t;
			if (direction == 'r') t = glm::vec3(1.0f, 0.0f, 0.0f);
			else if (direction == 'l') t = glm::vec3(-1.0f, 0.0f, 0.0f);
			else if (direction == 'u') t = glm::vec3(0.0f, 0.0f, -1.0f);
			else if (direction == 'd') t = glm::vec3(0.0f, 0.0f, 1.0f);
			elem[head] = elem[prevHead] + t;			

			// check if ate itself
			for (int i = 0; i < elem.size(); i++) {
				if (i != head && elem[head] == elem[i])
					died = true;
			}
		}
		else {
			ateFood = false;
		}
		
	}
	void changeDirection(bool * keys) {
		if (keys[0]) {
			if (direction == 'u' || direction == 'd') direction = 'l';
		}
		else if (keys[1]) {
			if (direction == 'l' || direction == 'r') direction = 'u';
		}
		else if (keys[2]) {
			if (direction == 'u' || direction == 'd') direction = 'r';
		}
		else if (keys[3]) {
			if (direction == 'l' || direction == 'r') direction = 'd';
		}
		else if (keys[4] && died) {
			died = false;
			elem.clear();
			head = 0;
			direction = 'u';
			elem.push_back(glm::vec3(0.0f, 1.0f, -1.0f));
			elem.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
			elem.push_back(glm::vec3(2.0f, 1.0f, -1.0f));
			elem.push_back(glm::vec3(3.0f, 1.0f, -1.0f));
		}
	}
	void checkCollision(float mapRadius, std::vector<Food> * food, std::vector<Obstacle> * obstacle, int * numOfFood) {
		glm::vec3 nextHead;
		if (direction == 'r') nextHead = glm::vec3(1.0f, 0.0f, 0.0f);
		else if (direction == 'l') nextHead = glm::vec3(-1.0f, 0.0f, 0.0f);
		else if (direction == 'u') nextHead = glm::vec3(0.0f, 0.0f, -1.0f);
		else if (direction == 'd') nextHead = glm::vec3(0.0f, 0.0f, 1.0f);

		glm::vec3 headPos = elem[head] + nextHead;
		// check outside of the map
		if (headPos.x > mapRadius || headPos.x < -mapRadius || headPos.z > mapRadius || headPos.z < -mapRadius)
			died = true;

		// check collision with food
		for (int i = 0; i < (*food).size(); i++) {
			glm::vec3 pos = (*food)[i].position;
			if (headPos.x == pos.x && headPos.z == pos.z) {
				(*food).erase((*food).begin() + i);
				ateFood = true;
				elem.insert(elem.begin() + head, (elem[head] + nextHead));
				(*numOfFood)--;
			}
		}

		// check collision with obstacles
		for (int i = 0; i < (*obstacle).size(); i++) {
			glm::vec3 pos = (*obstacle)[i].position;
			if (headPos.x == pos.x && headPos.z == pos.z) {
				died = true;
			}
		}

	}
	char getDirection() {
		return direction;
	}
	glm::vec3 getElem(int i) {
		return elem[i];
	}
	glm::vec3 getHead() {
		return elem[head];
	}
	int getHeadIndex() {
		return head;
	}
	bool getDied() {
		return died;
	}
};

#endif 
