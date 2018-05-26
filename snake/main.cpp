#include <iostream>
#define GLEW_STATIC
#include <gl/glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/functions.hpp>
#include <time.h>

#include "Shader.h"
#include "Snake.h"
#include "Food.h"
#include "Obstacle.h"
#include "lodepng.h"

GLfloat cube[] =
{
	0.5f,-0.5f,-0.5f,1.0f,
	-0.5f, 0.5f,-0.5f,1.0f,
	-0.5f,-0.5f,-0.5f,1.0f,

	0.5f,-0.5f,-0.5f,1.0f,
	0.5f, 0.5f,-0.5f,1.0f,
	-0.5f, 0.5f,-0.5f,1.0f,


	-0.5f,-0.5f, 0.5f,1.0f,
	0.5f, 0.5f, 0.5f,1.0f,
	0.5f,-0.5f, 0.5f,1.0f,

	-0.5f,-0.5f, 0.5f,1.0f,
	-0.5f, 0.5f, 0.5f,1.0f,
	0.5f, 0.5f, 0.5f,1.0f,

	0.5f,-0.5f, 0.5f,1.0f,
	0.5f, 0.5f,-0.5f,1.0f,
	0.5f,-0.5f,-0.5f,1.0f,

	0.5f,-0.5f, 0.5f,1.0f,
	0.5f, 0.5f, 0.5f,1.0f,
	0.5f, 0.5f,-0.5f,1.0f,

	-0.5f,-0.5f,-0.5f,1.0f,
	-0.5f, 0.5f, 0.5f,1.0f,
	-0.5f,-0.5f, 0.5f,1.0f,

	-0.5f,-0.5f,-0.5f,1.0f,
	-0.5f, 0.5f,-0.5f,1.0f,
	-0.5f, 0.5f, 0.5f,1.0f,

	-0.5f,-0.5f,-0.5f,1.0f,
	0.5f,-0.5f, 0.5f,1.0f,
	0.5f,-0.5f,-0.5f,1.0f,

	-0.5f,-0.5f,-0.5f,1.0f,
	-0.5f,-0.5f, 0.5f,1.0f,
	0.5f,-0.5f, 0.5f,1.0f,

	-0.5f, 0.5f, 0.5f,1.0f,
	0.5f, 0.5f,-0.5f,1.0f,
	0.5f, 0.5f, 0.5f,1.0f,

	-0.5f, 0.5f, 0.5f,1.0f,
	-0.5f, 0.5f,-0.5f,1.0f,
	0.5f, 0.5f,-0.5f,1.0f,
};
GLfloat cube_texture[] =
{
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
};
GLfloat cube_normals[] =
{
	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,

	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,

	0.0f, 0.0f, 1.0f,0.0f,
	0.0f, 0.0f, 1.0f,0.0f,
	0.0f, 0.0f, 1.0f,0.0f,

	0.0f, 0.0f, 1.0f,0.0f,
	0.0f, 0.0f, 1.0f,0.0f,
	0.0f, 0.0f, 1.0f,0.0f,

	1.0f, 0.0f, 0.0f,0.0f,
	1.0f, 0.0f, 0.0f,0.0f,
	1.0f, 0.0f, 0.0f,0.0f,

	1.0f, 0.0f, 0.0f,0.0f,
	1.0f, 0.0f, 0.0f,0.0f,
	1.0f, 0.0f, 0.0f,0.0f,

	-1.0f, 0.0f, 0.0f,0.0f,
	-1.0f, 0.0f, 0.0f,0.0f,
	-1.0f, 0.0f, 0.0f,0.0f,

	-1.0f, 0.0f, 0.0f,0.0f,
	-1.0f, 0.0f, 0.0f,0.0f,
	-1.0f, 0.0f, 0.0f,0.0f,

	0.0f,-1.0f, 0.0f,0.0f,
	0.0f,-1.0f, 0.0f,0.0f,
	0.0f,-1.0f, 0.0f,0.0f,

	0.0f,-1.0f, 0.0f,0.0f,
	0.0f,-1.0f, 0.0f,0.0f,
	0.0f,-1.0f, 0.0f,0.0f,

	0.0f, 1.0f, 0.0f,0.0f,
	0.0f, 1.0f, 0.0f,0.0f,
	0.0f, 1.0f, 0.0f,0.0f,

	0.0f, 1.0f, 0.0f,0.0f,
	0.0f, 1.0f, 0.0f,0.0f,
	0.0f, 1.0f, 0.0f,0.0f,
};
GLuint numOfTriangles = 36;

