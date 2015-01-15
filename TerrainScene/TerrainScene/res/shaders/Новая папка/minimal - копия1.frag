uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D texVec;

varying vec2 vertex_src;
varying  vec3 l; 
varying vec3 n; 

const vec4  diffColor = vec4 ( 0.8, 0.8, 0.8, 1.0 ); 
  const vec4  specColor = vec4 ( 0.9, 0.9, 0.9, 1.0 ); 
  const float  specPower = 80.0; 

void main()
{

        vec3 Color1   = vec3(texture2D(tex1  ,gl_TexCoord[0].xy));    
        vec3 Color2   = vec3(texture2D(tex2  ,gl_TexCoord[0].xy));    
        vec3 Color3   = vec3(texture2D(tex3  ,gl_TexCoord[0].xy));    
        vec3 ColorVec = vec3(texture2D(texVec,vec2(vertex_src)));   
	vec3 colorSmeshn=vec3(Color1*ColorVec.r+Color2*ColorVec.g+Color3*ColorVec.b); 
        
       
 vec4 smesh=vec4(vec3(colorSmeshn),0.0);




  vec3  n2  = normalize ( n ); 
  vec3  l2  = normalize ( l ); 
  vec4  diff = diffColor * max ( dot ( n2, l2 ), 0.0 ); 

  smesh=diff*smesh;


       if(smesh[0]>1) smesh[0]=1;
       if(smesh[1]>1) smesh[1]=1;
       if(smesh[2]>1) smesh[2]=1;

  gl_FragColor = smesh; 


}