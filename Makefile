NAME = webserv
CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
INC_DIR = INC/utils
SRC_DIR = SRC
OBJ_DIR = OBJ
SRC = $(SRC_DIR)/Server.cpp \
      $(SRC_DIR)/Socket.cpp \
	  $(SRC_DIR)/Location.cpp \
	  $(SRC_DIR)/ServerManager.cpp \
	  $(SRC_DIR)/Utils.cpp \
      $(SRC_DIR)/main.cpp 
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
INC = $(INC_DIR)/Colors.hpp \
	  $(INC_DIR)/Webserver.hpp \
	  $(INC_DIR)/Socket.hpp \
	  $(INC_DIR)/Server.hpp \
	  $(INC_DIR)/Location.hpp \
	  $(INC_DIR)/Utils.hpp \
	  $(INC_DIR)/ServerManager.hpp \

all : $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)
	@echo "Executable $(NAME) created!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -I $(INC_DIR) -c $< -o $@
	@echo "Compiled $< into $@"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Object files and directories removed."

fclean: clean
	@rm -f $(NAME)
	@echo "Executable $(NAME) removed."

re: fclean all

.PHONY: all clean fclean re
