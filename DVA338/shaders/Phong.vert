//
//  DVA338
//
//  Created by Anton Roslund on 2017-04-19.
//  Copyright © 2017 Anton Roslund. All rights reserved.
//
#version 150 core

in vec3 vPos;
in vec3 vNorm;
out vec3 N;
out vec3 pos;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main(void)
{
// Transform vertex normal into eye coordinates
N = normalize(vec3(Model * vec4(vNorm, 0.0f)));
pos = vec3(Model * vec4(vPos, 1.0f));
    
//Set this shit
gl_Position = Projection * View * Model * vec4(vPos, 1.0f);
}
