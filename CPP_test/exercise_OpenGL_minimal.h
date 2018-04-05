#pragma once

#include "include_GL.h"

namespace exercise_OpenGL_minimal
{
#if 0
	void test0()
	{

		//raw Vertex Data
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<unsigned int> indices;

		//generic buffer objects
		//VBO is just a term used for normal Buffer Objects that are meant to hold vertex data!
		GLuint vbo[3];
		glGenBuffers(3, vbo);

		//Type Array Buffer for vertex attributes
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float) * 3, vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float) * 2, uvs.data(), GL_STATIC_DRAW);

		//Type Element buffer for indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

		//compile Shader Code
		GLuint vertex;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		GLuint fragment;
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		//Link to Program
		GLuint program;
		program = glCreateProgram();
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		glLinkProgram(ID);

		//you can delete original
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		//activate the shader
		glUseProgram(program);

		//draw
		glEnableVertexAttribArray(0); //layout location
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1); //layout location
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); //GL_Lines etc!

		//deactivate the shader or use the next
		glUseProgram(0);

	}
#endif
}