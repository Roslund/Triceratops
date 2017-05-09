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

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main(void)
{
    color = abs(vec4(vNorm, 1.0));
    gl_Position = Projection * View * Model * vec4(vPos, 1.0f);
}
