uniform float distance;

void main()
{
    vec4 vertex = gl_Vertex;
    // gl_InstanceID includes an index for the current instance, starting at 0
    vertex.x = vertex.x + gl_InstanceID * distance;
    vertex.y = vertex.y + gl_InstanceID * distance;
    gl_Position = gl_ModelViewProjectionMatrix * vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
}
