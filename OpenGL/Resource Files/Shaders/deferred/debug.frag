#version 330 core

out vec4 FragColor;
int vec3 TexCoords;

unifrom sampler gPosition;
unifrom sampler gNormals;
unifrom sampler gAlbedo;

void main(){
	  // Scale positions to 0-1 range for visualization
        vec3 pos = texture(gPosition, TexCoords).rgb;
        FragColor = vec4(pos * 0.1, 1.0); // Scale for visibility
}