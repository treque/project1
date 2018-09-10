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

PROJECTNAME=main
PRJSRC=main.cpp
# Inclusions additionnelles
INC=-I../lib_dir
# Libraires a lier (ex: -lmylib)
LIBS=../lib_dir/librairie.a

TRG=$(PROJECTNAME).out

###################################################

# Creation des cibles Phony (Phony Target)
.PHONY: all install clean 
	

all: $(TRG)
	

$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) \
	-lm $(LIBS)

%.hex: %.out
	$(OBJCOPY) -j .text -j .data \
		-O $(HEXFORMAT) $< $@

install: $(HEXROMTRG)				
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID)   \
	-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)

clean:
	$(REMOVE) $(OBJDEPS) $(HEXTRG) $(TRG) *.d *.map *.hex *.out
