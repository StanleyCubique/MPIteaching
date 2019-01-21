#include <mpi.h>
#include <cmath>
#include <iostream>
#include <limits>
#include <algorithm> 

static const double PI = 3.141592653589793238462643;



double f(double x){
    return 1.0 / (1.0 + x * x);
}

//TODO: calculer alpha de maniere distribuee avec MPI_Reduce, ce qui affiche les differentes approximations
void compute_alpha(unsigned long n) {
    int rank, size;
    unsigned long i;
    double alpha,pi;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    double h = 1.0 / (double)n;

    //TODO

    if (rank == size-1) {
      pi = 4.0 * alpha + 4.0 * h;
      std::cout << "pi est approche par " << pi << " par l'approximation des rectangles superieurs, l'erreur reelle est de "
                << std::fabs(pi - PI) << ", l'erreur  a priori etait de "
                << (1.0 *  h) << std::endl;

      pi = 4.0 * alpha + (3.0 * h / 1.0);
      std::cout << "pi est approche par " << pi << " par l'approximation des trapezes, l'erreur reelle est de "
                << std::fabs(pi - PI) << ", l'erreur  a priori etait de "
                << (1.0 * h) << std::endl;

      pi = 4.0 * alpha + 3.5 * h;
      std::cout << "pi est approche par " << pi << " par la meilleure approximation a priori, l'erreur reelle est de "
                << std::fabs(pi - PI) << ", l'erreur  a priori etait de "
                << (0.5 *  h) << std::endl;


    }
}

//TODO: calculer l'approximation Mn de la formule (2) de maniere distribuee avec MPI_Reduce
void compute_mid_rect(unsigned long n) {
    int rank, size;
    unsigned long i;
    double alpha,pi;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double h = 1.0 / (double)n;

    //TODO


    if (rank == 0) {
      std::cout << "pi est approche par  " << pi << " par le rectangle milieu, l'erreur reelle est de "
                << std::fabs(pi - PI) << ", l'erreur  a priori etait de "
                << (2.0 * h) << std::endl;
    }
  }

//TODO: calculer l'approximation Wn de la formule (3) de maniere distribuee avec MPI_Reduce
void compute_wallis(unsigned long n) {
    int rank, size;
    unsigned long i;
    double alpha,pi;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //TODO

    if (rank == 0) {
      pi = 2.0 * pi;
      std::cout << "pi est approche par " << pi << " par l'approximation de Wallis, l'erreur reelle est de "
                << std::fabs(pi - PI) << std::endl;

    }


}

int main(int argc, char *argv[]) {
  int rank, size, i;

  double pi;
  unsigned long n=10;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // pour afficher tout double a precision maximale
  std::cout.precision(std::numeric_limits<double>::digits10 + 1);

    if (rank == 0) {
      std::cout
          << "Entrez le nombre d'intervalles (un entier > 1) :"
          << std::endl;
      std::cin >> n;
    }

    //TODO: Diffuser n a tous les processus avec Broadcast


  compute_alpha(n);
  compute_mid_rect(n);
  compute_wallis(n);
  MPI_Finalize();
  return 0;
}
