SUBDIRS = src/referee src/game src/player

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: $(SUBDIRS)

clean: 
	rm build/* src/*/*.o src/game/Game-* src/referee/REFEREE_PIPE src/player/PLAYER_PIPE-*