#version 150 core

uniform vec3 LightPosition;
in vec3 N;
out vec4 fColor;

void main()
{
    vec4 color;
    vec3 L = normalize(LightPosition);
    float intensity = dot(L,N);

    if (intensity > 0.95)
        color = vec4(1.0,0.5,0.5,1.0);
    else if (intensity > 0.5)
        color = vec4(0.6,0.3,0.3,1.0);
    else if (intensity > 0.25)
        color = vec4(0.4,0.2,0.2,1.0);
    else
        color = vec4(0.2,0.1,0.1,1.0);

    fColor = color;
}
