#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "GL/glew.h"

#ifdef __linux__
#include <GL/glut.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#endif

#ifdef __APPLE__
#include <glut.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#endif

#ifdef _WIN32
#include "GL/glut.h"
#include "inc/mtime.h"
#endif

#include "inc/objLoader.h"
///////////////////////////////////////////////////////////////////////
//Error checking functions
void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
		abort();
	}
}

#define _DEBUG 1
#if _DEBUG
#define GL_CHECK(stmt) do { \
	stmt; \
	CheckOpenGLError(#stmt, __FILE__, __LINE__); \
} while (0)
#else
#define GL_CHECK(stmt) stmt
#endif

///////////////////////////////////////////////////////////////////////
//Text file IO for shader files
char *textFileRead(char *fn)
{
	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) {
		fp = fopen(fn,"rt");

		if (fp != NULL) {

			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}

	if (content == NULL)
	{
		fprintf(stderr, "ERROR: could not load in file %s\n", fn);
		exit(1);
	}
	return content;
}

int textFileWrite(char *fn, char *s)
{
	FILE *fp;
	int status = 0;

	if (fn != NULL) {
		fp = fopen(fn,"w");

		if (fp != NULL) {

			if (fwrite(s,sizeof(char),strlen(s),fp) == strlen(s))
				status = 1;
			fclose(fp);
		}
	}
	return(status);
}   

///////////////////////////////////////////////////////////////////////
//shaders and light pos variables
GLuint v,f,p,g;
float lpos[4] = {15.0, 0.5, 15.0, 0.0};
struct timeval time_;
int subdivLevel;
GLuint tex;
PPMImage * textureImage;

// mouse controls
/////////////////////////////////////////////////
//TODO add scene interaction variables here
int mouse_old_x, mouse_old_y;
int mouse_buttons = 0;
float rotate_x = 0.0, rotate_y = 0.0;
float move_x = 0.0, move_y = 0.0;
float win_width = 128.0, win_height = 128.0;
float translate_z = -1.0;
/////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
//adapt viewport when window size changes
void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	/////////////////////////////////////////////////
	//TODO add scene interaction code here
	win_width = w;
	win_height = h;
	/////////////////////////////////////////////////
}

///////////////////////////////////////////////////////////////////////
//the actual render function, which is called for each frame
void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0,0.0,1.0,0.0,0.0,-1.0,0.0f,1.0f,0.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glPushMatrix();
	/////////////////////////////////////////////////
	//TODO add scene interaction code here
	glTranslatef(move_x, move_y, 0.0);
	glTranslatef(0.0, 0.0, translate_z);
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	/////////////////////////////////////////////////
	glActiveTexture(GL_TEXTURE0);
	GLint loc = glGetUniformLocation(p, "textureImage");
	if (loc != -1)
	{
		GL_CHECK(glUniform1i(loc, 0));
	}

	glBindTexture(GL_TEXTURE_2D, tex);
	glutSolidTeapot(0.5);
	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();
	GL_CHECK(glutSwapBuffers());
}

///////////////////////////////////////////////////////////////////////
//keyboard functions
void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27) 
		exit(0);
}

///////////////////////////////////////////////////////////////////////
// mouse interaction functions
void mouseClick(int button, int state, int x, int y)
{
	/////////////////////////////////////////////////
	// TODO add code to handle mouse click events
	// use GLUT_UP and GLUT_DOWN to evaluate the current 
	// "state" of the mouse.

	if (state == GLUT_DOWN)
	{
		mouse_buttons |= 1<<button;
	}
	else if (state == GLUT_UP)
	{
		mouse_buttons = 0;
	}

	mouse_old_x = x;
	mouse_old_y = y;
	/////////////////////////////////////////////////
}

void mouseMotion(int x, int y)
{
	/////////////////////////////////////////////////
	// TODO add code to handle mouse move events
	// and calculate reasonable values for object 
	// rotations

	float dx, dy;
	dx = (float)(x - mouse_old_x);
	dy = (float)(y - mouse_old_y);

	if (mouse_buttons & 1)
	{
		rotate_x += dy * 0.2f;
		rotate_y += dx * 0.2f;
	}
	else if (mouse_buttons & 2)
	{
		move_x += dx * 1.0f/win_width;
		move_y -= dy * 1.0f/win_height;
	}
	else if (mouse_buttons & 4)
	{
		translate_z += dy * 0.01f;
	}

	mouse_old_x = x;
	mouse_old_y = y;
	/////////////////////////////////////////////////
}

