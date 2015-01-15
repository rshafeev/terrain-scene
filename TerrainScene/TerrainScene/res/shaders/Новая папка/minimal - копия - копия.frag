uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D texVec;

varying vec2 vertex_src;


void main()
{

        vec3 Color1   = vec3(texture2D(tex1  ,gl_TexCoord[0].xy));    
        vec3 Color2   = vec3(texture2D(tex2  ,gl_TexCoord[0].xy));    
        vec3 Color3   = vec3(texture2D(tex3  ,gl_TexCoord[0].xy));    
        vec3 ColorVec = vec3(texture2D(texVec,vec2(vertex_src)));   
	vec3 colorSmeshn=vec3(Color1*ColorVec.r+Color2*ColorVec.g+Color3*ColorVec.b); 
        vec4 smesh=vec4(vec3(colorSmeshn),0.0);







       smesh=gl_Color*smesh;
       if(smesh[0]>1) smesh[0]=1;
       if(smesh[1]>1) smesh[1]=1;
       if(smesh[2]>1) smesh[2]=1;
       gl_FragColor = smesh; 


}