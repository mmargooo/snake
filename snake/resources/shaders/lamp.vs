#version 330 core

// argumenty
in vec4 vertex;
//in vec4 normal;

// jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

void main()	{
	gl_Position=P*V*M*vertex; 
}