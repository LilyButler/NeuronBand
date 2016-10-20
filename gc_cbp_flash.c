/* Experiment gc_cbp_flash */
/*  for nc script retsim.cc */

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include "ncfuncs.h"
#include "retsim.h"
#include "retsim_var.h"
#include <map>
#include <string>

double temp_freq;
double ntrials;
double dstim;
double sdia;
double stimtime;
double minten;
double scontrast;
double setploti;

int rec_ct;
int rec_cn;

/*------------------------------------------------------*/

void defparams(void) 
{
  setptr("temp_freq", &temp_freq);
  setptr("ntrials",   &ntrials);
  setptr("dstim",     &dstim);
  setptr("sdia",      &sdia);
  setptr("stimtime",  &stimtime);
  setptr("minten",    &minten);
  setptr("scontrast", &scontrast);
  setptr("setploti",  &setploti);
  nvalfile = "nval_gc_cbp_flash.n";
}

/*------------------------------------------------------*/

void setparams(void)
{
  make_rods = 0;
  make_cones= 1;        /* make cones, dbp, gc */
  n_cones = 50;
  make_ha   = 1;
  n_hb = 3;
  make_hb   = 0;
  make_hbat = 0;
  make_dbp1 = 1;
  n_dbp1 = 1;
  make_dbp2 = 1;
  n_dbp2 = 1;
  make_rbp  = 0;
  make_aii = 1;
  n_aii = 3;
  make_gca  = 1;
  n_gca = 3;
  make_gcb  = 0;
  make_dsgc = 0;
  //gyarrsiz = 500.0;
  //gxarrsiz = 400.0;

  if(notinit(rec_ct)) rec_ct = gca;
  //if (notinit(arrsiz)) arrsiz = 300;
  if (notinit(bg_inten)) bg_inten = 2.0e4;      /* background light intensity */
  //if (arrsiz==100) {
  //  setsv (dbp1,SCOND,1, 25e-10);
  //}

/*#define DBP1ARR 30
    conexarr  = (double *)emalloc(DBP1ARR*sizeof(double));
    coneyarr  = (double *)emalloc(DBP1ARR*sizeof(double));
    conetharr = (double *)emalloc(DBP1ARR*sizeof(double));
    conenarr  = (int *) emalloc(DBP1ARR*sizeof(int));
    
    conexarr[0] =  5;    coneyarr[0] = 6;    conetharr[0] = 0;    conenarr[0] = 1;
    conexarr[1] = -5;    coneyarr[1] = 6;    conetharr[1] = 0;    conenarr[1] = 2;
    conexarr[2] = 5;    coneyarr[2] = -6;    conetharr[2] = 0;    conenarr[2] = 3;
    conexarr[3] = -5;    coneyarr[3] = -6;    conetharr[3] = 0;    conenarr[3] = 4;
    conexarr[4] = 3;    coneyarr[4] = -3;    conetharr[4] = 0;    conenarr[4] = 5;
    conexarr[5] =  7;    coneyarr[5] =8;    conetharr[5] = 0;    conenarr[5] = 6;
    conexarr[6] = -7;    coneyarr[6] = 8;    conetharr[6] = 0;    conenarr[6] = 7;
    conexarr[7] = 7;    coneyarr[7] = -8;    conetharr[7] = 0;    conenarr[7] = 8;
    conexarr[8] = -7;    coneyarr[8] = -8;    conetharr[8] = 0;    conenarr[8] = 9;
    conexarr[9] = 0;    coneyarr[9] = -0;    conetharr[9] = 0;    conenarr[9] = 10;
    n_cones = 10;
*/
}

/*------------------------------------------------------*/

void addcells(void)

// Make a ganglion cell compartment postsynaptic to the bipolar cell.
// To use, set make_gca = 0 above

{      
     node *npt;
     int dbpn, gcn, gcnod;
     node *dbpnod;
     sphere *s;
     cable *c;
     int num_pigm = 1;
  
  if (make_cones)
  {
      for (elem * pElement = elempnt; pElement = foreach(pElement, xcone); pElement = pElement->next)
      //for (npt=nodepnt; npt=foreach (elem *epnt, int etype); npt=npt->next)
      {
          int type = pElement->ctype;                                             
          if (type == CONE)
          {
            photorec * pPhotoReceptor = (photorec*)pElement;
            cerr << "Number cone " << pPhotoReceptor -> elnum << " Pigment " << num_pigm << "\n";
            pPhotoReceptor -> pigm = num_pigm++;
            if (num_pigm > 3) 
            {
                num_pigm = 1;
            }
          }
      }
  }


}

