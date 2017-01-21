
#include <stdio.h>
#include <SDL/SDL.h>

#define APP_NAME	"synth"

#define SCREEN_BPP	16

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

#include <list>
#include <algorithm>

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstdio>
#include <GL/freeglut.h>

#include <linux/soundcard.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

using namespace std;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define tex_num 6

const int BPP = 4; 
const double PI = 3.14159;
static unsigned int g_seed;
 int fd;
GLuint texture[tex_num]; 
GLUquadricObj *quadratic; 
int Width = 1200;
int Height = 900;


int buf_mat_size = 0;
unsigned char* buf_mat; 


Vector4D light(0, 20, 5, 1);


const float move_sensitivity = 0.2f;
const float radius_sensitivity = 0.04f;
int mouse_x = 0;
int mouse_y = 0;
bool mouse_left_down = false;
bool mouse_right_down = false;


const float max_radius = 40.0f;
const float min_radius = 1.0f;
const float max_elevation_angle = 0.0f;
const float min_elevation_angle = -PI;
float tilt_angle = PI / 2.0f;
float elevation_angle = -PI / 2.0f;
float camera_radius = 5.0f;
Vector3D camera(0, 0, 0);


bool post_effect = false;


struct MyPolygon
{
	Vector3D vertices[3];
	Vector3D normal;
	float sort_criteria;

	bool operator <(const MyPolygon &poly) const { return poly.sort_criteria < sort_criteria; }
};
std::list<MyPolygon> bottle;
struct NormalMapBottle
{
	Vector3D vertice;
	Vector3D normal;
};


GLUnurbsObj *nurbs_object;
float key_points[4][4][3];


GLUquadricObj *quadric;


struct MyStar
{
	Vector3D vertice;
	float sort_criteria;

	bool operator <(const MyStar &star) const { return star.sort_criteria < sort_criteria; }
};
std::list<MyStar> stars;

const GLfloat fogColor[4] = 		{0.5f,0.5f,0.5f,1.0f};
inline int fastrand() { 
  g_seed = (214013*g_seed+2531011); 
  return (g_seed>>16)&0x7FFF; 
} 

typedef struct
{
    bool Visible;
    bool MouseFocus;
    bool KeyboardFocus;
} S_AppStatus;

bool isProgramLooping;														
S_AppStatus AppStatus;														
	SDL_Surface *Screen;													
	SDL_Event	E;															
	Uint8		*Keys;														
	Uint32		Vflags;														
	Uint32		TickCount;													
	Uint32		LastCount;

int crcl_angle = 0;
bool trig_tr = false,butt_tr = false,key_tr = false;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// int LoadGLTextures( )
// {

//     /* Status indicator */
//     bool Status = false;;

//     int loop;

//     /* Create storage space for the texture */
//     SDL_Surface *TextureImage[2];

//     /* Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit */
//     if ( ( TextureImage[0] = SDL_LoadBMP( "data/bg.bmp" ) ) &&
//          ( TextureImage[1] = SDL_LoadBMP( "data/reflect.bmp" ) ) )
//     {

//         /* Set the status to true */
//         Status = true;

//         /* Create The Texture */
//         glGenTextures( tex_num, &texture[0] );
//         for( loop = 0; loop <= 1; loop++ )
//         {
//             /* Create Nearest Filtered Texture */
//             glBindTexture( GL_TEXTURE_2D, texture[loop] ); /* Gen Tex 0 And 1 */
//             glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST );
//             glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST );
//             glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[loop]->w, TextureImage[loop]->h,
//                 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage[loop]->pixels );

//             /* Create Linear Filtered Texture */
//             glBindTexture( GL_TEXTURE_2D, texture[loop+2] ); /* Gen Tex 2 And 3 */
//             glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//             glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//             glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[loop]->w, TextureImage[loop]->h,
//                 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage[loop]->pixels );

//             /* Create MipMapped Texture */
//             glBindTexture( GL_TEXTURE_2D, texture[loop+4] ); /* Gen Tex 4 and 5 */
//             glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//             glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
//             gluBuild2DMipmaps( GL_TEXTURE_2D, 3, TextureImage[loop]->w, TextureImage[loop]->h,
//                 GL_BGR, GL_UNSIGNED_BYTE, TextureImage[loop]->pixels );
//         }
//     }
//     /* Free up any memory we may have used */
//     for( loop = 0; loop <= 1; loop++ )
//     {
//         if ( TextureImage[loop] )
//             SDL_FreeSurface( TextureImage[loop] );
//     }

