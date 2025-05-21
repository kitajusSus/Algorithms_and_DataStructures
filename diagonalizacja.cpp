#include <chrono>
#include <cmath> // For std::pow, std::abs
#include <iomanip>
#include <iostream>
#include <random> // For random matrix generation
#include <vector>

// Eigen includes
#include <Eigen/Dense>
#include <Eigen/Eigenvalues> // For EigenSolver

// --- Funkcje pomocnicze ---

// Generuje losową macierz kwadratową NxN
Eigen::MatrixXd generate_random_matrix(int size) {
  // Użyj bardziej nowoczesnego generatora losowego C++
  std::random_device rd;
  std::mt19937 gen(rd());
  // Zakres wartości, np. od -5.0 do 5.0
  std::uniform_real_distribution<> distrib(-5.0, 5.0);

  Eigen::MatrixXd matrix(size, size);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      matrix(i, j) = distrib(gen);
    }
  }
  return matrix;
}

// Metoda 1: Bezpośrednie potęgowanie macierzy (iteracyjne)
Eigen::MatrixXd matrix_power_direct(const Eigen::MatrixXd &A, int p) {
  if (p < 0) {
    throw std::invalid_argument(
        "Power must be non-negative for direct method here.");
  }
  if (p == 0) {
    return Eigen::MatrixXd::Identity(A.rows(), A.cols());
  }
  Eigen::MatrixXd result = A;
  for (int i = 1; i < p; ++i) {
    result = result * A; // Główna operacja mnożenia
  }
  return result;
}

// Metoda 2: Potęgowanie macierzy przez diagonalizację
// A^p = P * D^p * P^-1
Eigen::MatrixXd matrix_power_diagonalization(const Eigen::MatrixXd &A, int p) {
  if (A.rows() != A.cols()) {
    throw std::invalid_argument("Matrix must be square for diagonalization.");
  }
  if (p < 0) {
    // Można by zaimplementować A^-1 i potem (A^-1)^(-p)
    // ale dla uproszczenia, zakładamy p >= 0
    throw std::invalid_argument(
        "Power must be non-negative for this diagonalization example.");
  }
  if (p == 0) {
    return Eigen::MatrixXd::Identity(A.rows(), A.cols());
  }
  if (p == 1) {
    return A;
  }

  Eigen::EigenSolver<Eigen::MatrixXd> es(A);
  if (es.info() != Eigen::Success) {
    // Problem z dekompozycją (np. macierz osobliwa lub źle uwarunkowana)
    // W praktyce rzadko dla losowych macierzy, ale warto wiedzieć
    std::cerr << "Warning: Eigenvalue decomposition failed for a matrix."
              << std::endl;
    // Zwracamy pustą macierz lub rzucamy wyjątek, aby zasygnalizować błąd
    // Dla celów benchmarku możemy spróbować kontynuować lub pominąć
    // Tutaj rzucimy wyjątek, żeby było jasne, że coś poszło nie tak
    throw std::runtime_error("Eigenvalue decomposition failed.");
  }

  Eigen::MatrixXcd P =
      es.eigenvectors(); // Macierz wektorów własnych (może być zespolona)
  Eigen::VectorXcd D_values =
      es.eigenvalues(); // Wektor wartości własnych (mogą być zespolone)

  // Oblicz D^p
  Eigen::VectorXcd D_pow_p_values = D_values;
  for (int i = 0; i < D_values.size(); ++i) {
    // std::pow dla liczb zespolonych
    D_pow_p_values(i) = std::pow(D_values(i), p);
  }
  Eigen::MatrixXcd D_pow_p = D_pow_p_values.asDiagonal();

  // Oblicz P^-1
  // Dla stabilności numerycznej, EigenSolver często zwraca P takie, że P^-1 =
  // P. djoint() / det(P) lub jeśli macierz A jest symetryczna, P jest
  // rtogonalna (P^-1 = P.transpose()) Użyjemy generycznego P.inverse()
  Eigen::MatrixXcd P_inv = P.inverse();

  // Oblicz A^p = P * D^p * P^-1
  Eigen::MatrixXcd result_complex = P * D_pow_p * P_inv;

  // Wynik powinien być rzeczywisty, jeśli A jest rzeczywiste. Bierzemy część
  // rzec ywistą. Należy uważać na błędy numeryczne - część urojona powinna być
  // bliska z ru.
  return result_complex.real();
}

