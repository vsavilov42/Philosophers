# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/18 15:11:03 by Vsavilov          #+#    #+#              #
#    Updated: 2022/06/22 21:57:22 by Vsavilov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############################
###   Program/s name/s   ###
############################

NAME = philo

LIBFT_NAME = libft.a

##############################
###   Compiler and flags   ###
##############################

CC = gcc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3

CFLAGS += -I ./$(INC_PATH) -I ./$(LIBFT)/inc

#################
###   Paths   ###
#################

SRC_PATH = src

OBJ_PATH = obj

INC_PATH = inc

LIBFT = libft

########################
###   Source items   ###
########################

SRCS_NAME = main.c

#####################
###   Make rule   ###
#####################

MAKE = make

##########################
###   Create objects   ###
##########################

OBJS_NAME = $(SRCS_NAME:%.c=%.o)

SRCS = $(addprefix $(SRC_PATH)/, $(SRCS_NAME))

OBJS = $(addprefix $(OBJ_PATH)/, $(OBJS_NAME))

#################################
###   Rules can be executed   ###
#################################

all: $(NAME)

#######################
###   Objects dir   ###
#######################

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH) 2> /dev/null

$(LIBS_DIR):
	mkdir -p $(LIBS-DIR) 2> /dev/null

#########################
###   Compile libs   ###
#########################

$(LIBFT_NAME):
	$(MAKE) all -sC $(LIBFT)
	cp -r $(addprefix $(LIBFT)/, $(LIBFT_NAME)) $(LIBFT_NAME)

#####################
###   Compile.o   ###
#####################

$(NAME): $(LIBFT_NAME) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_NAME)

#######################
###   Other rules   ###
#######################

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	$(MAKE) fclean -sC $(LIBFT)
	rm -rf $(NAME)
	rm $(LIBFT_NAME)

re: fclean all

funsiona:
	norminette $(INC_PATH)
	norminette $(SRC_PATH)

.PHONY: all clean fclean re funsiona
