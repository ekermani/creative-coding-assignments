#version 120


uniform vec2 u_mouse;
// create uniform, give variable type (2 for width and height), then name
uniform vec2 u_resolution;
uniform float u_smoothX;
uniform float u_smoothY;

#define colorA vec3(1.0,1.0,0.6)
#define colorB vec3(6,0.2,0.6)

void main() {
    
    //    vec2 st = gl_FragCoord.xy / 1024.0; // putting 0->1024 between 0 and 1
    
//    vec2 st = gl_FragCoord.xy / u_resolution; // dividing vec 2 by vec2
    // AKA vec2 st = gl_FragCoord.xy / vec2(1024.0, 768.0);
    
    
    
    //    gl_FragColor = vec4(1.0,0.0,0.0, 1.0);
//    gl_FragColor = vec4(st.x,st.y,0.6, 1.0);
    

    vec2 st = gl_FragCoord.st / u_resolution;
    
    // scale mouse values to 0 to 1
    vec2 s_mouse = u_mouse/u_resolution;
    
    // find aspect ratio of resolution so we get a circulare pattern instead of ellipse if screen not square
    // scale by .25 to make smaller circle (change this vaue to experiment with other sizes)
    vec2 s_res = vec2(u_resolution.y/u_resolution.x,u_resolution.y/u_resolution.y) * .25;
    
    // calculate values based on distance to mouse
    float pct = length( (s_mouse-st) / s_res );
    
    // shape value
    pct =1.0-pct*pct;
    
    // mix two colors
    vec3 color = colorA*pct + (1.0-pct)*colorB;//mix(colorA,colorB,vec3(c,c,c));
    
    // apply color value
//    gl_FragColor = vec4(color,1.0);
    gl_FragColor = vec4(st.x,st.y,u_smoothX/768, u_smoothY/1024);

    

}

