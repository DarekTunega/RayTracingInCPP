CFLAGS = -Wall -Wextra -Werror 
CC = g++
SCR_PATH = srcs/
SRCS = $(addprefix $(SCR_PATH), $(SRC))
OBJECTS = $(SRC:.cpp=.o)
OBJ_PATH = objects/
OBJS = $(OBJECTS)
OBJ_FILES = $(addprefix $(OBJ_PATH), $(OBJS))
NAME = Raytracer
SRC = main.cpp Tuple.cpp Enviroment.cpp Projectile.cpp Color.cpp Canvas.cpp Matrix.cpp

all: $(NAME)
$(OBJ_PATH)%.o: $(SCR_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	echo "Compiling $< to $@"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling $< to $@"

$(NAME): $(OBJ_FILES)
	@echo "Linking $@"
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES)
	@echo "Linking $@"
	@echo "Done"

clean:
	@echo "Cleaning up object files..."
	@rm -f $(OBJ_FILES)
	@rm -rf objects/

fclean: clean
	@echo "Cleaning up executable, object folder files, and ppm file..."
	@rm -f $(NAME)
	@rm -f *.ppm

re: fclean all
	@echo "Rebuilding..."
	@echo "Done"

.PHONY: all clean fclean re
