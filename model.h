#pragma once

#include "shaderClass.h"

class Model
{
public:

    Model(const char* file);

    void Draw(Shader& shader);
};