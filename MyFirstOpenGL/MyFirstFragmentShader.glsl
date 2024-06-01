#version 440 core

uniform vec2 windowSize;
uniform sampler2D textureSampler;
uniform vec3 sourceLight;
uniform float t;

uniform vec3 colorA;
uniform vec3 colorB;

in vec2 uvsFragmentShader;
in vec3 normalsFragmentShader;
in vec4 primitivePosition;

vec4 ambientColor; 

vec4 color;
out vec4 fragColor;

void main() {
       
            vec2 adjustedTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);
            vec4 baseColor = texture(textureSampler, adjustedTexCoord);  

            vec3 lineToLight = normalize(sourceLight - primitivePosition.xyz); 
            float sourceLightAngle = dot(normalsFragmentShader, lineToLight); 

            vec3 ambientColor = mix(colorA, colorB, t);

            color =  vec4(baseColor.rgb * sourceLightAngle * ambientColor, 1.0); 
        

        fragColor = color;

}
