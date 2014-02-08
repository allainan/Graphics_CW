#version 150 compatibility

uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;
uniform float specularExponent;
uniform int shader;

in fragmentData
{
	vec3 pos;
	vec3 normal;
	vec4 color;
}frag;

///////////////

void main()
{
        vec4 outcol = frag.color;

        if(shader == 2)
        {
		////////////////////////////
		//exercise 2.2 Phong shading
		//TODO add your code here
		 
		 // Compute light source position and convert it
		vec3 light_Pos = vec3(gl_LightSource[0].position);
		
		// Compute direction and distance to the light source
		vec3 light_Dir = light_Pos - frag.pos;
		float d = distance(light_Pos, frag.pos);
		
		// Compute attenuation
		float attenuation = 1.0 / (gl_LightSource[0].constantAttenuation 
				    + gl_LightSource[0].linearAttenuation * d
				    + gl_LightSource[0].quadraticAttenuation * d * d);	
				    
		// Update I value
		float mu = 0.3;
		vec3 light_reflect = reflect(light_Dir, frag.normal);
		vec3 light_DirNorm = normalize(light_Dir);
		outcol = ambientColor 
			+ attenuation*diffuseColor*max(0.0, dot(frag.normal, light_DirNorm))
			+ attenuation*specularColor*max(0.0, pow(dot(normalize(-light_reflect), light_DirNorm), mu*specularExponent));
		 
		 

		////////////////////////////
        }

        if(shader == 3)
	{
		////////////////////////////
		//exercise 2.3 toon shading
		//TODO add your code here
		
		// Compute intensity
		vec3 l_norm = normalize(vec3(gl_LightSource[0].position));
		vec3 n_norm = normalize(frag.normal);
		float intensity = dot(l_norm, n_norm);
		
		// Update outcol value
		if (intensity > 0.98)
			outcol = vec4(0.8,0.8,0.8,1.0);
		else if (intensity > 0.5)
			outcol = vec4(0.8,0.4,0.4,1.0);
		else if (intensity > 0.25)
			outcol = vec4(0.6,0.2,0.2,1.0);
		else
			outcol = vec4(0.1,0.1,0.1,1.0);
		
		////////////////////////////
        }

	gl_FragColor = outcol;
}
