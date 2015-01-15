uniform sampler2D tex1;


void main()
{

  vec4 smesh=vec4(vec3(texture2D(tex1,gl_TexCoord[0].xy)),0.0);
  gl_FragColor =smesh*gl_Color; 


}