## ARGUMENTS
CLIENT_NAME		= client
SERVER_NAME		= server

## DIRECTORIES
SRC_DIR			= source
INC_DIR			= include

## SOURCE FILES
CLIENT_SRCS		= $(SRC_DIR)/client.c
SERVER_SRCS		= $(SRC_DIR)/server.c
UTILS_SRCS		= $(SRC_DIR)/utils.c

## OBJECT FILES
CLIENT_OBJS		= $(CLIENT_SRCS:.c=.o) $(UTILS_SRCS:.c=.o)
SERVER_OBJS		= $(SERVER_SRCS:.c=.o) $(UTILS_SRCS:.c=.o)

## COMPILATION & FLAGS
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pedantic -g -Wunreachable-code -I $(INC_DIR)
AR 			= ar rcs
RM			= rm -f

## TARGETS

all:				$(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME):		$(CLIENT_OBJS)
					$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $(CLIENT_NAME)

$(SERVER_NAME):		$(SERVER_OBJS)
					$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(SERVER_NAME)

$(SRC_DIR)/%.o:		$(SRC_DIR)/%.c
					$(CC) $(CFLAGS) -c $< -o $@

clean:
					$(RM) $(CLIENT_OBJS) $(SERVER_OBJS)

fclean:				clean
					$(RM) $(CLIENT_NAME) $(SERVER_NAME)

re:					fclean all

.PHONY: 			all clean fclean re
