CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf
NAME = ft
STD = std

SRCS = main.cpp \
				test.cpp \
				vector_test.cpp \
				map_test.cpp \
				stack_test.cpp \
				set_test.cpp \
				util_test.cpp

SUB_SRCS = sub.cpp

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
SUB_OBJS = $(addprefix $(OBJ_DIR)/, $(SUB_SRCS:.cpp=.o))

$(NAME): $(OBJS) $(INCS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $@
	@printf "💡 Make $(NAME) Done\n"

$(STD): $(INCS)
	@$(CXX) $(CXXFLAGS) $(SRCS) -o $@ -D STD
	@printf "💡 Make $(STD) Done\n"

test:
	@make sub
	@make sub_std
	time ./sub $(SEED)
	time ./sub_std $(SEED)

sub : $(SUB_OBJS) $(INCS)
	@$(CXX) $(CXXFLAGS) $(SUB_OBJS) -o $@
	@printf "💡 Make sub Done\n"

sub_std : $(INCS)
	@$(CXX) $(CXXFLAGS) $(SUB_SRCS) -o $@ -D STD
	@printf "💡 Make sub_std Done\n"

$(OBJ_DIR)/%.o : %.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -g

all: $(NAME)

diff: $(NAME) $(STD)
	@./$(NAME) > $(NAME).out
	@./$(STD) > $(STD).out
	@printf "🍽  "
	diff $(NAME).out $(STD).out

clean :
	@$(RM) $(OBJ_DIR)
	@echo "🗑 Remove test OBJs Done"

fclean : clean
	@$(RM) $(NAME) $(STD) $(NAME).out $(STD).out sub sub_std
	@echo "🗑 Remove test Done"

re:
	@make fclean all

.PHONY : all clean fclean re