int main() {
  std::cout << std::fixed << std::setprecision(6);

  std::vector<int> matrix_sizes = {2,  3, 5, 10,
                                   20, 30}; // Rozmiary macierzy do testowania
  std::vector<int> powers = {2, 5, 10, 15, 20}; // Potęgi do testowania

  // Nagłówki tabeli
  std::cout << std::setw(8) << "Size" << " | " << std::setw(8) << "Power"
            << " | " << std::setw(20) << "Direct (ms)" << " | " << std::setw(25)
            << "Diagonalization (ms)" << " | " << std::setw(15)
            << "Matrices Close?" << std::endl;
  std::cout << std::string(90, '-') << std::endl;

  for (int size : matrix_sizes) {
    // Dla małych macierzy (np. 2x2), diagonalizacja może nie być zawsze
    // numerycznie stabilna, lub jej koszt stały może być większy.
    // Generujemy jedną macierz dla danego rozmiaru, aby porównywać metody na ty
    // h samych danych.
    Eigen::MatrixXd A = generate_random_matrix(size);

    // Małe sprawdzenie: czy macierz jest diagonalizowalna "wystarczająco d
    // brze" Prosty test: A * P_i ~ lambda_i * P_i
    // Eigen::EigenSolver<Eigen::MatrixXd> temp_es(A);
    // if (temp_es.info() != Eigen::Success) {
    //     std::cerr << "Skipping size " << size << " due to decomposition
    //     issues with test matrix." << std::endl; continue;
    // }
    // Eigen::MatrixXcd P_check = temp_es.eigenvectors();
    // Eigen::MatrixXcd D_check = temp_es.eigenvalues().asDiagonal();
    // Eigen::MatrixXcd A_reconstructed_check = P_check * D_check *
    // P_check.inverse(); if ((A.cast<std::complex<double>>() -
    // A_reconstructed_check).norm() > 1e-6 * A.norm()) {
    //      std::cout << "Warning: Matrix size " << size << " might not be
    //      well-suited for diagonalization (high reconstruction error: "
    //                << (A.cast<std::complex<double>>() -
    //                A_reconstructed_check).norm() << ")" << std::endl;
    // }

    for (int p : powers) {
      if (size > 10 && p > 15 &&
          size * size * size * p > 200000000) { // Heurystyka, aby uniknąć zbyt
                                                // d ugich obliczeń dla direct
        std::cout << std::setw(8) << size << " | " << std::setw(8) << p << " | "
                  << std::setw(20) << "SKIPPED (too long)" << " | ";
      } else {
        auto start_direct = std::chrono::high_resolution_clock::now();
        Eigen::MatrixXd R_direct = matrix_power_direct(A, p);
        auto end_direct = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time_direct =
            end_direct - start_direct;
        std::cout << std::setw(8) << size << " | " << std::setw(8) << p << " | "
                  << std::setw(20) << time_direct.count() << " | ";
      }

      Eigen::MatrixXd R_diag;
      bool diag_success = true;
      std::chrono::duration<double, std::milli> time_diag(0);

      try {
        auto start_diag = std::chrono::high_resolution_clock::now();
        R_diag = matrix_power_diagonalization(A, p);
        auto end_diag = std::chrono::high_resolution_clock::now();
        time_diag = end_diag - start_diag;
        std::cout << std::setw(25) << time_diag.count() << " | ";
      } catch (const std::runtime_error &e) {
        std::cout << std::setw(25) << "ERROR (decomp)" << " | ";
        diag_success = false;
      }

      // Sprawdzenie czy wyniki są zbliżone (jeśli oba obliczenia się powiodły)
      // Wypisz tylko R_direct jeśli istnieje
      Eigen::MatrixXd R_direct_check; // Pusta macierz
      bool direct_calculated =
          (size <= 10 || p <= 15 || size * size * size * p <= 200000000);
      if (direct_calculated) {
        R_direct_check = matrix_power_direct(
            A, p); // Oblicz ponownie jeśli było skipnięte dla czasu
      }

      if (diag_success && direct_calculated) {
        // Używamy normy Frobeniusa do porównania macierzy
        // (R_direct - R_diag).norm() powinno być małe
        double diff_norm = (R_direct_check - R_diag).norm();
        double relative_error_norm = (R_direct_check.norm() > 1e-9)
                                         ? diff_norm / R_direct_check.norm()
                                         : diff_norm;

        if (relative_error_norm < 1e-6) { // Tolerancja błędu
          std::cout << std::setw(15) << "Yes (" << std::scientific
                    << std::setprecision(2) << relative_error_norm << std::fixed
                    << std::setprecision(6) << ")" << std::endl;
        } else {
          std::cout << std::setw(15) << "**NO** (" << std::scientific
                    << std::setprecision(2) << relative_error_norm << std::fixed
                    << std::setprecision(6) << ")" << std::endl;
          // Można dodać więcej diagnostyki:
          // std::cout << "A:\n" << A << std::endl;
          // std::cout << "R_direct:\n" << R_direct_check << std::endl;
          // std::cout << "R_diag:\n" << R_diag << std::endl;
        }
      } else if (!direct_calculated && diag_success) {
        std::cout << std::setw(15) << "Diag OK" << std::endl;
      } else {
        std::cout << std::setw(15) << "N/A" << std::endl;
      }
    }
    std::cout << std::string(90, '-') << std::endl;
  }

  return 0;
}
