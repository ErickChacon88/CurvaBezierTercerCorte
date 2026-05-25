#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in float Height;

uniform vec4 lightColor;

void main()
{
    // =====================================
    // DIRECCION DE LUZ
    // =====================================

    vec3 lightDir =
        normalize(vec3(-0.3, -1.0, -0.2));

    // =====================================
    // DIFUSA
    // =====================================

    float diff =
        max(dot(normalize(Normal), -lightDir), 0.2);

    // =====================================
    // GLOW SCI-FI
    // =====================================

    float glow =
        0.5 + abs(sin(Height * 8.0)) * 0.5;

    vec3 finalColor =
        lightColor.rgb *
        diff *
        1.8;

    // =====================================
    // BRILLO EXTRA
    // =====================================

    finalColor +=
        lightColor.rgb *
        glow *
        0.25;

    FragColor =
        vec4(finalColor, 1.0);
}