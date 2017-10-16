#version 120

//uniform sampler2DRect tex0;
uniform sampler2DRect texture;

varying vec2 texCoordVarying;

void main()
{
    gl_FragColor = texture2DRect(texture, texCoordVarying);
}