//     return Status;
// }








// void sub(void(*draw_callback)())
// {
// 	//glClearStencil(0);
// 	glClear(GL_STENCIL_BUFFER_BIT);
// 	glEnable(GL_CULL_FACE);
// 	glCullFace(GL_BACK);
// 	glDepthMask(GL_FALSE);
// 	glEnable(GL_STENCIL_TEST);	
// 	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
// 	glStencilFunc(GL_ALWAYS, 0, 0);
// 	draw_callback();
// 	glDepthMask(GL_TRUE);
// 	glCullFace(GL_FRONT);
// 	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
// 	glStencilFunc(GL_NOTEQUAL, 0, 1);
// 	glDepthFunc(GL_GREATER);  
// 	draw_callback();  
// 	glDisable(GL_STENCIL_TEST);
// 	glDepthFunc(GL_LESS);
// 	glCullFace(GL_BACK);
// }


// void clip(void(*draw_callback)())
// {
// 	glCullFace(GL_FRONT);
// 	draw_callback();  
// 	glCullFace(GL_BACK);
// }


// void draw_main_object()
// {
// 	glPushMatrix();
// 	gluCylinder(quadric, 1, 1, 2, 64, 64);
// 	glRotatef(180, 0, 1, 0);
// 	gluDisk(quadric, 0, 1, 64, 64);
// 	glRotatef(-180, 0, 1, 0);
// 	glTranslatef(0, 0, 2);
// 	gluDisk(quadric, 0, 1, 64, 64);
// 	glPopMatrix();
// }



// void draw_sub_object1()
// {
// 	glPushMatrix();
// 	glScalef(0.6f, 0.6f, 1.1f);
// 	glTranslatef(0, 0, -0.1f);
// 	draw_main_object();

// 	glPopMatrix();
// }


// void draw_sub_object2()
// {
// 	glPushMatrix();
// 	glTranslatef(0, 1, 1);
// 	gluSphere(quadric, 0.5f, 64, 64);
// 	glPopMatrix();
// }


// void draw_sub_object3()
// {
// 	glPushMatrix();
// 	glTranslatef(0, 1, 1);
// 	glScalef(2.2f, 1.2f, 0.5f);
// 	glutSolidCube(1);
// 	glPopMatrix();
// }


// void draw_csg(bool shadow_color = false)
// {
// 	glPushMatrix();
// 	glTranslatef(6, -1, 0);
// 	float angle = SDL_GetTicks() * 0.03f;
// 	//glRotatef(angle, 0, 1, 0);

	
// 		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

// 		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);		
// 		draw_main_object();
// 		sub(draw_sub_object1);
// 		sub(draw_sub_object2);
// 		sub(draw_sub_object3);
// 		sub(draw_sub_object1);
// 		sub(draw_sub_object2);
// 		sub(draw_sub_object3);
// 		clip(draw_main_object);
// 		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

// 		glDepthFunc(GL_EQUAL);
// 		glCullFace(GL_BACK);

// 		glColor3ub(200, 200, 255);
// 		draw_main_object();
// 		glCullFace(GL_FRONT);
// 		glColor3ub(255, 255, 20);
// 		draw_sub_object1();
// 		glColor3ub(200, 255, 200);
// 		draw_sub_object2();
// 		glColor3ub(255, 200, 255);
// 		draw_sub_object3();		

// 		glDepthFunc(GL_LEQUAL);
// 		glDisable(GL_STENCIL);
// 		glDisable(GL_CULL_FACE);

// 		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	

// 	glPopMatrix();
// }
// inline Vector3D bottle_eq(float u, float v)
// {
// 	float r = 4.0f * (1.0f - cos(u) / 2.0f);
// 	return u < PI ? Vector3D(5 * cos(u) * (1 + sin(u)) + r * cos(u) * cos(v) - 10, 10.0f * sin(u) + r * sin(u) * cos(v) + 10, r * sin(v) - 30) * 0.1f : 
// 					Vector3D(5 * cos(u) * (1 + sin(u)) + r * cos(v + PI) - 10, 10.0f * sin(u) + 10, r * sin(v) - 30) * 0.1f;	
// }


