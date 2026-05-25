#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
    public: 
        //Referencia de ID para el objeto de matriz de vértices
        GLuint ID;
        //Constructor que genera el ID de VAO
        VAO();

        //Vincula un VBO al VAO usando un diseño determinado
        void LinkVBO(VBO VBO, GLuint layout);
        //Vincula el VAO
        void Bind();
        //Desvincula el VAO
        void Unbind();
        //Elimina el VAO 
        void Delete();
};

#endif