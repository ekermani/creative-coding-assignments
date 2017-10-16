#version 120

uniform sampler2DRect texture;
// the time value is passed into the shader by the OF app.
uniform float time;

varying vec2 texCoordVarying;

void main()
{
    // get the texture coordinates
    texCoordVarying = gl_MultiTexCoord0.xy;
    
    vec4 modifiedPosition = gl_Vertex;
    
    // we need to scale up the values we get from the texture
    float scale = 200;
    
    // here we get the red channel value from the texture
    // to use it as vertical displacement
    float displacementY = texture2DRect(texture, texCoordVarying).x;
    float displacementHeight = 80.0;
    float displacementWidth = 40.0;
    
    // use the displacement we created from the texture data
    // to modify the vertex position
    //modifiedPosition.z += displacementY * scale * (sin(time));
    modifiedPosition.z += displacementY * scale * (sin(time*100.0));
    
    // this is the resulting vertex position multiplied by the correct matrix
    gl_Position = gl_ModelViewProjectionMatrix * modifiedPosition;
}
