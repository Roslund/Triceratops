//
//  DVA338
//
//  Created by Anton Roslund on 2017-04-19.
//  Copyright © 2017 Anton Roslund. All rights reserved.
//
#version 150 core

in vec3 N;
in vec3 pos;
out vec4 fColor;

uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;

uniform vec3 LightPosition;
uniform float Shininess;

void main(void)
{
    vec3 L = normalize(LightPosition);// - pos); //vector from light to the point
    vec3 E = normalize(pos); //Eye position; from origen to point
    vec3 H = normalize(L + E); //Half angle vector
    
    
    //compute therms in the illumination equation
    vec4 ambient = AmbientProduct;
    
    float Kd = max( dot(L, N), 0.0 );
    vec4 diffuse = Kd * DiffuseProduct;
    
    float Ks = pow( max( dot(H, N), 0.0 ), Shininess );
    vec4 specualar = Ks * SpecularProduct;
    if( dot(L, N) < 0.0 )
        specualar = vec4(0.0, 0.0, 0.0, 1.0);
    
    
    fColor = ambient + diffuse + specualar;
    fColor.a = 1.0;
}
