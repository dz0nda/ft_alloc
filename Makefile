###############################################################################
#                                                                             #
# Makefile                                                                    #
#                                                                             #
###############################################################################

ifeq ($(HOSTTYPE), )
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif

LIBNAME = ./libft_malloc.so
TARGET = ./libft_malloc_$(HOSTTYPE).so
PROJDIR = .
SRCDIR = ./src
OBJDIR = ./build

MAKEFILE_NAME = Makefile-$(lastword $(subst /, ,$(TARGET)))

CC = gcc
CFLAGS = -fPIC
LDFLAGS = -shared
SUBDIR = \
				alloc \
				calloc \
				free \
				malloc \
				realloc \
				reallocf \
				show
SUBFILE = \
				alloc/ft_alloc_arena.c \
				alloc/ft_alloc_chunk.c \
				alloc/ft_alloc_get.c \
				alloc/ft_alloc_init.c \
				alloc/ft_alloc_pthread.c \
				alloc/ft_alloc_search.c \
				alloc/ft_alloc_state_system.c \
				alloc/ft_alloc_state_user.c \
				calloc/ft_calloc.c \
				free/ft_free.c \
				malloc/ft_malloc.c \
				realloc/ft_realloc.c \
				reallocf/ft_reallocf.c \
				show/ft_show.c \
				show/ft_show_hexa.c \
				show/ft_show_tools.c

SRCDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(SRCDIR)/, $(dir)))
OBJDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(OBJDIR)/, $(dir)))
INCLUDES = $(foreach dir, $(SRCDIRS), $(addprefix -I, $(dir)))

VPATH = $(SRCDIRS)
SRCS = $(foreach file, $(SUBFILE), $(addprefix $(SRCDIR)/, $(file)))
OBJS = $(subst $(SRCDIR),$(OBJDIR),$(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

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