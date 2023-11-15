CXX		?= g++
RM		?= rm
CXX		:= LANG=en LC_MESSAGES=C $(CXX)

BUILDDIR	?= bin
SRCDIR		:= training_Prog/
EXE			:= trainingProg

SRCS		:= $(shell find ./$(SRCDIR) -name "*.cpp" -type f)
OBJS		:= $(patsubst ./%.cpp, $(BUILDDIR)/%.o, $(SRCS))
DEPS		:= $(patsubst ./%.cpp, $(BUILDDIR)/%.d, $(SRCS))

WARNINGS	:=	-Wall -Wextra -pedantic

FLAGS		:= $(WARNINGS) -std=c++17
LDFLAGS		:= 

ifdef DEBUG
	FLAGS	:= $(FLAGS) -g -Og -DDEBUG
else
	FLAGS	:= $(FLAGS) -O3
endif

all: $(EXE)

-include $(DEPS)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: ./%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(FLAGS) -MMD -MP -c $< -o $@


clean:
	$(RM) -rf $(BUILDDIR)
	$(RM) $(EXE)

re: clean $(EXE)

.PHONY: all clean re
.SUFFIXES: .cpp .hpp .o .d

re: clean $(TRAINPROG)

.PHONY: all clean re
.SUFFIXES: .cpp .hpp .o .d