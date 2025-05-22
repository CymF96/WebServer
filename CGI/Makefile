# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 17:39:37 by ssottori          #+#    #+#              #
#    Updated: 2025/05/18 00:41:15 by ssottori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============== COLORS =================
MAKEFLAGS += --silent
RED=\033[1;31m
GREEN=\033[1;32m
NC=\033[0m

# ============== COMPILER/FLAGS ============
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic
RM = rm -rf

# ============== FILES ====================
NAME = cgi
SRC_DIR = src
INC_DIR = inc

SRCS = main.cpp \
		$(SRC_DIR)/receiveRequest.cpp \
		$(SRC_DIR)/prepEnv.cpp \
		$(SRC_DIR)/executeScript.cpp \
		$(SRC_DIR)/returnOutput.cpp \
		#$(SRC_DIR)/CgiHandler.cpp \


OBJS = $(SRCS:.cpp=.o)

# ============== RULES ====================
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) -o $(NAME)
	@echo "[$(GREEN)CGI$(NC)] Build complete!"

%.o: %.cpp
	@echo "[$(GREEN)CGI$(NC)] Compiling...$<"
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# ============== CLEAN ====================
clean:
	@echo "[$(RED)CGI$(NC)] Object files..."
	@$(RM) $(OBJS)

fclean: clean
	@echo "[$(RED)CGI$(NC)] Executable..."
	@$(RM) $(NAME)

re: fclean all

leaks:
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re