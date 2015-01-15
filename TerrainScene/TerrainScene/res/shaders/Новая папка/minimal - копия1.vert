
varying vec2 vertex_src;

varying  vec3 l; 
varying  vec3 n; 
uniform  vec4  lightPos; 


void main()
{
        vertex_src      = vec2(gl_Vertex.x/2000,1.0-gl_Vertex.z/2000);
        gl_TexCoord[0] = gl_MultiTexCoord0;
        vec3  p = vec3 ( gl_ModelViewMatrix * gl_Vertex );  

  l = normalize ( vec3 (vec3(gl_LightSource[0].position );              
  n = normalize ( gl_NormalMatrix * gl_Normal );              

  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; 


}
