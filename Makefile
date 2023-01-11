CXX = clang++
CXXFLAGS = -Wall -std=c++20 -stdlib=libc++ -g

MAKE_CMD = make
BEAR_CMD = bear

ALL = all
NAME = escape-room
EXT = cpp
OBJECTS = $(NAME).$(EXT)

COMPILATION_DB = compile_commands.json
CACHE = .cache

$(ALL): $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

run: $(NAME)
	./$(NAME)

clean:
	rm -rf $(NAME) $(COMPILATION_DB) $(CACHE)

$(COMPILATION_DB): clean
	$(BEAR_CMD) -- $(MAKE_CMD) $(ALL)

