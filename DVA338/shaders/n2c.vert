//
//  DVA338
//
//  Created by Anton Roslund on 2017-04-19.
//  Copyright © 2017 Anton Roslund. All rights reserved.
//
#version 150 core

in vec3 vPos;
in vec3 vNorm;
out vec4 color;
uniform mat4 PV;
uniform int White;

void main(void)
{
    color = abs(vec4(vNorm, 1.0));
    if(White == 1)
    {
        color = vec4(1.f, 1.f, 1.f, 1.f);
    }
    gl_Position = PV * vec4(vPos, 1.0f);
}
