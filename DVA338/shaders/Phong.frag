//
//  DVA338
//
//  Created by Anton Roslund on 2017-04-19.
//  Copyright © 2017 Anton Roslund. All rights reserved.
//
#version 330 core

in vec3 N;
in vec3 pos;
out vec4 fColor;

uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 DiffuseProduct2;
uniform vec4 SpecularProduct;

uniform vec3 LightPosition;
uniform vec3 LightPosition2;
uniform float Shininess;

void main(void)
{
    vec3 L = normalize(LightPosition); //vector from light to the point
    vec3 L2 = normalize(LightPosition2); //vector from light to the point
    vec3 E = normalize(-pos); //Eye position; from origen to point
    vec3 R = reflect(-L, N);
    vec3 R2 = reflect(-L2, N);
    
    
    //compute therms in the illumination equation
    vec4 ambient = AmbientProduct;
    
    float Kd = max( dot(L, N), 0.0 );
    vec4 diffuse = Kd * DiffuseProduct;
    
    float Ks = pow( max( dot(-E, R), 0.0 ), Shininess );
    vec4 specualar = Ks * SpecularProduct;
    if( dot(L, N) < 0.0 )
        specualar = vec4(0.0, 0.0, 0.0, 1.0);
    
    Kd = max( dot(L2, N), 0.0 );
    vec4 diffuse2 = Kd * DiffuseProduct2;
    
    Ks = pow( max( dot(-E, R2), 0.0 ), Shininess );
    vec4 specualar2 = Ks * SpecularProduct;
    if( dot(L, N) < 0.0 )
        specualar = vec4(0.0, 0.0, 0.0, 1.0);
    
    fColor = ambient + diffuse + specualar +diffuse2 + specualar2;
    fColor.a = 1.0;
}