const GLuint WIDTH = 800, HEIGHT = 600;
float aspect = 800.0/600.0;

GLuint vbo_vertices, vbo_texture, vbo_normals;
GLuint vao, lightVAO;
GLuint tex_snake, tex_grass, tex_food, tex_stone;
Shader * shader, * lampShader;

// left, up, right, down, escape
bool keys[] = {false, false, false, false}; 
bool keyPressed = false;

// timing
float timeInt = 0.25f;

float angle = 0.0f;

int boardWidth = 15;
int boardHeight = 15;

std::vector<Food> food;
std::vector<Obstacle> obstacle;

void initOpenGL(GLFWwindow* window);
void prepareObjects();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void clearKeys();
GLuint readTexture(char* filename);
void windowResize(GLFWwindow* window, int width, int height);
void generateFood(int numOfFood, Snake snake);
void generateObstacles(int numOfObstacles, Snake snake);

void generateFood(int numOfFood, Snake snake) {
	for (int i = 0; i < numOfFood; i++) {
		bool checkOthers = false;

		int x, z;
		do {
			x = (rand() % boardWidth) - boardWidth / 2;
			z = (rand() % boardHeight) - boardHeight / 2;
			glm::vec3 pos = glm::vec3((float)x, 1.0f, (float)z);
			for (int j = 0; j < snake.elem.size(); j++) {
				if (snake.elem[j] == pos)
					checkOthers = true;
			}
			for (int j = 0; j < obstacle.size(); j++) {
				if (obstacle[j].position == pos)
					checkOthers = true;
			}
			for (int j = 0; j < food.size(); j++) {
				glm::vec3 foodPos = food[j].position;
				foodPos.y = 1.0f;
				if (foodPos == pos)
					checkOthers = true;
			}
		} while (checkOthers);

		food.push_back(Food(glm::vec3((float)x, 1.0f, (float)z)));
	}
}

void generateObstacles(int numOfObstacles, Snake snake) {
	for (int i = 0; i < numOfObstacles; i++) {
		bool checkOthers = false;

		int x, z;
		do {
			x = (rand() % boardWidth) - boardWidth/2;
			z = (rand() % boardHeight-1) - boardHeight/2;
			glm::vec3 pos = glm::vec3((float)x, 1.0f, (float)z);
			for (int j = 0; j < snake.elem.size(); j++) {
				if (snake.elem[j] == pos)
					checkOthers = true;
			}
			for (int j = 0; j < obstacle.size(); j++) {
				if (obstacle[j].position == pos)
					checkOthers = true;
			}
		} while (checkOthers);

		obstacle.push_back(Obstacle(glm::vec3((float)x,1.0f,(float)z)));
	}
}


