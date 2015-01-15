uniform sampler2D tex1;
uniform sampler2D tex2;
uniform vec2 volna;
varying vec2 vertex_src;


void main()
{
     vec3 texture1= vec3(texture2D(tex1  ,gl_TexCoord[0].xy));
     vec3 texture2= vec3(texture2D(tex2  ,gl_TexCoord[0].xy));
     vec4 color =vec4(vec3(texture1*volna[0]+texture2*volna[1]),1.0);
     if(color[0]>1.0) color[0]=1.0;
     if(color[1]>1.0) color[1]=1.0;
     if(color[2]>1.0) color[2]=1.0; 
     gl_FragColor=color;

}