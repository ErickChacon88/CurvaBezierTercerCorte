#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
    //ID de referencia del programa sombreador
    GLuint ID;
    //Constructor que construye el programa shader a partir de 2 shaders diferentes
    Shader(const char* vertexFile, const char* fragmentfile);

    //Activa el programa shader
    void Activate();
    //Elimina el programa shader
    void Delete();
};


#endif