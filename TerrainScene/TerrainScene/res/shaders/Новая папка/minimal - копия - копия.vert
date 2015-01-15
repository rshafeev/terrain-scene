
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
		
		/* ������� �������������� ������� � ������ ���������� � ����������� ��������� */
		normal = normalize(gl_NormalMatrix * gl_Normal);
		
		/* ������ ����������� ����������� �����. ������, ��� �������� ������������
		OpenGL, ���� ����������� � ������������ ������ �������. �����, ��� ��� �� 
		������� � ������������ �����, ���� "�������" - ��� � ���� �����������. */

		lightDir = normalize(vec3(gl_LightSource[0].position));
 
		/* �������� ������� ���� ����� �������� � ������������ �����. ���� � ���
		������������, ��� ��� ����������� - ��������� ��� ������ �������. */
		NdotL = max(dot(normal, lightDir), 0.0);
		
		/* ��������� ������ */
		diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
		
		gl_FrontColor =  NdotL * diffuse;
		
		gl_Position = ftransform();


        vertex_src      = vec2(gl_Vertex.x/2000,1.0-gl_Vertex.z/2000);
        gl_TexCoord[0] = gl_MultiTexCoord0;

}
