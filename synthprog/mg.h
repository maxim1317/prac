//Объявления переменных, просто объявления
const int BPP = 4; 
const double PI = 3.1415926535897932384626433832795;
static unsigned int g_seed;

int window_width = 1200;
int window_height = 900;


int buffer_size = 0;
unsigned char* buffer; 


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