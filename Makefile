CC := clang
CFLAGS += -O2 -fPIC -D_GNU_SOURCE $(shell pkg-config --cflags freetype2) -Wall -Wextra -Werror
LDFLAGS += $(shell pkg-config --libs freetype2)
LIB := liblolifont_hook.so
OBJS := hook.o filter.o

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(LDFLAGS) -shared $(OBJS) -o $(LIB)

clean:
	rm -f $(OBJS) $(LIB)
