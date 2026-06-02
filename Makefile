# ================================ COLORS ================================== #
RESET		=	\033[0m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
MAGENTA		=	\033[35m
CYAN		=	\033[36m
WHITE		=	\033[37m
BOLD		=	\033[1m
BLACK 		=	\033[30m
ITALIC		=	\033[3m

# =============================== PROJECT =================================== #
NAME		=	philosophers
COMPILER	=	gcc
FLAGS		=	-Wall -Wextra -Werror
OBJS_DIR	=	objs

# ================================ FILES ==================================== #
FILES		=	./src/main.c \
				./src/cleanup.c \
				./src/initialize_args.c \
				./src/initialize_table.c \
				./src/routine.c \
				./src/start_dinner.c \
				./src/utils.c \
				./src/monitor.c \


OBJS		=	$(patsubst %.c,$(OBJS_DIR)/%.o,$(FILES))

# =============================== TARGETS =================================== #
all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(CYAN)$(BOLD)🔗 Linking $(NAME)...$(RESET)\n"
	@$(COMPILER) $(FLAGS) $(OBJS) -o $(NAME)
	@printf "$(GREEN)$(BOLD)✅ $(NAME) successfully compiled!$(RESET)\n\n"
	@printf "\n"
	@printf "            ________o8A888888o_                     \n"
	@printf "        _o888888888888K_1888888o                    \n"
	@printf "                  ~~~+8888888888o                   \n"
	@printf "                      ~8888888888                   \n"
	@printf "                      o88888888888                  \n"
	@printf "                     o8888888888888                 \n"
	@printf "                   _8888888888888888                \n"
	@printf "                  o888888888888888888_              \n"
	@printf "                 o88888888888888888888_             \n"
	@printf "                _8888888888888888888888_            \n"
	@printf "                888888888888888888888888_           \n"
	@printf "                8888888888888888888888888           \n"
	@printf "                88888888888888888888888888          \n"
	@printf "                88888888888888888888888888          \n"
	@printf "                888888888888888888888888888         \n"
	@printf "                ~88888888888888888888888888_        \n"
	@printf "                 488888888888888888888888888        \n"
	@printf "                  888888888888888888888888888       \n"
	@printf "                   888888888888888888888888888_     \n"
	@printf "                   ~8888888888888888888888888888    \n"
	@printf "                     +88888888888888888888~~~~~     \n"
	@printf "                      ~=888888888888888888o         \n"
	@printf "               _=oooooooo888888888888888888         \n"
	@printf "                _o88=8888==~88888888===8888         \n"
	@printf "                ~   =~~ _o88888888=      ~~~        \n"
	@printf "                        ~ o8=~88=~                  \n"
	@printf "$(YELLOW)    🐧 TioElvis says: Great job! Your program is ready! 🐧$(RESET)\n\n"

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)🔨 Compiling $<...$(RESET)\n"
	@$(COMPILER) $(FLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@printf "$(BLUE)📁 Creating objects directory...$(RESET)\n"

clean:
	@printf "$(RED)🧹 Cleaning object files...$(RESET)\n"
	@rm -rf $(OBJS_DIR)
	@printf "$(GREEN)✨ Clean completed!$(RESET)\n"

fclean: clean
	@printf "$(RED)🗑️  Removing $(NAME)...$(RESET)\n"
	@rm -f $(NAME)
	@printf "$(GREEN)✨ Full clean completed!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re