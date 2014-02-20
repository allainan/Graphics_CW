#version 330 core

//simplified IO structures, no geometry shader any more
in vec2 textureUV;
out vec3 color;

//this is the texture of the framebuffer object
uniform sampler2D renderedTexture;

const float sampleDist = 0.3;

void main(){

	//this is one fragment of the framebuffer texture the main programme renders 
	//color = texture( renderedTexture, textureUV).xyz;

	//////////////////////////////////////
	//TODO Exercise 5
	//implement a simple image based blur here
	//modify color accordingly
	float s[12] =float[](-0.10568,-0.07568,-0.042158,
			     -0.02458,-0.01987456,-0.0112458,
			      0.0112458,0.01987456,0.02458,
			      0.042158,0.07568,0.10568);
	vec2 c = vec2(0.5, 0.5); 
	vec3 computed = vec3(0.0,0.0,0.0);
	
	for (int i=0; i!=12; i++)
	{
	  vec2 p = textureUV;
	  vec2 pvec = (c-p);
	  float d_i = s[i]*sampleDist;
	  computed += texture(renderedTexture, p + normalize(pvec)*d_i).xyz;
	}	
	
	color = computed/12;
	
	//////////////////////////////////////
}
