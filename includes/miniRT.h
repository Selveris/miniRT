#ifndef MINIRT_H
# define MINIRT_H

//---------------------------------//
//             config              //
//---------------------------------//
# define WIN_NAME		"-- MiniRT --"
# define WIN_W			1920
# define WIN_H			1080
# define DESTROY_NOTIFY	17
# define RAY_MAX_DEPTH	8
# define ALIASING		4

typedef struct s_session
{
	void	*mlx;
	void	*win;
}	t_ses;

t_ses	*start_session(void);
int		close_session(t_ses *ses);
int		key_hook(int key, t_ses *ses);
int		loop_hook(t_ses *ses);


//---------------------------------//
//              utils              //
//---------------------------------//
double	min(double a, double b);
double	max(double a, double b);
double	solve_quadratic(double a, double b, double c);

typedef struct s_v3
{
	double	x;
	double	y;
	double	z;
}	t_v3;

static const t_v3	V_ZERO = {0, 0, 0};

t_v3	v_scalarmul(t_v3 v, double s);
t_v3	v_sub(t_v3 a, t_v3 b);
t_v3	v_add(t_v3 a, t_v3 b);
double	v_norm(t_v3 v);
t_v3	v_normalize(t_v3 v);
double	v_dot(t_v3 a, t_v3 b);
t_v3	v_direction_to(t_v3 origin, t_v3 dest);
double	v_distance_to(t_v3 origin, t_v3 dest);
t_v3	v_symmetric(t_v3 dir, t_v3 normal);

typedef struct s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_color;

static const t_color	C_BLACK = {0, 0, 0};
static const t_color	C_WHITE = {255, 255, 255};
static const t_color	C_RED = {255, 0, 0};
static const t_color	C_GREEN = {0, 255, 0};
static const t_color	C_BLUE = {0, 0, 255};

void	color_add_normalized(t_color *base, t_color add);
void	color_add_bounded(t_color *base, t_color add);
t_color	color_vmul(t_color const base, t_v3 const *ratio);
t_color	color_smul(t_color const base, double ratio);

typedef struct s_img
{
	void			*mlx_img;
	int				bpp;
	int				l_size;
	int				endian;
	unsigned char	*data;
}	t_img;

t_img	*img_create(void *mlx, int width, int height);
void	img_destroy(void *mlx, t_img **img);
void	img_set_pixel(t_img *img, int i, int j, t_color color);


//---------------------------------//
//           RT Objects            //
//---------------------------------//
# include <libft.h>
static const double	O_MIN_DIST = 0.00001;

typedef struct s_ray
{
	t_v3	origin;
	t_v3	dir;
}	t_ray;

typedef struct s_cam
{
	t_v3	origin;
	double	yaw;
	double	pitch;
	double	roll;
	int		fov;	
}	t_cam;

typedef struct s_ambiant
{
	t_color	color;
}	t_ambiant;

typedef struct s_light
{
	t_v3	origin;
	t_color	color;
}	t_light;

typedef struct s_plane
{
	double	dist;
	t_v3	normal;
}	t_plane;

typedef struct s_sphere
{
	double	r;
	t_v3	origin;
}	t_sphere;

typedef struct s_mat
{
	t_v3	diffuse_ratio;
	double	reflection_ratio;
	double	specular_ratio;
	double	shininess;
}	t_mat;

typedef enum e_OType
{
	O_SPHERE,
	O_PLANE,
	O_LAST
}	t_OType;

typedef struct s_obj
{
	t_OType	type;
	t_mat	mat;
	union u_obj
	{
		t_plane		plane;
		t_sphere	sphere;
	}	geometry;
}	t_obj;

typedef struct s_scene
{
	t_cam		cam;
	t_color		background;
	t_ambiant	ambiant;
	t_list		*lights;
	t_list		*objs;
}	t_scene;

typedef struct s_intersect
{
	t_obj const	*obj;
	t_v3		point;
	t_v3		normal;
	t_v3		viewer;
}	t_intersect;

void	init_cam_dir(t_cam *cam, t_v3 const dir);
t_ray	cam_pixel_to_ray(t_cam const *cam, int i, int j);

t_v3	ray_forward(t_ray const *ray, double dist);

double	plane_intersect(t_ray const *ray, t_obj const *obj,
						t_intersect *intersect);
double	sphere_intersect(t_ray const *ray, t_obj const *obj,
						t_intersect *intersect);
static double(*const obj_intersect[O_LAST])(t_ray const *ray, t_obj const *obj,
		t_intersect *intersect) = {
	&sphere_intersect,
	&plane_intersect,
};


void	compute_scene(t_scene const *scene, t_img *img);


//---------------------------------//
//           Phong Model           //
//---------------------------------//


//---------------------------------//
//             DEBUG               //
//---------------------------------//
void	v3_print(t_v3 const v);
void	ray_print(t_ray const *ray);
void	obj_print(t_obj const *obj);
#endif
