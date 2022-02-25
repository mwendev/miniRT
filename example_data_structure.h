
typedef struct s_ambient
{
	float	ratio;
	int		RGB[3]; /* maybe convert to single int color immediately during parsing ? */
}	t_ambient;

typedef struct s_camera
{
	float	coord[3];
	float	orient[3];
}	t_camera;

typedef struct s_light
{
	float	coord[3];
	float	orient[3];
	int		RGB[3]; /* same as ambient */
}	t_light;

typedef struct s_sphere
{
	float	coord[3];
	float	diameter;
	int		RGB[3]; /* same as ambient */
}	t_sphere;

typedef struct s_plane
{
	float	coord[3];
	float	orient[3];
	int		RGB[3]; /* same as ambient */
}	t_plane;

typedef struct s_cylinder
{
	float	coord[3];
	float	orient[3];
	float	diameter;
	float	height;
	int		RGB[3]; /* same as ambient */
}	t_cylinder;

typedef struct s_data
{
	void	*img;
	void	*mlx;
	void	*mlx_win;
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
}	t_data;