// void set_bottle()
// {
// 	float delta = 2.0f * PI / 120.0f;

// 	for (float u = -PI; u < PI - EPS; u += delta)
// 	{
// 		for (float v = -PI; v < PI - EPS; v += delta)
// 		{	
// 			MyPolygon poly1;
// 			poly1.vertices[0] = bottle_eq(u, v);
// 			poly1.vertices[1] = bottle_eq(u + delta, v);
// 			poly1.vertices[2] = bottle_eq(u, v + delta);			
// 			poly1.normal = getNormal(poly1.vertices[2], poly1.vertices[1], poly1.vertices[0]);
// 			bottle.push_back(poly1);

// 			MyPolygon poly2;
// 			poly2.vertices[0] = bottle_eq(u, v + delta);
// 			poly2.vertices[1] = bottle_eq(u + delta, v);
// 			poly2.vertices[2] = bottle_eq(u + delta, v + delta);	
// 			poly2.normal= getNormal(poly2.vertices[2], poly2.vertices[1], poly2.vertices[0]);
// 			bottle.push_back(poly2);
// 		}
// 	}
// }


// void draw_bottle(bool shadow_color = false)
// {
	
// 	for (std::list<MyPolygon>::iterator i = bottle.begin(); i != bottle.end(); i++)
// 	{
// 		i->sort_criteria = camera.distanceTo((i->vertices[0] + i->vertices[1] + i->vertices[2]) / 3);
// 	}

	
// 	bottle.sort();

// 	glPushMatrix();
// 	 glColor4ub(255, 205, 255, 155);
// 		glBegin(GL_TRIANGLES);
// 	for (std::list<MyPolygon>::iterator i = bottle.begin(); i != bottle.end(); i++)
// 	{
// 		glNormal3fv(i->normal);
// 		glVertex3fv(i->vertices[0]);
// 		glVertex3fv(i->vertices[1]);
// 		glVertex3fv(i->vertices[2]);
// 	}
// 	glEnd();
// 	glColor4ub(255, 255, 255, 255);	
// 	glPopMatrix();
// }



// void cinsity()
// {
// 	glReadPixels(0, 0, (GLsizei)Width, (GLsizei)Height, GL_RGBA, GL_UNSIGNED_BYTE, buf_mat);

// 	for (int i = 0; i < buf_mat_size; i += BPP)
// 	{
// 		int bw = (buf_mat[i + 0] + buf_mat[i + 1] + buf_mat[i + 2]) / 3;

// 		buf_mat[i + 0] = bw ;
// 		buf_mat[i + 1] = bw ;
// 		buf_mat[i + 2] = bw ;
// 		buf_mat[i + 3] = 255;
		
// 	}

// 	glDrawPixels((GLsizei)Width, (GLsizei)Height, GL_RGBA, GL_UNSIGNED_BYTE, buf_mat);
// }


// void draw_ground()
// {

// 	glColor4f(0.0, 0.0, 0.0, 0.40);
// 	glPushMatrix();
// 	glTranslatef(0, -4, 0);
// 	glRotatef(-90, 1, 0, 0);
// 	gluDisk(quadric, 0, 10, 64, 64);
// 	glPopMatrix();
// 	glColor3ub(255, 255, 255);

// }



// void draw_reflection()
// {
	
	
// 	glPushMatrix();
// 	glTranslatef( 0.0f, 0.0f, +10.0f );
// 	glEnable(GL_TEXTURE_GEN_S);
    
//     glEnable(GL_TEXTURE_GEN_T);

   
//     glBindTexture( GL_TEXTURE_2D, texture[2] );

//      gluCylinder(quadratic,1.0f,1.0f,3.0f,32,32);  

//     glDisable( GL_TEXTURE_GEN_S );
    
//     glDisable( GL_TEXTURE_GEN_T );
// 	glPopMatrix();

//     glBindTexture( GL_TEXTURE_2D, texture[1] );

//     glPushMatrix();
//         glTranslatef( 0.0f, 0.0f, +20.0f );
//         glBegin( GL_QUADS );
//             glNormal3f( 0.0f, 0.0f, 1.0f);
//             glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -13.3f, -10.0f,  10.0f );
//             glTexCoord2f( 1.0f, 0.0f ); glVertex3f(  13.3f, -10.0f,  10.0f );
//             glTexCoord2f( 1.0f, 1.0f ); glVertex3f(  13.3f,  10.0f,  10.0f );
//             glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -13.3f,  10.0f,  10.0f );
//         glEnd();
//     glPopMatrix();
  
