
varying vec2 vertex_src;
void main()
{

                vec3 normal, lightDir;
		vec4 diffuse, ambient, globalAmbient;
		float NdotL;
		
		normal = normalize(gl_NormalMatrix * gl_Normal);
		lightDir = normalize(vec3(gl_LightSource[0].position));
		NdotL = max(dot(normal, lightDir), 0.0);
		diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
		
		ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
		globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
		
		gl_FrontColor =  NdotL * diffuse + globalAmbient + ambient;
		
		gl_Position = ftransform();
                vertex_src      = vec2(gl_Vertex.x/4096,1.0-gl_Vertex.z/4096);
                gl_TexCoord[0]  = gl_MultiTexCoord0;

}
