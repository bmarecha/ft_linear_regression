TRAINPROG := trainingProg
TRAINDIR := training_Prog


OGPROG := $(TRAINDIR)/$(TRAINPROG)

all : $(TRAINPROG)

$(OGPROG) :
	make -C $(TRAINDIR)

$(TRAINPROG) : $(OGPROG)
	cp $(OGPROG) $(TRAINPROG)

clean :
	make -C $(TRAINDIR) clean
	rm $(TRAINPROG)


re: clean $(TRAINPROG)

.PHONY: all clean re
.SUFFIXES: .cpp .hpp .o .d