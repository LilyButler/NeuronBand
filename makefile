FLAGS = -Ofast
# CFLAGS = -g -Ofast
# CFLAGS = -g
CFLAGS = -O3 -fPIC
# CFLAGS = -Ofast -fPIC  # for 64-bit systems
# CFLAGS = -O3 -fPIC
# CFLAGS = -g 
# CFLAGS = -g -fPIC
# CFLAGS = -pg -fPIC 
# CFLAGS = -pg 
# CFLAGS = -g -Wall -Wmissing-prototypes
# CFLAGS = -O5 -DCPML -ffast-math -fomit-frame-pointer -finline-functions
# CFLAGS = -O5 -ffast-math -fomit-frame-pointer -finline-functions
# CFLAGS = -O3 -non_shared  # for DEC UNIX
# LDFLAGS = -s
# LDFLAGS = -g
# LDFLAGS = -pg
# LDFLAGS = -s -non_shared  # for DEC UNIX

## NB: to get the expt*.so files to load, must define path.
## Either use ldconfig, or define LD_LIBRARY_PATH:
##
## bash:    LD_LIBRARY_PATH=.; export LD_LIBRARY_PATH
## tcsh:    setenv LD_LIBRARY_PATH .
##
## NB #2: to get the expt*.so files to load under "mosrun", must 
##   link them to /usr/local/lib (or other lib you put in /etc/ld.so.conf)
#    from the current directory where they sit like this:
##    ln -s `pwd`/expt_aii_flash.so /usr/local/lib/lib_expt_aii_flash.so
##  Then run "ldconfig" (config for linker). That way ldconfig finds the
##    name correctly. Test this with "ldconfig -v".


# NC_HOME = ~/nc

ifndef NC_HOME
		NCCDIR=../../src
			LIBPDIR=../../libP
		else
			NCCDIR=$(NC_HOME)/src
				LIBPDIR=$(NC_HOME)/libP
			endif

#
# uncomment this OS definition for MAC OSX:
#
# OSFLAGS = -DMACOSX
ifndef OSFLAGS
		DLSUFFIX=so
			NCLIBCALL = -L $(NCCDIR) -lnc -L $(LIBPDIR) -lP
.cc.so:
		$(CXX) $(CFLAGS) -shared -Wl,-soname,$*.so -o $*.so $*.cc -I $(NCCDIR) -ldl
	else
		DLSUFFIX=so
			LDFLAGS =
				NCLIBCALL = -L$(NCCDIR) -lnc -L$(LIBPDIR) -lP
.cc.so:
		$(CXX) -bundle -o $*.so $*.cc -I$(NCCDIR) $(NCLIBCALL) -bundle_loader retsim
	endif

#NCCDIR = ../../src
#LIBPDIR = ../../libP

SHELL=/bin/bash
# CXX = g++
# CC = gcc

.SUFFIXES: .so .dylib

.cc.o:	
		$(CXX) -c $(CFLAGS) -I $(NCCDIR) $*.cc

LIBNC=libnc.a
NCLIBS = $(NCCDIR)/libnc.a $(LIBPDIR)/libP.a
RETOBJS = retsim.o celfuncs.o celseg.o makcel.o synfuncs.o stimfuncs.o plot_funcs.o \
		  		spike_plot.o sb_makfuncs.o sb_recfuncs.o setexpt.o morphfuncs.o rectask.o namedparams.o

