#version 150

uniform vec4 globalColor;

out vec4 outputColor;

uniform sampler2DRect tex0;
in vec2 texCoordVarying;
 
void main()
{
    outputColor = globalColor;
    //outputColor = texture(tex0, texCoordVarying);
}
