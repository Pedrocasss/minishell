# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 11:20:48 by paugonca          #+#    #+#              #
#    Updated: 2023/10/26 11:12:48 by paugonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(VERBOSE).SILENT:

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g #-fsanitize=address

RM          = rm -f
MKD         = mkdir -p

SRC_PATH    = ./src
OBJ_PATH    = ./obj

SRC_NAME    = main.c						\
              env_utils.c					\
			  exit_stts.c					\
			  fd_utils.c					\
			  parser/parser.c				\
			  parser/parser_utils.c			\
			  parser/tree_init.c			\
			  parser/tree_utils.c			\
			  parser/pipe_utils.c			\
			  parser/signs_utils.c			\
			  parser/quotes_utils.c			\
			  parser/tilde_utils.c			\
			  parser/syntax_utils.c			\
			  parser/var_utils.c			\
			  parser/get_stts_utils.c		\
			  builtins/builtin_utils.c		\
			  builtins/ft_cd.c				\
			  builtins/ft_cd_utils.c		\
			  builtins/ft_echo.c			\
			  builtins/ft_env.c				\
			  builtins/ft_exit.c			\
			  builtins/ft_export.c			\
			  builtins/ft_export_utils.c	\
			  builtins/ft_pwd.c				\
			  builtins/ft_unset.c			\
              executor/executor.c			\
			  executor/executor_handy.c		\
			  executor/cmd_utils.c			\
              executor/path_utils.c			\
			  executor/sig_utils.c			\
			  executor/termios_utils.c		\
			  executor/redir_utils.c		\
			  executor/redir_in_utils.c		\
			  executor/redir_out_utils.c	\
			  executor/redir_builtins.c		\
			  executor/heredoc_utils.c		\
			  executor/reset_the_term.c		\
              extra/free_utils.c			\
			  extra/print_utils.c			\
			  extra/soups_utils.c

SRC         = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ         = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))
DEPS        = ./libft/libft.a -lreadline

LIBFT_PATH  = ./libft

all: $(NAME)

$(LIBFT_PATH)/libft.a:
	@echo "Compiling libft..."
	make -C $(LIBFT_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@$(MKD) -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(DEPS) $(OBJ)
	@echo "Compiling minishell..."
	@$(CC) $(CFLAGS) $(OBJ) $(DEPS) -o $(NAME)
	@echo "minishell compiled sucessfully!"

clean:
	@echo "Removing object files..."
	make clean -C $(LIBFT_PATH)
	$(RM) -r $(OBJ_PATH)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	@echo "Removing minishell..."
	$(RM) $(NAME)

re: fclean all

run: re
	@clear
#	@valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes ./minishell
	@./minishell

.PHONY: all clean fclean re
