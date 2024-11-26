#version 330


layout(location = 0) in vec3 aPos;        

uniform mat4 model;
uniform mat4 DirlightSpaceMatrix;


void main(){
	gl_Position = DirlightSpaceMatrix * model * vec4(aPos, 1.0f);
}