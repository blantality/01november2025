#include <iostream>

void destroy(int **mtx, size_t created);
int **create(size_t rows, size_t cols);
void construct(int **mtx, int init, size_t rows, size_t cols);
void input(int **mtx, size_t rows, size_t cols);
void output(int **mtx, size_t rows, size_t cols);

int main() {
  size_t rows = 0, cols = 0;
  std::cin >> rows >> cols;
  if (!std::cin) {
    std::cerr << "Bad input!\n";
    return 2;
  }
  int **matrix = nullptr;
  matrix = create(rows, cols);
  try {
    matrix = create(rows, cols);
  } catch (const std::bad_alloc &e) {
    destroy(matrix, rows);
    std::cerr << e.what() << '\n';
    return 1;
  }
  std::cout << "Created!\n";
  construct(matrix, 0, rows, cols);
  input(matrix, rows, cols);
  if (!std::cin) {
    std::cerr << "Bad input!\n";
    destroy(matrix, rows);
    return 2;
  }
  output(matrix, rows, cols);
  destroy(matrix, rows);
}

void destroy(int **mtx, size_t created) {
  for (size_t i = 0; i < created; ++i) {
    delete[] mtx[i];
  }
  delete[] mtx;
}

int **create(size_t rows, size_t cols) {
  int **mtx = new int *[rows];
  size_t created = 0;
  try {
    for (size_t i = 0; i < rows; ++i) {
      mtx[i] = new int[cols];
      ++created;
    }
  } catch (const std::bad_alloc &e) {
    destroy(mtx, created);
    throw;
  }
  return mtx;
}

void construct(int **mtx, int init, size_t rows, size_t cols) {
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      mtx[i][j] = init;
    }
  }
}

void input(int **mtx, size_t rows, size_t cols) {
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      std::cin >> mtx[i][j];
    }
  }
}

void output(int **mtx, size_t rows, size_t cols) {
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols - 1; ++j) {
      std::cout << mtx[i][j] << ' ';
    }
    std::cout << mtx[i][cols - 1] << '\n';
  }
}
