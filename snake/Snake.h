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
	Snake() {
		elem.push_back(glm::vec3(0.0f, 1.0f, -1.0f));
		elem.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
		elem.push_back(glm::vec3(2.0f, 1.0f, -1.0f));
		elem.push_back(glm::vec3(3.0f, 1.0f, -1.0f));
	}
	void move() {
		if (!ateFood && !died) {
			int prevHead = head;

			// save tail position
			tailPos = elem[prevHead == 0 ? elem.size() - 1 : prevHead - 1];
			
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

		for (int i = 0; i < (*food).size(); i++) {
			if (elem[head]+nextHead == (*food)[i].position) {
				(*food).erase((*food).begin() + i);
				ateFood = true;
				elem.insert(elem.begin() + head, (elem[head] + nextHead));
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
		int tailId = head == 0 ? elem.size() - 1 : head - 1;
		if (i == tailId)
			return tailPos;
			//return elem[tailId] + (elem[tailId] - elem[tailId - 1 == -1 ? elem.size() - 1 : tailId - 1]);

		if (i == elem.size() - 1)
			return elem[0];
		else
			return elem[i + 1];

		/*if (i == head) {
			glm::vec3 t;
			if (direction == 'r') t = glm::vec3(1.0f, 0.0f, 0.0f);
			else if (direction == 'l') t = glm::vec3(-1.0f, 0.0f, 0.0f);
			else if (direction == 'u') t = glm::vec3(0.0f, 0.0f, -1.0f);
			else if (direction == 'd') t = glm::vec3(0.0f, 0.0f, 1.0f);
			return elem[head] + t;
		}

		if (i == elem.size()-1)
			return elem[0];
		else 
			return elem[i + 1];*/
	}
	glm::vec3 getHead() {
		return elem[head];
	}
	int getHeadId() {
		return head;
	}
};

#endif 