// }


// void set_stingray()
// {
// 	for (int u = 0; u < 4; u++)
// 	{
// 		for (int v = 0; v < 4; v++)
// 		{
// 			key_points[u][v][0] = u;
// 			key_points[u][v][1] = v - 0.5f;
// 			key_points[u][v][2] = 0;
// 		}
// 	}

// 	nurbs_object = gluNewNurbsRenderer();	
// 	gluNurbsProperty(nurbs_object, GLU_CULLING, GL_TRUE);
// 	gluNurbsProperty(nurbs_object, GLU_DISPLAY_MODE, GLU_FILL);
// }


// void animate_stingray()
// {
// 	float angle = glutGet(GLUT_ELAPSED_TIME) * 0.003f;

// 	key_points[0][0][2] = sin(angle + PI / 7.0f) * 0.4f;
// 	key_points[0][1][2] = cos(angle + PI / 8.0f) * 0.7f;
// 	key_points[0][2][2] = sin(angle + PI / 9.0f) * 0.3f;
// 	key_points[0][3][2] = sin(angle + PI / 10.0f) * 0.4f;

// 	key_points[1][0][2] = cos(angle + PI / 4.0f) * 0.9f;
// 	key_points[1][1][2] = sin(angle + PI / 5.0f) * 0.7f;
// 	key_points[1][2][2] = cos(angle + PI / 6.0f) * 0.4f;
// 	key_points[1][3][2] = cos(angle + PI / 7.0f) * 0.5f;

// 	key_points[2][0][2] = sin(angle + PI / 10.0f) * 0.8f;
// 	key_points[2][1][2] = sin(angle + PI / 12.0f) * 0.7f;
// 	key_points[2][2][2] = cos(angle + PI / 13.0f) * 0.4f;
// 	key_points[2][3][2] = cos(angle + PI / 14.0f) * 0.2f;
		
// 	key_points[3][0][2] = sin(angle + PI / 14.0f) * 0.7f;
// 	key_points[3][1][2] = cos(angle + PI / 13.0f) * 0.6f;		
// 	key_points[3][2][2] = sin(angle + PI / 12.0f) * 0.4f;
// 	key_points[3][3][2] = sin(angle + PI / 11.0f) * 0.1f;
// }


// void draw_towel(bool shadow_color = false)
// {	
// 	glEnable(GL_AUTO_NORMAL);
// 	float shadow_k = 0.3f;
// 	if (shadow_color) 
// 		glColor4ub(145 * shadow_k, 155 * shadow_k, 255 * shadow_k, 150); 
// 	else 
// 		glColor4ub(145, 155, 255, 200);
// 	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
// 	float knots[] = {0, 0, 0, 0, 1, 1, 1, 1};
// 	glPushMatrix();
// 	glTranslatef(-3, 5, 2);
// 	glRotatef(-90, 1, 0, 0);
// 	glScalef(2, 2, 2);
// 	gluBeginSurface(nurbs_object);	
// 	gluNurbsSurface(nurbs_object, 8, knots, 8, knots, 12, 3, &key_points[0][0][0], 4, 4, GL_MAP2_VERTEX_3);
// 	gluEndSurface(nurbs_object);
// 	glPopMatrix();
// 	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
// 	glColor4ub(255, 255, 255, 255);
// 	glDisable(GL_AUTO_NORMAL);
// }


// void draw_scene_objects(bool shadow_color = false)
// {
	
// 		draw_bottle(shadow_color);
// 		draw_towel();

// }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void draw_circle(int rot)
{
	glPushMatrix();
	int l = rot%360;
	glRotatef(l, 0, 0, 1);
	glColor3f(1.0, 0.0, 0.0);
	gluDisk(quadric, 0, 1, 64, 64);
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0, 0.8, -0.2);
	gluDisk(quadric, 0, 0.2, 64, 64);
	glPopMatrix();
	glPopMatrix();
	glColor3ub(255, 255, 255);
}

