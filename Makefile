###############################################################################
#                                                                             #
# Makefile                                                                    #
#                                                                             #
###############################################################################

ifeq ($(HOSTTYPE), )
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif

LIBNAME = libft_malloc.so
NAME = libft_malloc_$(HOSTTYPE).so
SRCDIR = src
OBJDIR = build

MAKEFILE_NAME = Makefile-$(lastword $(subst /, ,$(LIBNAME)))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC -pthread
LDFLAGS = -shared
SUBDIR = \
			alloc \
			free \
			malloc \
			calloc \
			realloc \
			reallocf \
			show \
			libft
SUBFILE = \
			alloc/ft_alloc_search.c \
			alloc/ft_alloc_history.c \
			alloc/ft_alloc_init.c \
			alloc/ft_alloc_chunk.c \
			alloc/ft_alloc_arena.c \
			malloc/ft_malloc.c \
			free/ft_free.c \
			realloc/ft_realloc.c \
			calloc/ft_calloc.c \
			reallocf/ft_reallocf.c \
			show/ft_show_history.c \
			show/ft_show_mem.c \
			libft/ft_memcpy.c \
			libft/ft_memset.c \
			libft/ft_putnbr.c \
			libft/ft_putstr.c \
			libft/ft_memmove.c

SRCDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(SRCDIR)/, $(dir)))
OBJDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(OBJDIR)/, $(dir)))
INCLUDES = $(foreach dir, $(SRCDIRS), $(addprefix -I, $(dir)))

SRCS = $(foreach file, $(SUBFILE), $(addprefix $(SRCDIR)/, $(file)))
OBJS = $(subst $(SRCDIR),$(OBJDIR),$(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

VERBOSE = FALSE
ifeq ($(VERBOSE),TRUE)
	HIDE =  
else
	HIDE = @
endif
MAKE = make -C
RM = rm -rf
MKDIR = mkdir -p
ERRIGNORE = 2>/dev/null

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJDIRS) $(OBJS) 
	$(HIDE)echo $(MAKEFILE_NAME): "Linking \t ->" $@
	$(HIDE)$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	$(HIDE)ln -s $(NAME) $(LIBNAME)

-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo $(MAKEFILE_NAME): "Building \t ->" $@
	$(HIDE)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD

$(OBJDIRS):
	@echo $(MAKEFILE_NAME): "Making  \t ->" $(OBJDIRS)
	$(HIDE)$(MKDIR) $(OBJDIRS) $(ERRIGNORE)

clean:
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Clean done !

fclean: clean
	$(HIDE)$(RM) $(NAME) $(ERRIGNORE)
	$(HIDE)$(RM) $(LIBNAME) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Fclean done !

re: fclean all