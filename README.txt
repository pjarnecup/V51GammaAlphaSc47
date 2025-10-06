# File: README.md
# V51(γ,α)47Sc Geant4 Application


## Build
```bash
mkdir build && cd build
cmake ..
make -j
```


## Run
Interactive (with visualization):
```bash
./v51_gamma_alpha
```
Batch:
```bash
./v51_gamma_alpha ../macros/run.mac
```


### Adjustable parameters
- `/beam/energy <MeV>`: mono-energetic gamma energy.


### Outputs
At end of run, prints total 47Sc produced, events, and yield per gamma.


### Notes
- Photonuclear modeling of specific (γ,α) channels depends on Geant4 version and data/models; this app **counts** 47Sc residuals created by the photo-nuclear process inside the target.
- Target: 1 cm × 1 cm × 1 mm V-51 slab centered at origin; beam along +Z from z = −2 mm.