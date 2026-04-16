# fastsimZDC

Classes to run fast tracking of particles from IP to ZDC location taking into account:
- magnetic fields (quadrupoles and dipole)
- beam properties (beam divergence, crossing angle, fermi momentum for spectator nucleons)
- detector properties (energy resolution, shower leakages, background from elemnts sorrounding ZDCs)
  
The code (fastMCzdc.cxx) can either read the output of an external event generator (currently implemented are HIJING, PYTHIA and FLUKA) or generate test particle of fixed energy (including nuclear fragments).

Settings for the beam optics are specified in the magline.dat file, while settings for the beam properties are done through the fastmc.dat data file.
To write a fastmc.dat one must use fastMCInputWriter.C, editing the values according to their needs and then running it compiled under root.

Once downloaded, the code must be compiled in an environment where ROOT is set, using:
./compilafast

Then the code is ready to run and produces as output a root file (whose name is set in the fastmc.dat file).

Code written by Mauro Gallio, tested and debugged by Chiara Oppedisano.