EXPTOBJS= expt_gc_cbp_flash.$(DLSUFFIX) \
		  	  expt_gc_cbp_am_flash.$(DLSUFFIX) \
			  	  expt_gc_cbp_flash_ry.$(DLSUFFIX) \
				  	  expt_gc_cbp_flash2.$(DLSUFFIX) \
					  	  expt_gc_uncage.$(DLSUFFIX) \
						  	  expt_gcb_dbp1_flash.$(DLSUFFIX) \
							  	  expt_cell_vclamp.$(DLSUFFIX) \
								  	  expt_cell_vclamp_t.$(DLSUFFIX) \
									  	  expt_sbac_vclamp.$(DLSUFFIX) \
										  	  expt_sbac_chans.$(DLSUFFIX) \
											  	  expt_sbac_stim.$(DLSUFFIX) \
												  	  expt_sbac_stim_w_dsgc.$(DLSUFFIX) \
													  	  expt_cbp_vclamp.$(DLSUFFIX) \
														  	  expt_cbp_cclamp.$(DLSUFFIX) \
															  	  expt_cbp_feedback.$(DLSUFFIX) \
																  	  expt_cbp_flash.$(DLSUFFIX) \
																	  	  expt_cbp_chirp.$(DLSUFFIX) \
																		  	  expt_gc_bphz_flash.$(DLSUFFIX) \
																			  	  expt_gc_bphz_flash1.$(DLSUFFIX) \
																				  	  expt_gc_cbp_aii_flash.$(DLSUFFIX) \
																					  	  expt_rbp_aii_a17.$(DLSUFFIX) \
																						  	  expt_cone_hz.$(DLSUFFIX) \
																							  	  expt_cone_hz_cvc.$(DLSUFFIX) \
																								  	  expt_cone_hz_hvc.$(DLSUFFIX) \
																									  	  expt_dsgc_cbp_bar.$(DLSUFFIX) \
																										  	  expt_dsgc_cbp_stim.$(DLSUFFIX) \
																											  	  expt_dsgc_cbp_twospot.$(DLSUFFIX) \
																												  	  expt_dsgc_chans.$(DLSUFFIX) \
																													  	  expt_dsgc_calib.$(DLSUFFIX) \
																														  	  expt_dsgc_sbac_bar.$(DLSUFFIX) \
																															  	  expt_dsgc_pair.$(DLSUFFIX) \
																																  	  expt_wfamac.$(DLSUFFIX) \
																																	  	  expt_wfamac_vclamp.$(DLSUFFIX) \
																																		  	  expt_aii_flash.$(DLSUFFIX) \
																																			  	  expt_aii_dbp.$(DLSUFFIX) \
																																				  	  expt_gcoff_hbp_flash.$(DLSUFFIX) \
																																					  	  expt_gcoff_hbp_flicker.$(DLSUFFIX) \
																																						  	  expt_crossover_centre.$(DLSUFFIX) \
																																							  	  expt_morph_props.$(DLSUFFIX) \
																																								  	  expt_cell_Rin.$(DLSUFFIX) \
																																									  	  expt_dsgc_G.$(DLSUFFIX) \
																																										  	  expt_surf_area.$(DLSUFFIX) \
																																											  	  expt_test.$(DLSUFFIX)

all:	retsim $(EXPTOBJS)

printvars:
		@echo "NeuronC Home: $(NC_HOME)"
			@echo "      NCCDIR: $(NCCDIR)"
				@echo "     LIBPDIR: $(LIBPDIR)"

retsim: $(RETOBJS) $(NCLIBS)
		$(CXX) $(LDFLAGS) -rdynamic -o retsim $(RETOBJS) $(NCLIBCALL) -lm -ldl

dsgc_movie: onplot_dsgc_movie.cc onplot_movie.cc

expt_dsgc_cbp_bar.o expt_dsgc_calib.o: dsgc_movie

phbuffer: phbuffer.cc
		$(CXX) phbuffer.cc -Ofast -o phbuffer -I$(NCCDIR) $(NCLIBCALL) -lm

maknval: maknval.o
		$(CXX) $(LDFLAGS) maknval.o -o maknval $(NCLIBCALL) -lm 

modelfit: modelfit.o $(NCLIBS)                                               # link with libnc.a
		$(CXX) $(CFLAGS) $(LDFLAGS) modelfit.o -o modelfit -I$(NCCDIR) $(NCLIBCALL) -L. -lm  

plotsplit: plotsplit.o $(NCLIBS)                                               # link with libnc.a
		$(CXX) $(CFLAGS) $(LDFLAGS) plotsplit.o -o plotsplit -I$(NCCDIR) $(NCLIBCALL) -L. -lm  

retsim.o celfuncs.o celseg.o makcel.o morphfuncs.o onplot_dsgc_movie.o \
	synfuncs.o stimfuncs.o plot_funcs.o spike_plot.o \
	sb_makfuncs.o sb_recfuncs.o setexpt.o $(EXPTOBJS): retsim.h

retsim.o makcel.o: nval.h

retsim.o: retsim_var.cc

celfuncs.o celseg.o makcel.o synfuncs.o stimfuncs.o plot_funcs.o spike_plot.o \
	sb_makfuncs.o sb_recfuncs.o setexpt.o $(EXPTOBJS): retsim_var.h 

retsim.o celfuncs.o celseg.o makcel.o synfuncs.o stimfuncs.o plot_funcs.o spike_plot.o \
	sb_makfuncs.o sb_recfuncs.o setexpt.o $(EXPTOBJS): $(NCCDIR)/ncfuncs.h

celfuncs.o celseg.o makcel.o retsim.o setexpt.o synfuncs.o $(EXPTOBJS): $(NCCDIR)/ncio.h

$(EXPTOBJS): retcolors.h

retsim.o: setexpt.h

retsim.o: retsim_var.cc nval_var.cc nval_var_set.cc

clean:
		rm -f $(RETOBJS) $(EXPTOBJS) retsim libnc.a core


