#version 410 core

in vec2 vTexCoords;

out vec4 FragColor;

uniform sampler2D fboTexture;
uniform float gamma;

void main()
{
    vec4 texelColor = texture(fboTexture, vTexCoords);
    
    // Apply gamma correction: C_out = C_in^(1/gamma)
    vec3 correctedColor = pow(texelColor.rgb, vec3(1.0 / gamma));

    FragColor = vec4(correctedColor, texelColor.a);
}

