#version 150 compatibility

////////////////
//exercise 2
uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;
uniform float specularExponent;
uniform int shader;

out vertexData
{
	vec3 pos;
	vec3 normal;
	vec4 color;
}vertex;

/////////////

void main()
{
        vertex.pos = vec3(gl_ModelViewMatrix * gl_Vertex);
        vertex.normal = normalize(gl_NormalMatrix * gl_Normal);
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        vertex.color = vec4(1.0,0.0,0.0,1.0);
	
        if(shader == 1)
        {
		//////////////////////////////
		//exercise 2.1 Gouraud shading
		//TODO add your code here
		
		// Compute light source position and convert it
		vec3 light_Pos = vec3(gl_LightSource[0].position);
		
		// compute direction and distance to the light source
		vec3 light_Dir = light_Pos - vertex.pos;
		float d = distance(light_Pos, vertex.pos);
		
		// Compute attenuation
		float attenuation = 1.0 / (gl_LightSource[0].constantAttenuation 
				    + gl_LightSource[0].linearAttenuation * d
				    + gl_LightSource[0].quadraticAttenuation * d * d);	
				    
		// Update I value
		float mu = 0.3;
		vec3 light_reflect = reflect(light_Dir, vertex.normal);
		vec3 light_DirNorm = normalize(light_Dir);
		vertex.color = ambientColor 
			      + attenuation*diffuseColor*max(0.0, dot(vertex.normal, light_DirNorm))
			      + attenuation*specularColor*max(0.0, pow(dot(normalize(-light_reflect), light_DirNorm), mu*specularExponent));
		
       
		//////////////////////////////
		
        
        } 

}
