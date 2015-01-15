
varying vec2 vertex_src;


uniform  vec4  lightPos; 

varying vec4 vertex;
varying vec3 light;
varying float h;

void main()
{

                vec3 normal, lightDir;
		vec4 diffuse;
		float NdotL;
		
		/* сначала трансформируем нормаль в нужные координаты и нормализуем результат */
		normal = normalize(gl_NormalMatrix * gl_Normal);
		
		/* “еперь нормализуем направление света. ”чтите, что согласно спецификации
		OpenGL, свет сохран€етс€ в пространстве нашего взгл€да. “акже, так как мы 
		говорим о направленном свете, поле "позици€" - это и есть направление. */

		lightDir = normalize(vec3(gl_LightSource[0].position));
 
		/* вычислим косинус угла между нормалью и направлением света. —вет у нас
		направленный, так что направление - константа дл€ каждой вершины. */
		NdotL = max(dot(normal, lightDir), 0.0);
		
		/* вычисл€ем диффуз */
		diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
		
		gl_FrontColor =  NdotL * diffuse;
		
		gl_Position = ftransform();


        vertex_src      = vec2(gl_Vertex.x/2000,1.0-gl_Vertex.z/2000);
        gl_TexCoord[0] = gl_MultiTexCoord0;

}
