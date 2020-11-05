SUBDIRS = src/referee src/game src/player include

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: $(SUBDIRS)

clean: 
	rm build/* src/*/*.o