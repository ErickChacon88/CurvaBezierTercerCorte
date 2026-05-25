#include"VAO.h"

//Constructor que genera el ID de VAO
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

//Vincula un VBO al VAO usando un diseño determinado
void VAO::LinkVBO(VBO VBO, GLuint layout)
{
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

//Vincula el VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

//Desvincula el VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

//Elimina el VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}