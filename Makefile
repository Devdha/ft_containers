CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf
NAME = ft
STD = std
VECTOR = vector

VECTOR_SRCS = vector_test.cpp
VECTOR_OBJS = $(addprefix $(OBJ_DIR)/, $(VECTOR_SRCS:.cpp=.o))

SRCS = main.cpp \
				vector_test.cpp \
				map_test.cpp \
				stack_test.cpp \
				set_test.cpp \
				util_test.cpp
INCS = vector.hpp \
				stack.hpp \
				map.hpp \
				set.hpp \
				rbtree.hpp \
				algorithm.hpp \
				iterator.hpp \
				type_traits.hpp \
				pair.hpp
OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

$(NAME): $(OBJS) $(INCS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $@ -D $(NAME)
	@printf "💡 Make $(NAME) Done\n"

$(STD): $(OBJS) $(INCS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $@ -D $(STD)
	@printf "💡 Make $(STD) Done\n"


$(VECTOR): $(VECTOR_OBJS) $(INCS)
	@$(CXX) $(CXXFLAGS) $(VECTOR_OBJS) -o $@
	@printf "💡 Make $(VECTOR) Done\n"
	@./vector

$(OBJ_DIR)/%.o : %.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -g

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