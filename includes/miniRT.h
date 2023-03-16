#ifndef MINIRT_H
# define MINIRT_H

//---------------------------------//
//             config              //
//---------------------------------//
# define WIN_NAME		"-- MiniRT --"
# define WIN_W			1680
# define WIN_H			1050
# define DESTROY_NOTIFY	17

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
//           RT Objects            //
//---------------------------------//

typedef struct s_v3
{
	double	x;
	double	y;
	double	z;
}	t_v3;

typedef struct s_ray
{
	t_v3	origin;
	t_v3	dir;
}	t_ray;

typedef struct s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_color;

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
	double	strength;
	t_color	color;
}	t_ambiant;

typedef struct s_light
{
	t_v3	origin;
	double	strength;
	t_color	color;
}	t_light;

typedef struct s_plan
{
	t_v3	origin;
	t_v3	normal;
	t_color	color;
}	t_plan;

typedef enum e_OType
{
	O_PLAN,
	O_LAST
}	t_OType;

typedef struct s_obj
{
	t_OType	type;
	union u_obj
	{
		t_plan	plan;
	}	data;
}	t_obj;
/*
typedef struct s_scene
{
	t_cam		cam;
	t_ambiant	ambiant;
	t_list		*lights;
	t_list		*objs;
}	t_scene;
*/
typedef struct s_intersect
{
	t_obj	*obj;
	t_v3	point;
	t_v3	normal;
}	t_intersect;

void	init_cam_dir(t_cam *cam, t_v3 const dir);
t_ray	cam_pixel_to_ray(t_cam const *cam, int i, int j);

static const t_v3	V_ZERO = {0, 0, 0};
t_v3	v_normalize(t_v3 v);

#endif
