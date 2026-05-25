#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	//ID de referencia del objeto de búfer de vértices
	GLuint ID;
	//Constructor que genera un objeto de búfer de vértices y lo vincula a los vértices
	VBO(GLfloat* vertices, GLsizeiptr size);

	//Vincula el VBO
	void Bind();
	//Desvincula el VBO
	void Unbind();
	//Elimina el VBO
	void Delete();
};
#endif