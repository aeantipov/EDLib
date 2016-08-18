#include <iostream>
#include <alps/params.hpp>


#include <Hamiltonian.h>
#include <SzSymmetry.h>
#include <SOCRSStorage.h>
#include <HubbardModel.h>
#include <GreensFunction.h>


/**
 * Define parameters used in programm
 * \param p - alps paramters
 */
void define_parameters(alps::params &p) {
  p.define<int>("NSITES", 4, "Number of sites");
  p.define<int>("NSPINS", 2, "Number of spins");
  p.define<int>("arpack.NEV", 2, "Number of eigenvalues to find");
  p.define<int>("arpack.NCV", "Number of convergent values");
  p.define<bool>("arpack.SECTOR", "Read symmetry sectors from file");
  p.define<size_t>("storage.MAX_SIZE", 70000, "Number of eigenvalues to find");
  p.define<size_t>("storage.MAX_DIM", 5000, "Number of eigenvalues to find");
  p.define<std::string>("INPUT_FILE", "input.h5", "File with initial data");
  p.define<int>("lanc.NOMEGA", 32, "Number of fermionic frequencies");
  p.define<int>("lanc.NLANC", 100, "Number of Lanczos iterations");
  p.define<double>("lanc.BETA", 10.0, "Inverse temperature");
  p.define<double>("lanc.BOLTZMANN_CUTOFF", 1e-12, "Cutoff for Boltsman factor");
}


int main(int argc, const char ** argv) {
  alps::params params(argc, argv);
  define_parameters(params);
  if(params.help_requested(std::cout)) {
    exit(0);
  }
  Hamiltonian<double, SzSymmetry, SOCRSStorage<double, SzSymmetry, HubbardModel<double> > , HubbardModel<double> > ham(params);
//  Hamiltonian<double, SzSymmetry, CRSStorage<double> , HubbardModel<double> > ham(params);
  ham.diag();
  GreensFunction<double, Hamiltonian<double, SzSymmetry, SOCRSStorage<double, SzSymmetry, HubbardModel<double> > , HubbardModel<double> > , HubbardModel<double> > greensFunction(params, ham);
  greensFunction.compute();
  return 0;
}