void draw_trigger(bool that)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
            glVertex3f(0.25,0.5,0);
            glVertex3f(0.25,-0.5,0);
            glVertex3f(-0.25,-0.5,0);
            
            
            glVertex3f(-0.25,0.5,0);
            glVertex3f(0.25,0.5,0);
            glVertex3f(-0.25,-0.5,0);
    glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0, 0, -0.2);
	if(that)
	{
    glBegin(GL_TRIANGLES);
            glVertex3f(0.25,0.5,0);
            glVertex3f(0.25,0,0);
            glVertex3f(-0.25,0,0);
            
            
            glVertex3f(-0.25,0.5,0);
            glVertex3f(0.25,0,0);
            glVertex3f(-0.25,0,0);
    glEnd();
	}
	else
	{
		glBegin(GL_TRIANGLES);
            glVertex3f(0.25,0,0);
            glVertex3f(0.25,-0.5,0);
            glVertex3f(-0.25,-0.5,0);
            
            
            glVertex3f(-0.25,0,0);
            glVertex3f(0.25,-0.5,0);
            glVertex3f(-0.25,-0.5,0);
    glEnd();
	}
    glColor3ub(255, 255, 255);
}


void draw_button(bool that)
{

	if(that)
	{

	glColor3f(0.0, 1.0, 0.0);

	glBegin(GL_TRIANGLES);
            glVertex3f(0.5,0.5,0);
            glVertex3f(0.5,-0.5,0);
            glVertex3f(-0.5,-0.5,0);
            
            
            glVertex3f(-0.5,0.5,0);
            glVertex3f(0.5,0.5,0);
            glVertex3f(-0.5,-0.5,0);
    glEnd();
	}
	else
	{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
            glVertex3f(0.5,0.5,0);
            glVertex3f(0.5,-0.5,0);
            glVertex3f(-0.5,-0.5,0);
            
            
            glVertex3f(-0.5,0.5,0);
            glVertex3f(0.5,0.5,0);
            glVertex3f(-0.5,-0.5,0);
    glEnd();
	}
    glColor3ub(255, 255, 255);
}


void draw_key(bool that)
{
	glColor3f(1.0, 0.0, 0.0);
	if(that)
	{
	glBegin(GL_TRIANGLES);
            glVertex3f(0.25,0.5,0);
            glVertex3f(0.25,-1.5,+0.5);
            glVertex3f(-0.25,-1.5,+0.5);
            
            
            glVertex3f(-0.25,0.5,0);
            glVertex3f(0.25,0.5,0);
            glVertex3f(-0.25,-1.5,+0.5);
    glEnd();
	}
	else
	{
		glBegin(GL_TRIANGLES);
            glVertex3f(0.25,0.5,0);
            glVertex3f(0.25,-1.5,0);
            glVertex3f(-0.25,-1.5,0);
            
            
            glVertex3f(-0.25,0.5,0);
            glVertex3f(0.25,0.5,0);
            glVertex3f(-0.25,-1.5,0);
    glEnd();
	}
    glColor3ub(255, 255, 255);
}


void scene()
{

draw_circle(crcl_angle);
glTranslatef(-4,0,0);
draw_trigger(trig_tr);
glTranslatef(+8,0,0);
draw_button(butt_tr);
glTranslatef(-4,-2,0);
draw_key(key_tr);

}



void set_camera_and_light()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluLookAt(camera.x, camera.y, camera.z, 0, 0, 0, 0.0, 1.0, 0.0);

	glLightfv(GL_LIGHT0, GL_POSITION, light);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Vector4D(0, -1, -0.2f, 1));
}


void display()
{

	set_camera_and_light();
	scene();
	
}

void mouse_move_callback(int x, int y)
{

	int dx = x - mouse_x;
	int dy = y - mouse_y;

	if (mouse_left_down)
	{			
		tilt_angle += dx * PI / 180.0f * move_sensitivity; 
		elevation_angle += dy * PI / 180.0f * move_sensitivity;		

		if (elevation_angle > max_elevation_angle) elevation_angle = max_elevation_angle - EPS;
		if (elevation_angle < min_elevation_angle) elevation_angle = min_elevation_angle + EPS;
	}

	if (mouse_right_down)
	{
		int d_max = fmax(-dx, dy);
		int d_min = fmin(-dx, dy);
		int delta = d_max > 0 ? d_max : (d_min < 0 ? d_min : 0);
		camera_radius += delta * radius_sensitivity;
		if (camera_radius < min_radius) camera_radius = min_radius;
		if (camera_radius > max_radius) camera_radius = max_radius;
	}

	camera.x = cos(tilt_angle) * sin(elevation_angle) * camera_radius;
	camera.y = cos(elevation_angle) * camera_radius;
	camera.z = sin(tilt_angle) * sin(elevation_angle) * camera_radius;

	mouse_x = x;
	mouse_y = y;
}

