CC = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf
NAME = megaphone

SRCS = megaphone.cpp
OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

$(NAME): $(OBJS)
	@$(CC) $(CXXFLAGS) $(OBJS) -o $@
	@printf "💡 Make $(NAME) Done\n"

$(OBJ_DIR)/%.o : %.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CXXFLAGS) -c $< -o $@ -g

all: $(NAME)

clean :
	@$(RM) $(OBJ_DIR)
	@echo "🗑 Remove $(NAME)'s OBJs Done"

fclean : clean
	@$(RM) $(NAME)
	@echo "🗑 Remove $(NAME) Done"

re:
	@make fclean all

.PHONY : all clean fclean re