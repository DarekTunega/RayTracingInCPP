NAME = raytracer
CFLAGS = -Wall -Wextra -Werror 
CC = g++

SRC_DIRS = srcs srcs/rendering srcs/math srcs/physics
INCLUDE_PATH = includes/

MAIN_SRC = main.cpp
MATH_SRC = Tuple.cpp Matrix.cpp
RENDERING_SRC = Canvas.cpp Color.cpp
PHYSICS_SRC = Enviroment.cpp Projectile.cpp

SRC = $(addprefix srcs/, $(MAIN_SRC)) \
      $(addprefix srcs/physics/, $(PHYSICS_SRC)) \
      $(addprefix srcs/math/, $(MATH_SRC)) \
      $(addprefix srcs/rendering/, $(RENDERING_SRC))

OBJ_PATH = objects/
OBJ = $(notdir $(SRC:.cpp=.o))
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

INC_FLAGS = $(addprefix -I, $(INCLUDE_PATH) $(SRC_DIRS))

VPATH = $(SRC_DIRS)

all: $(NAME)

$(OBJ_PATH)%.o: %.cpp
	@mkdir -p $(OBJ_PATH)
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "Linking $@"
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo "Done"

clean:
	@echo "Cleaning up object files..."
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "Cleaning up executable and ppm files..."
	@rm -f $(NAME)
	@rm -f *.ppm

re: fclean all

.PHONY: all clean fclean re
