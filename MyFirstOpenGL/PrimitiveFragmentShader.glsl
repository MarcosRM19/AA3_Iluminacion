#version 440 core

out vec4 fragColor;

uniform vec2 windowSize;
uniform vec4 ambientColor; 

void main(){
	fragColor = ambientColor;

}