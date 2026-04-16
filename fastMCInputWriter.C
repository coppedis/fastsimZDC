#include <TPDGCode.h>
#include "FastMCWriter.h"

int fastMCInputWriter()
{
    FastMCConfig cfg =  FastMCConfig();

    // =======================
    // Generator (HIJING PbPb)
    // =======================
    cfg.idgen = 3; // 1: HIJING AA, 2: HIJING pp, 3: test particle, 5: RELDIS, 6: FLUKA
    if(cfg.idgen == 1) {
        cfg.p0 = 208;
        cfg.p1 = 82;
        cfg.p2 = 208;
        cfg.p3 = 82;
        cfg.p4 = 2760;
        cfg.input_file = "hijing_input.dat";
    } else if(cfg.idgen == 3) {
        cfg.p0 = kNeutron;
        if(cfg.p0 == 2112){
          cfg.p1 = 1; // A
          cfg.p2 = 0; // Z
        }
        else if(cfg.p0 == 2212){
          cfg.p1 = 1; // A
          cfg.p2 = 1; // Z
        }
        cfg.p3 = 2680; // energy in GeV/c
        cfg.p4 = 1; // multiplicity (number of particles per event)
        if(cfg.p3 == 0) cfg.p5 = 100.; // if p3=0, then p5 is the sigma of the E distribution in GeV/c
    }

    cfg.output_file = "output.root";

    cfg.nevmax = 100000;
    cfg.nevfreq = 10000;
    cfg.nevfrst = 0;

    // =======================
    // Geometry DON'T CHANGE!!!
    // =======================
    cfg.geometry = {
        {0.0, 0.0, 112.5, 0.0352, 0.0352, 1.0},
        {0.0, 0.0, -112.5, 0.0352, 0.0352, 1.0},
        {0.2435, 0.0, 112.5, 0.112, 0.0352, 1.0},
        {0.2435, 0.0, -112.5, 0.112, 0.0352, 1.0},
        {-0.096, 0.0, 7.60, 0.035, 0.035, 0.21},
        {0.096, 0.0, 7.60, 0.035, 0.035, 0.21}
    };

    // =======================
    // Flags
    // =======================
    cfg.div = 1; // 0: no beam divergence, 1: beam divergence
    cfg.ip = 1; // smearing of IP
    cfg.cross = 0; // crossing angle 
    cfg.fermi = 1; // apply Fermi momentum 
    cfg.frag = 0; // fragm. models: 1: SMM 2: Chiara's data driven model 3: gallio's parametrization (only in AA)
    cfg.res = 1; // 1: provide parameters for resolution, 2: use built-in parametrized resolution
    cfg.bckgrnd = 1; // 1: background in ZN, ZP from beam pipe, 2: background in ZN, ZP from material around detectors, 3: naked fibres 
    cfg.nf = 1; // 0: no signal from naked fibres, 1: signa lin naked fibres is considered
    cfg.newreadout = 0; // 1: RUN 3 readout format (not needed)

    // =======================
    // Beam parameters
    // =======================
    if(cfg.div == 1) cfg.theta_div = 0.000024; // divergence angle (in mm)
    if(cfg.ip == 1) cfg.ipbeam = {0.000, 0.000065, 0.000, 0.000065, 0.0, 0.1, 0}; // vertex smearing: x, dx, y, dy, z, dz, 0: flat 1: gaus
    if(cfg.cross == 1) cfg.cross_angle = 0.0; // crossing angle (in mm)
    if(cfg.res == 2){
        cfg.ZN[0] = 2.566;
        cfg.ZN[1] = 0.103;
        cfg.ZN[2] = 0.90;
        cfg.ZN[3] = 0.0;
        //
        cfg.ZP[0] = 2.37;
        cfg.ZP[1] = 0.125;
        cfg.ZP[2] = 1.07;
        cfg.ZP[3] = 0.05;
    }

    // Readout
    if(cfg.newreadout > 0) {
      cfg.sigma_tof = 0.25;
      cfg.baseline_mean = 0.0;
      cfg.baseline_spread = 0.01;
    }
    
    // =======================
    // Write file
    // =======================
    writeFastMC(cfg);

    return 0;
}