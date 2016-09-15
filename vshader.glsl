in vec3 a_position;
//inout vec4 color;
void main()
{
    // Calculate vertex position in screen space
    gl_Position = gl_ModelViewProjectionMatrix * vec4(a_position, 1.0);
}
