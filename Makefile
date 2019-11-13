###############################################################################
#                                                                             #
# Makefile                                                                    #
#                                                                             #
###############################################################################

ifeq ($(HOSTTYPE), )
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif

LIBNAME = libft_malloc.so
TARGET = libft_malloc_$(HOSTTYPE).so
SRCDIR = src
OBJDIR = build

MAKEFILE_NAME = Makefile-$(lastword $(subst /, ,$(TARGET)))

CC = gcc
CFLAGS = -fPIC 
LDFLAGS = -shared
SUBDIR = \
				alloc \
				free \
				malloc \
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

SRCS = $(foreach file, $(SUBFILE), $(addprefix $(SRCDIR)/, $(file)))
OBJS = $(subst $(SRCDIR),$(OBJDIR),$(SRCS:.c=.o))

VERBOSE = false
ifeq ($(VERBOSE),true)
	HIDE =  
else
	HIDE = @
endif 
RM = rm -rf 
RMDIR = rm -rf 
MKDIR = mkdir -p
ERRIGNORE = 2>/dev/null
SEP=/
PSEP = $(strip $(SEP))

.PHONY: all directories clean fclean re

all: directories $(TARGET)

$(TARGET): $(OBJS)
	$(HIDE)echo $(MAKEFILE_NAME): Linking $@
	$(HIDE)$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)
	$(HIDE)ln -s $(TARGET) $(LIBNAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo $(MAKEFILE_NAME): Building $@
	$(HIDE)$(CC) $(CFLAGS) -c $(INCLUDES) -o $@ $< -MMD

directories:
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(OBJDIRS)) $(ERRIGNORE)

clean:
	$(HIDE)$(RMDIR) $(subst /,$(PSEP),$(OBJDIRS)) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Build cleaning done !

fclean: clean
	$(HIDE)$(RM) $(TARGET) $(ERRIGNORE)
	$(HIDE)$(RM) $(LIBNAME) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Bin cleaning done !

re: fclean all