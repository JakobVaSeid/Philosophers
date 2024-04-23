# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/04/23 13:42:45 by jseidere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


RED = \033[38;5;196;1m
ORANGE = \033[38;5;208;1m
YELLOW = \033[38;5;226;1m
GREEN = \033[38;5;082;1m
BLUE = \033[38;5;027;1m
INDIGO = \033[38;5;093;1m
VIOLET = \033[38;5;163;1m
WHITE = \033[38;5;231;1m
BROWN = \033[38;5;137;1m
END = \033[0m

NAME = philoshers

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RFLAGS = -pthread
DEPFLAGS =-MT $@ -MMD -MP -MF $(OBJ_DIR)/$*.d
RM = rm -rf

MAIN =	test.c

SRCS =	$(MAIN)
			
OBJ_DIR = object/
OBJS =  $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
DEPS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.d))

all: $(NAME) 

object/%.o: source/%.c
	@mkdir -p $(dir $@)
	@printf "$(ORANGE). $(END)";
	@$(CC) -c $(CFLAGS) $(DEPFLAGS) $< -o $@

$(NAME): $(OBJS) 
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME) $(RFLAGS)
	@$(RM) heredocs
	@mkdir heredocs
	@printf "\r$(GREEN)🚀 ./$(NAME)          created                                                                     \n$(END)"


clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(RED)💥 object files\t\tremoved\n$(END)"

fclean: clean cleanf
	@$(RM) $(NAME)
	@$(RM) test
	@$(RM) heredocs
	@printf "$(RED)💥 ./$(NAME) \t\tremoved\n$(END)"

cleanf:
	@find . -depth -maxdepth 1 -name ".git" -prune -o  -type f ! -name "*.c" ! -name "*.h" ! -name "*.json" ! -name "minishell" ! -name "README.md" ! -name ".gitignore" ! -name Makefile -delete 
	@printf "$(RED)💥 test & useless files removed\n$(END)"

re: _rebuild fclean all

_rebuild:
	@printf "$(ORANGE)🚧 ./$(NAME)\t\trebuild\n$(END)"

nothing:
	@printf "💩$(BROWN) made $(RED)n$(ORANGE)o$(YELLOW)t$(GREEN)h$(BLUE)i$(INDIGO)n$(VIOLET)g\n$(END)"

-include $(DEPS)

.PHONY: all bonus both clean fclean re _rebuild nothing