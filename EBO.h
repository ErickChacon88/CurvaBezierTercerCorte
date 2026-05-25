#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	//Referencia de ID del objeto de búfer de elementos
	GLuint ID;
	//Constructor que genera un objeto de búfer de elementos y lo vincula a índices
	EBO(GLuint* indices, GLsizeiptr size);

	//Vincula el EBO
	void Bind();
	//Desvincula el EBO
	void Unbind();
	//Elimina el EBO 
	void Delete();
};
#endif
