#version 400

//in vec3 VertexPosition;
//in vec3 VertexColor;
out vec3 Color;
uniform mat4 MVP;
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;
void main()
{
   //gl_Position = vec4( VertexPosition, 1.0 );
   
   //gl_Position =gl_Vertex;
   gl_Position = MVP * vec4(vPos,1);

   Color = vColor;
}