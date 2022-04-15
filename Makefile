MAKEFILE		=	makefile.nix
UNAME			=	$(shell uname)

ifeq ($(UNAME), Darwin)
	MAKEFILE	=	makefile.mak
endif

all:
	make -f $(MAKEFILE)

bonus:
	make bonus -f $(MAKEFILE)

clean:
	make clean -f $(MAKEFILE)

fclean:
	make fclean -f $(MAKEFILE)
