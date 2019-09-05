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
SUBDIR = alloc \
malloc \

SUBFILE = ./src/alloc/alloc.c \
./src/malloc/malloc.c

SRCDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(SRCDIR)/, $(dir)))
OBJDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(OBJDIR)/, $(dir)))
INCLUDES = $(foreach dir, $(SRCDIRS), $(addprefix -I, $(dir)))

VPATH = $(SRCDIRS)
SRCS = $(SUBFILE)
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

define buildSource
$(1)/%.o: %.c
	@echo $(MAKEFILE_NAME): Building $$@
	$(HIDE)$(CC) $(CFLAGS) -c $$(INCLUDES) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<) -MMD
endef

.PHONY: all directories clean fclean re

all: directories $(TARGET)

$(TARGET): $(OBJS)
	$(HIDE)echo $(MAKEFILE_NAME): Linking $@
	$(HIDE)$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)
	$(HIDE)ln -s $(TARGET) $(LIBNAME)

-include $(DEPS)

$(foreach targetdir, $(OBJDIRS), $(eval $(call buildSource, $(targetdir))))

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