NAME		= corewar


SRC_DIR		= ./src
INC_DIR		= ./includes
OBJ_DIR		= ./obj
LIB_DIR		= ./lib



SRC			= main.c \
			  util.c \
			  conversion.c \
			  execution.c \
			  fetch_instructions.c \
			  process_list_api.c \
			  decode_params.c \
			  vm.c \
			  vm_loop.c \
			  ops.c \
			  fetch_cur_ops.c \
			  load_champions.c

OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


CC			= gcc
CFLAGS          = -g
CFLAG		= -Wall -Werror -Wextra 


L_FT		= $(LIB_DIR)/libft
LIB_LNK		= -L $(L_FT) -lft
LIB_INC		= $(L_FT)/includes

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $@/vm

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIB_INC) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(MAKE) -C $(L_FT)
	$(CC) -o $@ $(OBJ) $(LIB_LNK)

clean:
	@$(MAKE) clean -C $(L_FT)
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(L_FT)
	rm -rf $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all
