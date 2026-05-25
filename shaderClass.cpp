#include"shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);      	
	}
	throw(errno);
}
//Constructor que construye el programa shader a partir de 2 shaders diferentes
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    //Leer vertexFile y fragmentFile y almacenar las cadenas
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

    //Convierte las cadenas de origen del sombreador en matrices de caracteres
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

    //Crear un objeto shader de vértices y obtener su referencia
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Adjuntar la fuente del shader de vértices al objeto del shader de vértices
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    //Compilar el shader de vértices en código de máquina
    glCompileShader(vertexShader);

    //Crear un objeto de shader de fragmentos y obtener su referencia
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //adjuntar la fuente del shader de fragmentos al objeto del shader de fragmentos
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    //compilar el shader de vértices en código de máquina
    glCompileShader(fragmentShader);

    //Crear un objeto de programa de shader y obtener su referencia
    ID = glCreateProgram();
    //Adjuntar los shaders de vértices y fragmentos al programa de shaders 
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    //Resumir/vincular todos los shaders en el programa de shaders
    glLinkProgram(ID);

    //Eliminar los ahora inútiles objetos de shader de fragmentos y vértices
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}