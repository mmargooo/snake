#ifndef  SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "Food.h"

class Snake {
private:
	char direction = 'u';
	int head = 0;
	bool ateFood = false;
	bool died = false;
	glm::vec3 tailPos;
public:
	std::vector<glm::vec3> elem;
	std::vector<glm::vec3> prevElem;
	Snake() {
		elem.push_back(glm::vec3(0.0f, 1.0f, -1.0f));
		elem.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
		elem.push_back(glm::vec3(2.0f, 1.0f, -1.0f));
		elem.push_back(glm::vec3(3.0f, 1.0f, -1.0f));

		for (int i = 0; i < elem.size(); i++) {
			prevElem.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		}
	}
	void move() {
		if (!ateFood && !died) {
			int prevHead = head;
			
			for (int i = 0; i < elem.size(); i++) {
				prevElem[i] = elem[i == elem.size()-1 ? 0 : i+1];
			}

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
	void changeDirection(bool keys[4]) {
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
	}
	void checkCollision(std::vector<Food> * food) {
		glm::vec3 nextHead;
		if (direction == 'r') nextHead = glm::vec3(1.0f, 0.0f, 0.0f);
		else if (direction == 'l') nextHead = glm::vec3(-1.0f, 0.0f, 0.0f);
		else if (direction == 'u') nextHead = glm::vec3(0.0f, 0.0f, -1.0f);
		else if (direction == 'd') nextHead = glm::vec3(0.0f, 0.0f, 1.0f);

		glm::vec3 headPos = elem[head] + nextHead;
		for (int i = 0; i < (*food).size(); i++) {
			glm::vec3 pos = (*food)[i].position;
			if (headPos.x == pos.x && headPos.z == pos.z) {
				(*food).erase((*food).begin() + i);
				ateFood = true;
				elem.insert(elem.begin() + head, (elem[head] + nextHead));
				prevElem.push_back((elem[head] - nextHead));
			}
		}

		// check collision with obstacles
	}
	char getDirection() {
		return direction;
	}
	glm::vec3 getElem(int i) {
		return elem[i];
	}
	glm::vec3 getPrevElem(int i) {
		return prevElem[i];
	}
	glm::vec3 getHead() {
		return elem[head];
	}
};

#endif 
