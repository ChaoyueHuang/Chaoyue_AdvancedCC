#version 150 //final project

uniform vec4 globalColor;

out vec4 outputColor;

//uniform sampler2DRect tex0;
//in vec2 texCoordVarying;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

//void main()
//{
//    vec2 st = gl_FragCoord.xy/u_resolution.xy;
//    st.x *= u_resolution.x/u_resolution.y;
//
//    vec3 color = vec3(0.);
//    color = vec3(st.x,st.y,abs(sin(u_time)));
//
//    outputColor = vec4(color,1.0);
//
//    //outputColor = globalColor;
//    //outputColor = texture(tex0, texCoordVarying);
//}

//// YUV to RGB matrix
//mat3 yuv2rgb = mat3(1.0, 0.0, 1.13983,
//                    1.0, -0.39465, -0.58060,
//                    1.0, 2.03211, 0.0);
//
//// RGB to YUV matrix
//mat3 rgb2yuv = mat3(0.2126, 0.7152, 0.0722,
//                    -0.09991, -0.33609, 0.43600,
//                    0.615, -0.5586, -0.05639);
//
//void main(){
//    vec2 st = gl_FragCoord.xy/u_resolution;
//    vec3 color = vec3(0.0);
//
//    // UV values goes from -1 to 1
//    // So we need to remap st (0.0 to 1.0)
//    st -= 0.5;  // becomes -0.5 to 0.5
//    st *= 2.0;  // becomes -1.0 to 1.0
//
//    // we pass st as the y & z values of
//    // a three dimensional vector to be
//    // properly multiply by a 3x3 matrix
//    color = yuv2rgb * vec3(abs(sin(u_time)), st.x, st.y);
//
//    outputColor = vec4(color,1.0);
//}

vec2 random2( vec2 p ) {
    return fract(sin(vec2(dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3))))*43758.5453);
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;
    vec3 color = vec3(st.x,st.y,abs(sin(u_time)));
    
    // Scale
    st *= 3.;
    
    // Tile the space
    vec2 i_st = floor(st);
    vec2 f_st = fract(st);
    
    float m_dist = 1.;  // minimun distance
    
    for (int y= -1; y <= 1; y++) {
        for (int x= -1; x <= 1; x++) {
            // Neighbor place in the grid
            vec2 neighbor = vec2(float(x),float(y));
            
            // Random position from current + neighbor place in the grid
            vec2 point = random2(i_st + neighbor);
            
            // Animate the point
            point = 0.5 + 0.5*sin(u_time + 6.2831*point);
            
            // Vector between the pixel and the point
            vec2 diff = neighbor + point - f_st;
            
            // Distance to the point
            float dist = length(diff);
            
            // Keep the closer distance
            m_dist = min(m_dist, dist);
        }
    }
    
    // Draw the min distance (distance field)
    color += m_dist;
    
    // Draw cell center
    //color += 1.-step(.02, m_dist);
    
    // Draw grid
    //color.r += step(.98, f_st.x) + step(.98, f_st.y);
    
    // Show isolines
    // color -= step(.7,abs(sin(27.0*m_dist)))*.5;
    
    outputColor = vec4(color,1.0);
}
