NAME = libft.a
CC = gcc
SRCS = 	$(wildcard *.c)

OBJS = $(SRCS:.c=.o)
TOTAL_FILES = $(words $(SRCS))
COMPLETED_FILES = 0
FLAGS = -Wall -Wextra -Werror

RM = rm -f

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)
	@echo
	@echo "\033[32m[✓] libft succesfully compiled\033[0m"

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@
	$(eval COMPLETED_FILES=$(shell echo $$(($(COMPLETED_FILES)+1))))
	@echo -n "\033[32m[" && i=0 ; while [ $$i -lt $(TOTAL_FILES) ] ; do if [ $$i -lt $(COMPLETED_FILES) ] ; then echo -n "▉" ; else echo -n " " ; fi ; i=$$((i+1)) ; done && echo -n "] $(COMPLETED_FILES)/$(TOTAL_FILES)\033[0m\r"

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all