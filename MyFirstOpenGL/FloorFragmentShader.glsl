#version 440 core

uniform vec2 windowSize;
uniform sampler2D textureSampler;
uniform vec3 sourceLight;
uniform float t;
uniform float coeficientValue;

uniform vec3 colorA;
uniform vec3 colorB;

in vec2 uvsFragmentShader;
in vec3 normalsFragmentShader;
in vec4 primitivePosition;

vec4 ambientColor; 

vec3 orbitColor;
vec3 color;
out vec4 fragColor;     

void main() {
       
            vec2 adjustedTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);
            vec4 baseColor = texture(textureSampler, adjustedTexCoord);  

            vec3 lineToLight = normalize(sourceLight - primitivePosition.xyz); 
            float sourceLightAngle = dot(normalsFragmentShader, lineToLight); 

            if(sourceLightAngle < 0.15)
            {
                sourceLightAngle = 0.15;
            }

            vec3 ambientColor = mix(colorA, colorB, t);

            orbitColor =  baseColor.rgb * sourceLightAngle * ambientColor * coeficientValue; 

            color = orbitColor;

        fragColor = vec4(color,1.0);
}
