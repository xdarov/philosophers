NAME =				philo

NAME_B =			philo_bonus

SRCS =				philo.c philo_utils.c philo_main.c

SRCS_B = 			philo_bonus.c philo_utils_bonus.c philo_main_bonus.c

LIB_PATH =			libft/

OBJ_DIR =			obj

HEADER =			philo.h

HEADER_B =			philo_bonus.h

OBJ =				$(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRCS)))

OBJ_B =				$(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRCS_B)))

CC =				gcc

FLAGS =				-g -Wall -Wextra -Werror

.PHONY:				all bonus makelibft clean fclean re

all:				makelibft $(NAME) $(NAME_B)

makelibft:			
					@make -C $(LIB_PATH) all

$(NAME):			$(HEADER) $(OBJ)
					$(CC) $(FLAGS) -I$(HEADER) $(OBJ) $(LIB_PATH)libft.a -o $(NAME)

bonus:				makelibft $(NAME_B)

$(NAME_B):			$(HEADER_B) $(OBJ_B)
					$(CC) $(FLAGS) -I$(HEADER_B) $(OBJ_B) $(LIB_PATH)libft.a -o $(NAME_B)

$(OBJ_DIR)/%.o:		%.c	$(HEADER)
					@mkdir -p $(OBJ_DIR)
					$(CC) -g -c $< -o $@

clean:
					@rm -rf $(OBJ_DIR)
					@make -C $(LIB_PATH) clean

fclean:				clean
					@rm -f $(NAME) $(NAME_B)
					@make -C $(LIB_PATH) fclean

re:					fclean all