void set_quadric()
{
	quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
}



bool init(SDL_Surface *S)
{

	glutInitDisplayMode(GLUT_RGBA | GLUT_STENCIL | GLUT_DOUBLE | GLUT_DEPTH);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.1f, 0.1f, 0.1f, 1);
	//LoadGLTextures();

	glEnable( GL_TEXTURE_2D );
	glShadeModel( GL_SMOOTH );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
	
	glEnable(GL_NORMALIZE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);	
	glClearDepth(1);	

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Vector4D(0.15f, 0.15f, 0.1f, 1));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Vector4D(0.75f, 0.75f, 0.6f, 1));
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 4);
	glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 80);
	glEnable(GL_LIGHT0);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Vector4D(0.15f, 0.15f, 0.1f, 1));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Vector4D(0.65f, 0.65f, 0.6f, 1));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Vector4D(0.1f, 0.1f, 0.1f, 1));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 40);		


	// set_bottle();
	 set_quadric();
	// set_stingray();

	// glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

 //    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    quadratic = gluNewQuadric( );

    // gluQuadricNormals( quadratic, GLU_SMOOTH );
 
    // gluQuadricTexture( quadratic, GL_TRUE );


	
	return true;
}



void TerminateApplication(void)												
{
	static SDL_Event Q;														

	Q.type = SDL_QUIT;														

	if(SDL_PushEvent(&Q) == -1)												
	{
		
		throw(0);															
	}

	return;																	
}

void sent_to()
{
	///////////////////////
	//////////////////
	///////////////
	//////////////
	//////////////////
	////////////////
	////////////////
	//////////////////
}

void Update(Uint32 Milliseconds, Uint8 *Keys)					
{

	if(Keys)													
	{
		if(Keys[SDLK_ESCAPE])									
		{
			TerminateApplication();								
		}
		if(Keys[SDLK_1])
		{
			if(butt_tr)
				butt_tr = false;
			else
				butt_tr = true;

			unsigned char data[3] = {0x90, 60, 127};
  			write(fd, data, sizeof(data));
  			cout<<"wrote button change to device" << endl;
		}
		else if(Keys[SDLK_2])
		{
			unsigned char data[3] = {0x90, 60, 127};
   			write(fd, data, sizeof(data));
            crcl_angle++;
            cout<<"wrote wheel rotation change to device" << endl;
		}
		else if(Keys[SDLK_3])
		{
			 
            if(trig_tr)
				trig_tr = false;
			else
				trig_tr = true;
			unsigned char data[3] = {0x90, 60, 127};
  			write(fd, data, sizeof(data));
  			cout<<"wrote trigger flick to device" << endl;
		}
		else if(Keys[SDLK_4])
		{
			 
            if(key_tr)
				key_tr = false;
			else
				key_tr = true;
			unsigned char data[3] = {0x90, 60, 127};
   			write(fd, data, sizeof(data));
   			cout<<"wrote key state to device" << endl;
		}	
	}
	return;														
}



bool Initialize(void)					
{
	AppStatus.Visible		= true;								
	AppStatus.MouseFocus	= true;								
	AppStatus.KeyboardFocus = true;								
	return true;												
}
void Deinitialize (void)										
{
	
}


bool InitTimers(Uint32 *C)													
{
	*C = SDL_GetTicks();													

	return true;															
}


void ToggleFullscreen(void)													
{
	SDL_Surface *S;															

	S = SDL_GetVideoSurface();												

	if(!S || (SDL_WM_ToggleFullScreen(S)!=1))								
	{
		
	}
	
	return;																	
}

