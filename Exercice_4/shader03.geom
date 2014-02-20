  #version 150 compatibility
  #extension GL_ARB_geometry_shader4 : enable

  #define WINDOWS 0

  #if WINDOWS
  layout (triangles) in;
  layout (triangle_strip) out;
  #endif

  layout (max_vertices = 72) out;

  const float pi = 3.14159265359;

  ////////////////
  uniform vec4 ambientColor;
  uniform vec4 diffuseColor;
  uniform vec4 specularColor;
  uniform float specularExponent;

  uniform int level;
  uniform float time;

  in vertexData
  {
	  vec3 pos;
	  vec3 normal;
	  vec4 color;
  }vertices[];

  out fragmentData
  {
	  vec3 vpos;
	  vec3 normal;
	  vec4 color;
  }frag;   


  ///////////////////////////////
  // exercise 3 random helper function for bonus 3.1
  float rnd(vec2 x)
  {
	  int n = int(x.x * 40.0 + x.y * 6400.0);
	  n = (n << 13) ^ n;
	  return 1.0 - float( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0;
  }

  ///////////////////////////////
  void main()
  {
	  ///////////////////////////////
	  // TODO replace the geometry pass-through 
	  // shader in the following with exercise 3
	  // you can also add a function to produce new vertices
	  
	  int factor = int(pow(2,level)); // Level of subdivision
	  
	  int animate = 0; // Display animation if animate==1
	  int loopDuration = 10;
	  int currTime = int(mod(time, loopDuration));	  
	  
	  int i = 0;
	  int j = 0;
	  frag.vpos = vertices[i].pos;
	  frag.normal = vertices[i].normal;
	  frag.color = vertices[i].color;
	  
	  vec4 direc1 = (gl_in[i+1].gl_Position - gl_in[i].gl_Position);
	  vec4 direc2 = (gl_in[i+2].gl_Position - gl_in[i].gl_Position);
	  
	  
	  for(i = 0; i < factor; i++)	
	  { 
	    for(j = 0; j < factor-i; j++)
	    {  	      
	      
	      if (animate == 0) { // Subdivision without animation
	    
		gl_Position = gl_in[0].gl_Position + (i*direc1)/factor + (j*direc2)/factor;
		EmitVertex();     
		gl_Position = gl_in[0].gl_Position + ((i+1)*direc1)/factor + (j*direc2)/factor;
		EmitVertex(); 
		gl_Position = gl_in[0].gl_Position + (i*direc1)/factor + ((j+1)*direc2)/factor;
		EmitVertex(); 
		
		EndPrimitive(); 	 
	      
	      } else {	// Subdivision with animation	    
	      
		if (currTime > loopDuration/2) 
		    currTime =  loopDuration - currTime;
		    
		vec3 N = frag.normal;
		
		/*Vertex Animation*/
		
		// /*
		gl_Position = gl_in[0].gl_Position + (i*direc1)/factor + (j*direc2)/factor;
		gl_Position.xy += frag.normal[0]*(rnd(gl_Position.xy)/(currTime+1))/loopDuration;
		gl_Position.yz += frag.normal[0]*(rnd(gl_Position.yz)/(currTime+1))/loopDuration;
		gl_Position.xz += frag.normal[0]*(rnd(gl_Position.xz)/(currTime+1))/loopDuration;
		EmitVertex();  		

		gl_Position = gl_in[0].gl_Position + ((i+1)*direc1)/factor + (j*direc2)/factor;
		EmitVertex(); 		

		gl_Position = gl_in[0].gl_Position + (i*direc1)/factor + ((j+1)*direc2)/factor;	
		EmitVertex(); 
	      
		EndPrimitive();
		
		// /*
	
		/*Explosion Animation (Comment above and Uncomment below to display)*/
		
		
		/*
		
		gl_Position = gl_in[0].gl_Position + (i*direc1)/factor + (j*direc2)/factor + vec4(currTime * rnd(x))/100;		
		EmitVertex();  
		
		gl_Position = gl_in[0].gl_Position + ((i+1)*direc1)/factor + (j*direc2)/factor + vec4(currTime * rnd(x))/100;		
		EmitVertex(); 
		
		gl_Position = gl_in[0].gl_Position + (i*direc1)/factor + ((j+1)*direc2)/factor + vec4(currTime * rnd(x))/100;		
		EmitVertex(); 
	      
		EndPrimitive(); 
		
		*/
	      
	      }
	   
	      }   
	    
	    }	 
  }