int main()
{
	srand(time(NULL));

	glfwInit();
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Snake", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}
	
	Snake snake;

	/*food.push_back(Food(glm::vec3(4.0f, 1.35f, 0.0f)));
	food.push_back(Food(glm::vec3(2.0f, 1.35f, 4.0f)));
	food.push_back(Food(glm::vec3(-2.0f, 1.35f, 4.0f)));*/

	/*obstacle.push_back(Obstacle(glm::vec3(6.0f, 1.0f, 6.0f)));
	obstacle.push_back(Obstacle(glm::vec3(6.0f, 1.0f, -6.0f)));
	obstacle.push_back(Obstacle(glm::vec3(-6.0f, 1.0f, -6.0f)));*/

	generateObstacles(6, snake);
	generateFood(3, snake);

	initOpenGL(window);
	glfwSetTime(0);

	// game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// time calculation
		float currentFrame = glfwGetTime();
		float ratio = currentFrame / timeInt;

		float x = sin(angle) * 7.0f;
		float z = cos(angle) * 7.0f;
		angle += 0.002;

		glm::vec3 lightPos(x, 5.0f, z);
		glm::vec3 cameraPos(0.0f, 15.0f, 15.0f);

		shader->use();
		
		shader->setUnifVec3("directionalLight.direction", glm::vec3(5.0f, 10.0f, 5.0f));
		shader->setUnifVec3("directionalLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		shader->setUnifVec3("directionalLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		shader->setUnifVec3("directionalLight.specular", glm::vec3(0.75f, 0.75f, 0.75f));

		shader->setUnifVec3("pointLight.position", lightPos);
		shader->setUnifVec3("pointLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		shader->setUnifVec3("pointLight.diffuse", glm::vec3(0.75f, 0.75f, 0.75f));
		shader->setUnifVec3("pointLight.specular", glm::vec3(0.25f, 0.25f, 0.25f));

		shader->setUnifVec3("spotLight.position", snake.getHead() + glm::vec3(0.0f, 10.0f, 0.0f));
		shader->setUnifVec3("spotLight.direction", -glm::vec3(0.0f, 10.0f, 0.0f));
		shader->setUnifVec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		shader->setUnifVec3("spotLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		shader->setUnifVec3("spotLight.specular", glm::vec3(0.3f, 0.3f, 0.3f));
		glUniform1f(shader->getUniformLocation("spotLight.cutOff"), glm::cos(glm::radians(1.0f)));
		glUniform1f(shader->getUniformLocation("spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		glUniform1i(shader->getUniformLocation("textureMap"), 0);
		glUniform1f(shader->getUniformLocation("shininess"), 16);

		glm::mat4 P = glm::perspective(50.0f * 3.1415f / 180.0f, aspect, 1.0f, 50.0f);
		glm::mat4 V = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 M = glm::mat4(1.0f);
		shader->setUnifMat4("P", P);
		shader->setUnifMat4("V", V);
		shader->setUnifMat4("M", M);
		
		if (glfwGetTime() > timeInt) {
			snake.changeDirection(keys);
			snake.checkCollision(&food, &obstacle);
			snake.move();
			clearKeys();
			glfwSetTime(0);
		}
		
		// draw background
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_grass);
		glBindVertexArray(vao);
		for (int i = 0; i < boardWidth; i++) {
			for (int j = 0; j < boardHeight; j++) {
				M = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f*(-boardWidth / 2 + i), 0.0f, 1.0f*(-boardHeight / 2 + j)));
				shader->setUnifMat4("M", M);
				glDrawArrays(GL_TRIANGLES, 0, numOfTriangles);
			}
		}
		glBindVertexArray(0);

		// draw snake
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_snake);
		glBindVertexArray(vao);

		for (int i = 0; i < snake.elem.size(); i++) {
			//glm::vec3 adj = (snake.getPrevElem(i) - snake.getElem(i)) * (1-ratio);
			M = glm::translate(glm::mat4(1.0f), snake.getElem(i));
			//M = glm::translate(M, adj);
			shader->setUnifMat4("M", M);
			glDrawArrays(GL_TRIANGLES, 0, numOfTriangles);

			/*M = glm::translate(glm::mat4(1.0f), snake.getPrevElem(i));
			M = glm::translate(M, glm::vec3(0.0f, 1.0f, 0.0f));
			shader->setUnifMat4("M", M);
			glDrawArrays(GL_TRIANGLES, 0, numOfTriangles);*/
		}
		glBindVertexArray(0);

		// draw food
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_food);
		glBindVertexArray(vao);
		for (int i = 0; i < food.size(); i++) {
			food[i].angle += 0.005;
			M = glm::translate(glm::mat4(1.0f), food[i].position);
			M = glm::scale(M, glm::vec3(0.65f, 0.65f, 0.65f));
			M = glm::rotate(M, food[i].angle, glm::vec3(0.0f, 1.0f, 0.0f));
			M = glm::translate(M, glm::vec3(0.0f, (sin(food[i].angle) - 0.5f)*0.25f, 0.0f));
			shader->setUnifMat4("M", M);
			glDrawArrays(GL_TRIANGLES, 0, numOfTriangles);
		}
		glBindVertexArray(0);

		// draw obstacles
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_stone);
		glBindVertexArray(vao);
		for (int i = 0; i < obstacle.size(); i++) {
			M = glm::translate(glm::mat4(1.0f), obstacle[i].position);
			shader->setUnifMat4("M", M);
			glDrawArrays(GL_TRIANGLES, 0, numOfTriangles);
		}
		glBindVertexArray(0);

		lampShader->use();
		M = glm::translate(glm::mat4(1.0f), lightPos);
		M = glm::scale(M, glm::vec3(0.2f));
		lampShader->setUnifMat4("P", P);
		lampShader->setUnifMat4("V", V);
		lampShader->setUnifMat4("M", M);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, numOfTriangles);
		glBindVertexArray(0);
		
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &vbo_texture);
	glDeleteBuffers(1, &vbo_normals);
	glDeleteBuffers(1, &vbo_texture);
	glfwTerminate();

	return EXIT_SUCCESS;
}

void windowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	if (height != 0) {
		aspect = (float)width / (float)height;
	}
	else {
		aspect = 1;
	}
}

void initOpenGL(GLFWwindow* window) {
	glClearColor(0.1f, 0.1f, 0.2f, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, windowResize);

	shader = new Shader("./resources/shaders/vertex.vs", "", "./resources/shaders/fragment.fs");
	lampShader = new Shader("./resources/shaders/lamp.vs", "", "./resources/shaders/lamp.fs");

	GLint textureUnits;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);

	prepareObjects();

	tex_snake = readTexture("./resources/textures/metal.png");
	tex_grass = readTexture("./resources/textures/grass.png");
	tex_food = readTexture("./resources/textures/texture.png");
	tex_stone = readTexture("./resources/textures/stone.png");
}

GLuint makeBuffer(void *data, int vertexCount, int vertexSize) {
	GLuint handle;

	glGenBuffers(1, &handle);
	glBindBuffer(GL_ARRAY_BUFFER, handle); 
	glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);

	return handle;
}

void prepareObjects() {
	vbo_vertices = makeBuffer(cube, numOfTriangles, sizeof(float) * 4);
	vbo_texture = makeBuffer(cube_texture, numOfTriangles, sizeof(float) * 2);
	vbo_normals = makeBuffer(cube_normals, numOfTriangles, sizeof(float) * 4);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	shader->setAttrVec4("vertex", vbo_vertices);
	shader->setAttrVec4("normal", vbo_normals);
	shader->setAttrVec2("texture", vbo_texture);
	glBindVertexArray(0);

	// --- LIGHT SHADER ---
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	lampShader->setAttrVec4("vertex", vbo_vertices);
	glBindVertexArray(0);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (!keyPressed) {
			keyPressed = true;
			if (key == GLFW_KEY_LEFT) keys[0] = true;
			else if (key == GLFW_KEY_UP) keys[1] = true;
			else if (key == GLFW_KEY_RIGHT) keys[2] = true;
			else if (key == GLFW_KEY_DOWN) keys[3] = true;
		}
	}
}

void clearKeys() {
	keyPressed = false;
	for (int i = 0; i < 4; i++) {
		keys[i] = false;
	}
}

GLuint readTexture(char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filename);
	glGenTextures(1, &tex); 
	glBindTexture(GL_TEXTURE_2D, tex); 
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return tex;
}