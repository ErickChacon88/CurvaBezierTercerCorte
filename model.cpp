#define _CRT_SECURE_NO_WARNINGS

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "model.h"

#include <iostream>

#include <tinygltf/tiny_gltf.h>

Model::Model(const char* file)
{
    tinygltf::TinyGLTF loader;

    tinygltf::Model model;

    std::string err;
    std::string warn;

    bool ret = loader.LoadBinaryFromFile(
        &model,
        &err,
        &warn,
        file
    );

    if (!warn.empty())
        std::cout << warn << std::endl;

    if (!err.empty())
        std::cout << err << std::endl;

    if (!ret)
        std::cout << "No se pudo cargar el GLB" << std::endl;
    else
        std::cout << "GLB cargado correctamente" << std::endl;
}

void Model::Draw(Shader& shader)
{
    shader.Activate();
}