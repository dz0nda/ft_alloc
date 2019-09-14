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
				alloc_lib \
				free \
				malloc \
				realloc \
				show
SUBFILE = \
				alloc_lib/print_addr.c \
				alloc_lib/strlen.c \
				alloc_lib/strrev.c \
				alloc_lib/memcpy.c \
				alloc_lib/itoa.c \
				alloc_lib/putchar.c \
				alloc_lib/putnbr.c \
				alloc_lib/putstr.c \
				alloc_lib/memset.c \
				alloc/alloc_get.c \
				alloc/alloc_info.c \
				alloc/alloc_arena.c \
				alloc/alloc_error.c \
				alloc/alloc_chunk.c \
				alloc/alloc_init.c \
				alloc/alloc_search.c \
				malloc/malloc.c \
				realloc/realloc.c \
				free/free.c \
				show/show.c \
				show/show_alloc_info.c

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