///////////////////////////////////////////////////////////////////////
//load, compile and set the shaders
void setShaders()
{
	char *vs,*fs,*gs;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	g = glCreateShader(GL_GEOMETRY_SHADER);

	vs = textFileRead("./shader04a.vert");
	fs = textFileRead("./shader04a.frag");
	gs = textFileRead("./shader04a.geom");

	const char * ff = fs;
	const char * vv = vs;
	const char * gg = gs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);
	glShaderSource(g, 1, &gg,NULL);

	free(vs);free(fs);free(gs);

	glCompileShader(v);
	glCompileShader(f);
	glCompileShader(g);

	GLint blen = 0; 
	GLsizei slen = 0;

	glGetShaderiv(v, GL_INFO_LOG_LENGTH , &blen);       
	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);
		glGetShaderInfoLog(v, blen, &slen, compiler_log);
		std::cout << "compiler_log vertex shader:\n" << compiler_log << std::endl;
		free (compiler_log);
	}
	blen = 0; 
	slen = 0;
	glGetShaderiv(f, GL_INFO_LOG_LENGTH , &blen);       
	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);
		glGetShaderInfoLog(f, blen, &slen, compiler_log);
		std::cout << "compiler_log fragment shader:\n" << compiler_log << std::endl;
		free (compiler_log);
	}
	blen = 0; 
	slen = 0;
	glGetShaderiv(g, GL_INFO_LOG_LENGTH , &blen);       
	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);
		glGetShaderInfoLog(g, blen, &slen, compiler_log);
		std::cout << "compiler_log geometry shader:\n" << compiler_log << std::endl;
		free (compiler_log);
	}

	p = glCreateProgram();

	glAttachShader(p,f);
	glAttachShader(p,v);
	glAttachShader(p,g);

	glLinkProgram(p);
	// comment out this line to not use the shader

	glUseProgram(p);

	GLint loc = glGetUniformLocation(p, "ambientColor");
	if (loc != -1)
	{
		GL_CHECK(glUniform4f(loc, 0.5,0.5,0.5,1.0));
	}

	loc = glGetUniformLocation(p, "diffuseColor");
	if (loc != -1)
	{
		GL_CHECK(glUniform4f(loc, 0.5,0.5,0.5,1.0));
	}

	loc = glGetUniformLocation(p, "specularColor");
	if (loc != -1)
	{
		GL_CHECK(glUniform4f(loc, 0.5,0.5,0.5,1.0));
	}

	loc = glGetUniformLocation(p, "specularExponent");
	if (loc != -1)
	{
		GL_CHECK(glUniform1f(loc, 25.0));
	}

}



void initialize () 
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, 320, 320);
	GLfloat aspect = (GLfloat) 320 / 320;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, aspect, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel( GL_SMOOTH );
	glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );
	glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
	GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
	glEnable( GL_LIGHT0 );
	glEnable( GL_COLOR_MATERIAL );
	glShadeModel( GL_SMOOTH );
	glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	//textureImage = readPPM("pebbles_texture.ppm");
	textureImage = readPPM("yourOwnTexture.ppm");
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	printf("%d %d \n", textureImage->x, textureImage->y);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureImage->x, textureImage->y, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage->data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

///////////////////////////////////////////////////////////////////////
//main, setup and execution of environment
int main(int argc, char **argv) {
	//in case somebody wants to try the example implementation of Exercise 3:
	subdivLevel = 2.0;
	if(argc > 1)
		subdivLevel = atoi(argv[1]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Computer Graphics");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);

	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0,0.0,0.0,1.0);

	glewInit();
	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		printf("Ready for GLSL\n");
	else {
		printf("No GLSL support\n");
		exit(1);
	}

	if (glewIsSupported("GL_VERSION_2_1"))
		printf("Ready for OpenGL 2.1\n");
	else {
		printf("OpenGL 2.1 not supported\n");
		exit(1);
	}
	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader && GL_EXT_geometry_shader4)
		printf("Ready for GLSL - vertex, fragment, and geometry units\n");
	else {
		printf("Not totally ready :( \n");
		exit(1);
	}
	initialize();
	setShaders();

	glutMainLoop();
	return EXIT_SUCCESS;
}
