NAME =				avm

CC =				clang++ -std=c++11

# FLAGS =				-Wall -Werror -Wextra -g

INC_DIR =			-I ./includes/

SRC_DIR =			./sources/
SRC_AVM =			main.cpp AbstractVM.cpp

OBJ_DIR =			./objects/

OBJ_AVM =			$(addprefix $(OBJ_DIR), $(SRC_AVM:.cpp=.opp))

all: $(NAME)

$(NAME): $(OBJ_AVM)
	$(CC) -o $(NAME) $(FLAGS) $(INC_DIR) $(OBJ_AVM)

$(OBJ_DIR)%.opp: $(SRC_DIR)%.cpp
	@/bin/mkdir -p $(OBJ_DIR)
	$(CC) -c $(FLAGS) $(INC_DIR) $< -o $@

clean:
	rm -rf $(OBJ_AVM) $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all