/*-------------000000000000000-----------------------------------------*/

void runexpt(void)

{
    int ct, cn, n, plnum;
    int colr;
    int midcone, midcbp, midcbp2;
    int synin1, synin2;
    double t, fmax,fmin;
    double rmin, rmax, plsize;
    double dtrial,exptdur;
    double Vmin, Vmax;
    fprintf(stderr, "runexpt-------------------------------------------------------------------------------------");
  if (notinit(temp_freq)) temp_freq = 2;
  if (notinit(ntrials)) ntrials = 1;
  if (temp_freq == 0) {
    fprintf (stderr,"## retsim1: temp_freq = 0, STOPPING\n");
    temp_freq = 1;
  };
  dtrial = 1 / temp_freq;
  exptdur = dtrial * ntrials;
  endexp  = exptdur;
  ploti = 1e-4;

  if (notinit(dstim))         dstim = 0.05;      /* stimulus duration */
  if (notinit(sdia))           sdia = 300;      /* spot diameter */
  if (notinit(stimtime))   stimtime = 0.1;      /* stimulus time */
  if (notinit(minten))       minten = bg_inten; /* background intensity (for make cone)*/
  if (notinit(scontrast)) scontrast = 20;       /* intensity increment */
  if (!notinit(setploti))     ploti = setploti; /* plot time increment */

  midcone = findmid(xcone,0,0);
  midcbp  = findmid(dbp1,0,0);
  midcbp2 = findmid(dbp1,10,10);
  //midcbp2 = find_gtconn(dbp1, 8);
  synin1 = ncel_in(dbp1,midcbp,xcone);
  synin2 = ncel_in(dbp1,midcbp2,xcone);
  if (ninfo >=1) fprintf (stderr,"# mid cone # %d\n", midcone);
  if (ninfo >=1) fprintf (stderr,"# mid cbp  # %d ncones %d\n",  midcbp,synin1);
  if (ninfo >=1) fprintf (stderr,"# mid cbp2 # %d ncones %d\n",  midcbp2,synin2);
  
  
  std::map<int, std::string> elem_type;

  elem_type[ELEMENT] = "ELEMENT";
  elem_type[CABLE] = "CABLE";
  elem_type[SPHERE] = "SPHERE";
  elem_type[SYNAPSE] = "SYNAPSE";
  elem_type[CHAN] = "CHANNEL";
  elem_type[ROD] = "ROD";
  elem_type[CONE] = "CONE";
  elem_type[TRANSDUCER] = "TRANSDUCER";
  elem_type[GJ] = "GAP JUNC";
  elem_type[PNX] = "PNX";
  elem_type[LOAD] = "LOAD";
  elem_type[RESISTOR] = "RESISTOR";
  elem_type[CAP] = "CAP";
  elem_type[GNDCAP] = "GNDCAP";
  elem_type[BATT] = "BATT";
  elem_type[GNDBATT] = "GNDBATT";
  elem_type[BUF] = "BUF";
  elem_type[CACOMP] = "CACOMP";

 for(elem * pElement = elempnt; pElement; pElement = pElement->next)
    {
        int type = pElement->ctype;
        cerr << "Type  " << elem_type[type] << "  Number " << pElement->elnum << " node " << pElement->node1b << "\n"; 
        if (type == SYNAPSE)
        {
            synapse *syn = (synapse *) pElement;
            //std::cerr << "RESP " << syn->resp << " \n ";
            syn->tfall2 = 0.5;
        }
    }
/*
  plot (G, 1, midcone, 0, 0.5); plot_param("rhodopsin", red, 2, 0.1);
  plot (G, 2, midcone, 0, 0.5); plot_param("meta rhod_1", blue, 3, 0.1);
  plot (G, 3, midcone, 0, 0.5); plot_param("meta rhod_2", green, 4, 0.1);
  plot (G, 4, midcone, 0, 0.5); plot_param("G_protein", magenta, 5, 0.1);
  plot (G, 5, midcone, 0, 0.1); plot_param("PDE", brown, 6, 0.1);
  plot (G, 6, midcone, 0, 0.5); plot_param("G cyclase", yellow,7, 0.1);
  plot (G, 7, midcone, 0.5, 1); plot_param("cGMP", gray, 8, 0.1);
  plot (G, 8, midcone, 0, 0.5); plot_param("Ca feedback", cyan, 9, 0.1);
  plot (G, 9, midcone, 0, 0.5); plot_param("Cax", white, 10, 0.1);
  plot (G, 10, midcone, 0, 8); plot_param("Rho kinase", green, 1, 0.1);
  plot_l_nod (xcone, 1, 0, 0, 2.0e4, yellow, "Lumos", 11, 0.09);
*/

  //plot (FA0, 10, 0, 0.008); plot_param("FA0_10", blue, 1, 0.25);
  //plot (FA4, 10, 0, 0.008); plot_param("FA4_10", green, 2, 0.2);
  
  //plot (FA9, 10, 0, 4); plot_param("FA9_10", magenta, 2, 0.2);
  //plot (FB0, 10, 0, 12); plot_param("FB0_10", red, 3, 0.2);
  //plot (FB0, 206, 0, 10); plot_param("FB0_10", green, 3, 0.2);
  //plot (FB0, 266, 0, 10); plot_param("FB0_10", blue, 3, 0.2);
  //plot (FB4, 10, 0, 0.7); plot_param("FB4_10", gray, 4, 0.25);
  //plot (FC4, 10, 0, 0.0002); plot_param("FC4_10", cyan, 5, 0.2);

  plot (I, 12, -1e-12, 0); plot_param("I", red, 6, 0.5);

  //plot (FC9, 3, 10, 0, 1.e-4); plot_param("G", white, 7, 0.25);
  //plot (G, 2, 10, 0, 0.2); plot_param("G", white, 8, 0.2);

 // cerr << "midcone " << midcone << "\n";
  //plot_v_nod(xcone, 25, soma, Vmin=-0.0385, Vmax =-.034, colr=red, "voltage", 1, 1); /* plot Vcones*/
  //plot_v_nod(0, 11, 0, Vmin=-0.0385, Vmax =-.034, colr=green, "voltage", 1, 1); /* plot Vcones*/
  //plot_v_nod(0, 6, 0, Vmin=-0.0385, Vmax =-.034, colr=blue, "voltage", 1, 1); /* plot Vcones*/
  
  //plot_v_nod(0, 1, 1, Vmin=-0.045, Vmax =-0.034, colr=cyan, "voltage", 1, 0.5); /* plot Vcones*/
  //plot_synrate_out(ct=xcone,cn=midcone,rmin=0,rmax=400,colr=magenta);	              /* plot rate out */
  //plot_v_nod(ct=dbp1,cn=midcbp,n=soma, Vmin=-.051,Vmax =-0.043,colr=red,"", 5, 0.5);     /* plot Vcbp */
  //plot_v_nod(ct=dbp1,cn=midcbp2,n=soma,Vmin=-.045,Vmax =-.035,colr=green,"", -1, -1);  /* plot Vcbp */
  //plot_synrate_out(ct=dbp1,cn=midcbp,rmin=0,rmax=200,colr=magenta);	              /* plot rate out */
  plot_v_nod(ct=gca, cn=1,n=soma,Vmin=-.090,Vmax =-.05,colr=blue,"", -1, 0.5);	      /* plot Vgc */
  /*if (make_gca && getn(gca,BIOPHYS))
    {
            plot(CA, 1, ndn(gca,1,soma), fmax=0.5e-6, fmin=0); 
			plot_param("Cai", colr=yellow,plnum=0,plsize=0.3);
    }*/
  stim_backgr(minten);
  //vclamp(ndn(0,1,1), -0.05, stimtime, dstim);
  for (t=0; t<exptdur; t+= dtrial){
     double start, dur;

    stim_spot(sdia, 0, 0,  minten*scontrast, start=t+stimtime,dur=dstim, 430.0, 0);
    step(dtrial);
    fprintf(stderr, "t = %f,  %f \n", t, t/exptdur*100.0);
  }
}
