#version 330 core
in vec2 TexCoords;
out vec4 color;
uniform bool EnableTexture = true ;
uniform vec4 Color;
uniform sampler2D image;

void main()
{   
    if(EnableTexture)
    {
        color =texture(image, TexCoords);
    }
    else   
    {
        color = Color;
    } 
   // color = vec4(0,0,0,1);
}  