void ReshapeGL(int width, int height)										
{
	if (width > 0 && height > 0)
	{
		Width = width;
		Height = height;

		buf_mat_size = width * height * BPP;

		if (buf_mat_size > 0) delete []buf_mat;
		buf_mat = new unsigned char[buf_mat_size];

		glViewport(0, 0, width, height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(45.0, (GLdouble)(width / (GLdouble)height), 0.1, 100.0);
	}
	return;																	
}

bool CreateWindowGL (SDL_Surface *S, int W, int H, int B, Uint32 F)			
{
	if(!(S = SDL_SetVideoMode(W, H, B, F)))									
	{
		return false;														
	}

	ReshapeGL(Width, Height);											
	return true;															
}

int main(int argc, char **argv)												
{
	char* device =  "/dev/midi" ;


    fd = open(device, O_WRONLY, 0);


	try															
{
	glutInit(&argc, argv);
    
													
	
	Screen = NULL;															
	Keys = NULL;															
	Vflags = SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_OPENGLBLIT;					
																			
	

	if(SDL_Init(SDL_INIT_VIDEO)<0)											
	{
		
		throw(0);															
	}

	

#if defined FULLSCREEN_ASK													

	if(MessageBox(HWND_DESKTOP, "Usare il modo fullscreen?",				
		"Fullscreen?", MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		Vflags|=SDL_FULLSCREEN;												
	}

#elif defined FULLSCREEN													

	Vflags|=SDL_FULLSCREEN;													

#endif																		
																			

	if(!CreateWindowGL(Screen, Width, Height, SCREEN_BPP, Vflags))		
	{
		
		throw(0);															
	}
	SDL_WM_SetCaption(APP_NAME, NULL);										

	if(!InitTimers(&LastCount))												
	{
		
		throw(0);															
	}

	if(!init(Screen))														
	{
		
		throw(0);														
	}

	if(!Initialize())														
	{
		
		throw(0);															
	}

	isProgramLooping = true;												

	while(isProgramLooping)													
	{
		if(SDL_PollEvent(&E))												
		{
			switch(E.type)													
			{
				
			case SDL_QUIT:													
				{
					isProgramLooping = false;								
					break;													
				}

			case SDL_VIDEORESIZE:											
				{
					ReshapeGL(E.resize.w, E.resize.h);						
					break;													
				}
			case SDL_MOUSEMOTION:
				{
					mouse_move_callback(E.motion.x,E.motion.y);
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
				{
					
					mouse_x = E.button.x;
					mouse_y = E.button.y;
					if (E.button.button == 	SDL_BUTTON_LEFT)	
						mouse_left_down = true; 
					if (E.button.button ==SDL_BUTTON_RIGHT) 
						mouse_right_down = true;
					break;
					
				}
			case SDL_MOUSEBUTTONUP:
			{
				if (E.button.button ==SDL_BUTTON_LEFT) 
					mouse_left_down = false; 
				if (E.button.button ==SDL_BUTTON_RIGHT) 
					mouse_right_down = false;
				break;
			}
			case SDL_ACTIVEEVENT:											
				{
					if(E.active.state & SDL_APPACTIVE)						
					{
						if(E.active.gain)									
						{
							AppStatus.Visible = true;						
						}
						else												
						{
							AppStatus.Visible = false;						
						}
					}
					
					if(E.active.state & SDL_APPMOUSEFOCUS)					
					{
						if(E.active.gain)									
						{
							AppStatus.MouseFocus = true;						
						}
						else												
						{
							AppStatus.MouseFocus = false;					
						}
					}

					if(E.active.state & SDL_APPINPUTFOCUS)					
					{
						if(E.active.gain)									
						{
							AppStatus.KeyboardFocus = true;					
						}
						else												
						{
							AppStatus.KeyboardFocus = false;				
						}
					}
					
					break;													
				}

			case SDL_KEYDOWN:												
				{
					Keys = SDL_GetKeyState(NULL);							
					break;													
				}

			}
		}
		else																
		{
			if(!AppStatus.Visible)											
			{
				SDL_WaitEvent(NULL);										
			}
			else															
			{
				TickCount = SDL_GetTicks();	




												
				Update(TickCount-LastCount, Keys);							
				LastCount = TickCount;										
				display();	
				
				SDL_GL_SwapBuffers();										
			}
		}
	}

	Deinitialize();															
																			
	throw(0);															
}
catch(int a){std::cout<<"exited with code "<<a<<std::endl;}

SDL_Quit();
	return 0;																
}
