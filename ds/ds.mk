.PHONY: debug_%
debug_%:
	cd ./$* && make -f $*.mk

.PHONY: release_%
release_%:
	cd ./$* && make -f $*.mk release

.PHONY: run_%
run_%:	
	./$*/$*.out

.PHONY: clean_%
clean_%:	
	cd ./$* && make -f $*.mk clean

.PHONY: vlg_%
vlg_%:
	valgrind --leak-check=yes --track-origins=yes ./$*/$*.out
