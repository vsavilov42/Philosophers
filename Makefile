# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/18 15:11:03 by Vsavilov          #+#    #+#              #
#    Updated: 2022/07/14 12:45:36 by Vsavilov         ###   ########.fr        #
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

CFLAGS = -Wall -Werror -Wextra

CFLAGS += -I ./$(INC_PATH)

CFLAGS += -fsanitize=address

#################
###   Paths   ###
#################

SRC_PATH = src

OBJ_PATH = obj

INC_PATH = inc

########################
###   Source items   ###
########################

SRCS_NAME = main.c \
	    parse.c \
	    philo.c \
	    philo_utils.c \
	    printer.c \
	    libft_utils.c

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

#####################
###   Compile.o   ###
#####################

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

#######################
###   Other rules   ###
#######################

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

funsiona:
	norminette $(INC_PATH)
	norminette $(SRC_PATH)

.PHONY: all clean fclean re funsiona
