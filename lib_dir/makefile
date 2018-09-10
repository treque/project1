########       AVR Project Makefile       ########
#####                                        #####
#####      Makefile produit et ecrit par     #####
#####   	   l'equipe 76 pour				 #####
#####           INF1995 - 2018               #####
#####                                        #####
#####         Inspire de Pat Deegan -        #####
#####  Psychogenic Inc (www.psychogenic.com) #####
##################################################


-include ../makefile_commun.txt

PROJECTNAME=librairie
PRJSRC= $(wildcard *.cpp) constantes.h

# Inclusions additionnelles
INC=
# Libraires a lier
LIBS=

#Nom des cibles par defaut
TRG=$(PROJECTNAME).a

####################################################
	
# Creation des cibles Phony (Phony Target)
.PHONY: all clean 

all: $(TRG)
	

$(TRG): $(OBJDEPS)
	$(AR) $(ARFLAGS) $(TRG) $(OBJDEPS)

clean:
	$(REMOVE) $(OBJDEPS) *.d $(TRG)
