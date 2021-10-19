# COLORS

GREEN	= \033[0;32m
RED		= \033[0;31m
BLUE	= \033[0;34m
GREY	= \033[38;5;240m
WHITE	= \033[0;37m
QUIT	= \033[0m

# MACROS

NAME	=	cub3d	
SRCS	=	$(wildcard cfiles/*.c)
DIR_O	=	OBJ/
OBJS	=	$(SRCS:cfiles/%.c=OBJ/%.o)
DOTH	=	extras/hfiles
LIBFT	=	extras/libft
MLX		=	-L /usr/local/lib -lmlx -framework OpenGL -framework Appkit	
LFT_EXE	=	extras/libft
CC		=	gcc

#UPDATE READLINE via brew because the Mac one is too old

CFLAGS	=	-Wall -Wextra -Werror
LDFLAGS = 	-g -fsanitize=address 
INCLUDE	=	-I./$(DOTH) -I./$(LIBFT) -I /usr/local/include
LINKS	=	-L./$(LIBFT) -lft $(MLX) 

# RULES

all:	$(NAME)

$(NAME): libft $(DIR_O) $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(wildcard cfiles/*.c) $(wildcard extras/libft/*c) -o $(NAME) $(LINKS)
	@echo "\n$(GREEN)\n"
	@cat ./fonts/cub3d.txt
	@echo "\n$(RESET)\n"

$(DIR_O)%.o: cfiles/%.c
	@$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@
	@echo "$(GREEN)#$(RESET)\c"

$(OBJS): $(DIR_O)

$(DIR_O):
	@mkdir -p $(DIR_O)

libft:
	@echo "$(WHITE) [ .. ] Creating LIBFT [ .. ]$(RESET)"
	@make -C $(LIBFT)
	@echo "\n$(GREEN)\n"
	@cat ./fonts/libft.txt
	@echo "$(WHITE) \n\n\n[ .. ] Creating '$(NAME)' [ .. ]$(RESET)"

clean:
	@echo "$(RED) [ .. ] Deleting LIBFT [ .. ]"
	@echo "$(RED)"
	@make -C $(LIBFT) fclean
	@cat ./fonts/libft_deleted.txt
	@echo "$(RESET)"
	@echo "$(RED) [ .. ] Deleting .o files [ .. ]$(RESET)"
	@rm -fr $(DIR_O)

fclean:	clean
	@echo "$(RED) [ .. ] Deleting '$(NAME)' executable  [ .. ]$(RESET)"
	@rm -fr $(NAME)
	@cat	./fonts/cub3d_deleted.txt
	@echo "$(RESET)"

re:		fclean all

.PHONY	=	all clean fclean re
