SUB_DIR = $(shell find . -mindepth 1 -maxdepth 1 -type d)

all: $(SUB_DIR)
clean: $(SUB_DIR)

$(SUB_DIR):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: all clean $(SUB_DIR)

