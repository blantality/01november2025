#include <iostream>

void destroy(int **mtx, size_t created) {
  for (size_t i = 0; i < created; ++i)
    delete[] mtx[i];
  delete[] mtx;
}

int **convert(const int *t, size_t n, const size_t *lns, size_t rows) {
  int **mtx = new int *[rows];
  size_t created = 0, now = 0;

  try {
    for (size_t i = 0; i < rows; ++i) {
      mtx[i] = new int[lns[i]];
      for (size_t j = 0; j < lns[i]; ++j)
        mtx[i][j] = t[now + j];
      now += lns[i];
      ++created;
    }
  } catch (const std::bad_alloc &) {
    destroy(mtx, created);
    throw;
  }

  return mtx;
}

void output(int **mtx, const size_t *lns, size_t rows) {
  std::cout << "Resulting matrix:\n";
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < lns[i]; ++j)
      std::cout << mtx[i][j] << ' ';
    std::cout << '\n';
  }
}

int main() {
  size_t rows;
  std::cout << "Rows: ";
  if (!(std::cin >> rows)) {
    std::cerr << "Error: invalid input.\n";
    return 1;
  }

  size_t *lns = new size_t[rows];
  std::cout << "Lengths of each row: ";
  for (size_t i = 0; i < rows; ++i) {
    if (!(std::cin >> lns[i])) {
      std::cerr << "Error: invalid input.\n";
      delete[] lns;
      return 1;
    }
  }

  size_t n = 0;
  for (size_t i = 0; i < rows; ++i)
    n += lns[i];

  int *t = new int[n];
  std::cout << "Enter " << n << " elements of array: ";
  for (size_t i = 0; i < n; ++i) {
    if (!(std::cin >> t[i])) {
      std::cerr << "Invalid input.\n";
      delete[] t;
      delete[] lns;
      return 1;
    }
  }

  int **matrix = nullptr;
  try {
    matrix = convert(t, n, lns, rows);
  } catch (const std::bad_alloc &e) {
    std::cerr << "Memory allocation error: " << e.what() << '\n';
    delete[] t;
    delete[] lns;
    return 1;
  }

  output(matrix, lns, rows);

  destroy(matrix, rows);
  delete[] t;
  delete[] lns;
}
