NAME	= libft.a

SRCS	= ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memalloc.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strlowcase.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_strcmp.c	\
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putendl_fd.c \
		ft_putendl.c \
		ft_print_error.c	\
		ft_putnbr_fd.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_abs.c \
		ft_isspace.c \
		ft_atof.c

SRCS_BONUS	= ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

OBJS	=	${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}


CC	=	gcc

CFLAGS	=	 -g3


${NAME}:
	@${CC} ${CFLAGS} ${SRCS} -c
	@ar rc ${NAME} ${OBJS}
	@ranlib ${NAME}

all: ${NAME}
	

bonus:
	@${CC} ${CFLAGS} ${SRCS_BONUS} -c
	@ar rc ${NAME} ${OBJS_BONUS}
	@ranlib ${NAME}

clean:
	@rm -f ${OBJS} ${OBJS_BONUS}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: re fclean clean bonus all
