SUBDIRS = src/referee src/game src/player

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: $(SUBDIRS)

clean: 
	rm build/* src/*/*.o