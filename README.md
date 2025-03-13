# fastsimZDC
Classes to run fast tracking of particles from IP to ZDC location.
It can either read the output from an event generator (currently implemented are HIJING, PYTHIA and FLUKA) or generate test particle of chosen energy (inclusing nuclear fragments).

The code includes:
- magnetic fields (quadrupoles and dipole)
- beam properties (beam divergence, crossing angle, fermi momentum for spectator nucleons)
- detector properties (energy resolution and shower leakages)

Settings for the beam optics are done through the magline.dat card, while settings for the beam properties are done through the fastmc.dat card.

Code written by Mauro Gallio, tested and debugged by Mauro Gallio and Chiara Oppedisano
