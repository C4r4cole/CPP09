# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 14:02:02 by fmoulin           #+#    #+#              #
#    Updated: 2026/05/28 12:09:04 by fmoulin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===========================
#           CONFIG
# ===========================

NAME        = PmergeMe

OBJ_DIR     = obj

CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98
RM          = rm -f

# ===========================
#           SOURCES
# ===========================

SRCS =  main.cpp PmergeMe.cpp
		
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

# ===========================
#           RULES
# ===========================

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
