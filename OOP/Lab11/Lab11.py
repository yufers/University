import numpy as np    
import io

class MatrixProcessor:
    def __init__(self):
        self.matrices = []
        self.completed_matrices = []
        self.equivalent_matrices = []

    def __str__(self):
        return self.build_result()

    def read_matrices(self):
        temp_matrices = []
        current = []
        
        while True:
            line = input().strip()
            
            if line == "end":
                if current:
                    temp_matrices.append(current)
                break
                
            if not line:
                if current:
                    temp_matrices.append(current)
                    current = []
                continue
                
            current.append(list(map(int, line.split())))
        
        self.matrices = temp_matrices

    def complete_matrices(self):
        if not self.matrices:
            return []
        
        tmp_completed_matrices = []

        for matrix in self.matrices:
            max_length = max(len(row) for row in matrix)
            
            completed = []
            for row in matrix:
                completed_row = row + [0] * (max_length - len(row))
                completed.append(completed_row)
            
            tmp_completed_matrices.append(completed)
        
        self.completed_matrices = tmp_completed_matrices

    def get_simple_equivalents(self):
        tmp_all_equivalents = []

        for matrix in self.completed_matrices:
            matrix_np = np.array(matrix)
            equivalents = []

            if matrix_np.shape[0] == matrix_np.shape[1]:
                equivalents.append(matrix_np.T)
            
            equivalents.append(matrix_np[::-1])
            equivalents.append(matrix_np[:, ::-1])
            equivalents.append(2 * matrix_np)
            equivalents.append(-1 * matrix_np)

            tmp_all_equivalents.append(equivalents)
        
        self.equivalent_matrices = tmp_all_equivalents

    def print_not_full_matrix(self, matrix):
        row_size = len(matrix)
        col_size = len(matrix[0])

        tm = matrix.copy()
        if tm[0][0] == 0 and tm[0][1] == 0 and tm[1][0] == 0:
            print()
            for i in range(0, row_size):
                for j in range(0, col_size - i - 1):
                    print("   ", end="")
                for j in range(col_size - i - 1, col_size):
                    print(tm[i][j], " ", end="")
                print()
            return
        
        if tm[row_size-1][0] == 0 and tm[row_size-2][0] == 0 and tm[row_size-1][1] == 0:
            print()
            for i in range(0, row_size):
                for j in range(0, i):
                    print("   ", end="")
                for j in range(i, col_size):
                    print(tm[i][j], " ", end="")
                print()
            return

        if tm[row_size-1][col_size-1] == 0 and tm[row_size-1][col_size-2] == 0 and tm[row_size-2][col_size-1] == 0:
            print()
            for i in range(0, row_size):
                for j in range(0, col_size - i):
                    print(tm[i][j], " ", end="")
                print()
            return
        
        if tm[0][col_size-1] == 0 and tm[0][col_size-2] == 0 and tm[1][col_size-1] == 0:
            print()
            for i in range(0, row_size):
                for j in range(0, i + 1):
                    print(tm[i][j], " ", end="")
                print()
            return

        print()
        for i in range(0, row_size):
            for j in range(0, col_size):
               print(tm[i][j], " ", end="")
            print()

    def print_results(self):
        idx = 0
        for matrix in self.matrices:
            print("изначальная матрица: ")
            for row in matrix:
                print(row)
            print()

            equivalent = self.equivalent_matrices[idx]
            counter = 0

            print("Эквивалентные матрици: ")
            for row in equivalent:
                if counter == 4:
                    break

                self.print_not_full_matrix(row)
                counter += 1

            idx += 1
    
    def build_result(self):
        with io.StringIO() as output:
            self.print_results()
            return output.getvalue()

    def process(self):
        self.read_matrices()
        self.complete_matrices()
        self.get_simple_equivalents()

def main():
    processor = MatrixProcessor()
    processor.process()
    print(processor)

if __name__ == "__main__":
    main()