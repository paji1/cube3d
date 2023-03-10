# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/31 04:31:34 by tel-mouh          #+#    #+#              #
#    Updated: 2023/03/07 08:12:42 by tel-mouh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash # Use bash syntax

# #################HEADERS###########################
HEADERS = *.h
HEADERS := $(addprefix include/, $(HEADERS))
# #################HEADERS_utils###########################
UHEADERS = 
UHEADERS := $(addprefix include/, $(UHEADERS))

# ################COMMANDS###########################

RM = rm -rf
CC = gcc
HEADERSFLAGS = -I include
CFLAG =   $(HEADERSFLAGS)

# ################SRCS_Objs##########################

SRC = main.c init.c print_functions.c exit_game.c mlx_hook.c point.c draw_line.c vectors.c\
	display_map.c
OBJ = $(addprefix obj/, $(SRC:.c=.o))

# ################SRCS_Objs_Utils####################

SRC_UTILS = 
OBJ_UTILS = $(addprefix obj/utils/, $(SRC_UTILS:.c=.o))

# ################COLOR##############################

COLOR='\033[0;32m'
NC='\033[0m'
RE= '\033[0;34m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'

lines=$(shell tput lines)
CODE_SAVE_CURSOR='\033[s'
CODE_RESTORE_CURSOR='\033[u'
CODE_CURSOR_IN_SCROLL_AREA="\033[1A"

# ###############executable##########################

NAME = ./cube3d
# LIBFT = libft/library/libft.a
# ILIBFT = libft/include
x  = -1

# ###################################################

all : $(NAME)

$(NAME): $(OBJ) $(OBJ_UTILS)
	@printf  ${CODE_RESTORE_CURSOR}""
	@tput el
	@ printf ${GREEN}"\rMaking is done ???\n"${NC}
	@ tput cvvis
	@$(CC) $(CFLAG)  $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -g -o $(NAME)

# library :
# 	@ make -C libft

obj/%.o : src/%.c  $(HEADERS) $(UHEADERS)
	@ mkdir -p obj
	@ mkdir -p obj/utils
	@ $(CC) $(CFLAG) -I/usr/include -Imlx_linux -O3 -g -c -lm $< -o $@
	@tput civis
	$(eval x=$(x)+1)
	@ printf $(notdir $@)"\n"
	@ printf  ${CODE_SAVE_CURSOR}""
	@ printf "\033[$(lines);0f"
	@ sleep 0.05
	@number=$x ; while [[ $$number -ge 0 ]] ; do \
        printf ${YELLOW}"????"${NC}  ;\
        ((number = number - 1)) ; \
    done
	@printf  ${CODE_RESTORE_CURSOR}""
	@printf  ${CODE_CURSOR_IN_SCROLL_AREA}""
	@printf  ${CODE_SAVE_CURSOR}""
	@printf ${RE}"???? Making the  --> "${NC} 
	@tput el

clean :
	@ $(RM) $(OBJ)
	@ $(RM) $(OBJ_UTILS)

# @ make clean -C libft
fclean : clean
	@ $(RM) $(NAME)

#@ make fclean -C libft

re : fclean all