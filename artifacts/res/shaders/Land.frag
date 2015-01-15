uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D texVec;

varying vec2 vertex_src;


void main()
{
  
        vec3 ColorVec = vec3(texture2D(texVec,vec2(vertex_src)));   
        vec4 smesh=vec4(vec3(vec3(texture2D(tex1  ,gl_TexCoord[0].xy))*ColorVec.r+
                             vec3(texture2D(tex2  ,gl_TexCoord[0].xy))*ColorVec.g+
                             vec3(texture2D(tex3  ,gl_TexCoord[0].xy))*ColorVec.b),0.0);

       smesh=gl_Color*smesh;
   
 /*    if(smesh[0]>1) smesh[0]=1;
       if(smesh[1]>1) smesh[1]=1;
       if(smesh[2]>1) smesh[2]=1;
   */    
       gl_FragColor = smesh; 

}