NAME = miniRT
BONUS = miniRT_bonus

CC = cc
UNAME_S := $(shell uname -s)
PKG_CONFIG ?= pkg-config

MLX_DIR = mlx_linux
MLX_MAKEFILE = $(MLX_DIR)/Makefile.mk
MLX_LIB = $(MLX_DIR)/libmlx.a

X11_INC := $(shell $(PKG_CONFIG) --variable=includedir x11 2>/dev/null)
X11_CFLAGS := $(shell $(PKG_CONFIG) --cflags x11 xext 2>/dev/null)
X11_LIBS := $(shell $(PKG_CONFIG) --libs x11 xext 2>/dev/null)

ifeq ($(strip $(X11_INC)),)
ifeq ($(UNAME_S),Darwin)
ifneq ($(wildcard /opt/X11/include/X11/Xlib.h),)
X11_PREFIX := /opt/X11
else
X11_PREFIX := $(shell brew --prefix 2>/dev/null)
endif
X11_INC := $(X11_PREFIX)/include
X11_CFLAGS := -I$(X11_INC)
X11_LIBS := -L$(X11_PREFIX)/lib -lXext -lX11
else
X11_INC := /usr/include
X11_LIBS := -lXext -lX11
endif
endif

CPPFLAGS = -Ilibft -I$(MLX_DIR) $(X11_CFLAGS)
CFLAGS = -O3
LDFLAGS = -Llibft -L$(MLX_DIR)
LDLIBS = -lft -lmlx $(X11_LIBS) -lm

SRCS =	aabb.c aabb_utils.c bvh_node.c  camera.c\
		color.c  hittable.c  camera_utils.c \
		main.c wrapper_func.c \
		qsort.c  ray.c bvh_node_func.c bvh_utils.c \
		raytracing.c matrix_basic.c matrix_create.c \
		hittable_list.c wrapper.c  \
		mlx_func.c key_events.c rotation.c translate.c \
		mouse_events.c matrix.c wrapper_plane.c \
		parser.c parser_object.c parser_utils.c parser_cam_light.c \
		parser_validation.c validate_texture.c init.c parser_validation1.c \
		create_object.c create_object1.c parser_utils1.c \
		hittable_list_func.c wrapper_plane_func.c \
		key_events_obj.c

#instance.c
# MATERIALS = $(addprefix materials/, lambertian.c diffuse_light.c)
FIGURES	= $(addprefix figures/, sphere.c circle.c cylinder.c pillar.c hyperboloid.c)   #plane.c quad.c  triangle.c box.c 
MATH = $(addprefix math/, vector_basic.c vector_utils.c vector.c quaternion.c interval.c vector_init.c)
TEXTURES = $(addprefix textures/, bumpmap.c checker.c image.c solid.c)
# SRCS += $(MATERIALS)
SRCS += $(FIGURES)
SRCS += $(MATH)
SRCS += $(TEXTURES)

MANDATORY_SRCS = $(addprefix mandatory/, $(SRCS))

BONUS_SRCS = $(addprefix bonus/, $(SRCS))
BONUS_SRCS += bonus/get_checker_scale_bonus.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(MANDATORY_SRCS) $(MLX_LIB) libft/libft.a
	$(CC) $(CPPFLAGS) $(CFLAGS) $(MANDATORY_SRCS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

bonus : $(BONUS)

$(BONUS): $(BONUS_SRCS) $(MLX_LIB) libft/libft.a
	$(CC) $(CPPFLAGS) $(CFLAGS) $(BONUS_SRCS) $(LDFLAGS) $(LDLIBS) -o $(BONUS)

libft/libft.a:
	$(MAKE) -C libft

$(MLX_MAKEFILE):
	@test ! -e "$(MLX_DIR)" || { \
		echo "$(MLX_DIR) is incomplete (missing Makefile.mk)" >&2; exit 1; \
	}
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)

$(MLX_LIB): $(MLX_MAKEFILE)
	@test -n "$(strip $(X11_INC))" || { \
		echo "X11 headers not found" >&2; exit 1; \
	}
	$(MAKE) -C $(MLX_DIR) -f Makefile.mk \
		CC="$(CC)" INC="$(X11_INC)" IFLAGS="$(X11_CFLAGS)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C libft fclean
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
