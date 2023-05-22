#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
 
 
template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> l;
    int sx = 0, sy = 0;
public:
    Matrix(int a = 0, int b = 0) {
        sy = a;
        sx = b;
    }
    
    Matrix operator+(Matrix n) {
        Matrix<T> m;
        if (sy != n.sy or sx != n.sx) {
            std::cerr << "this action is not possible because the matrices are of different sizes" << std::endl << std::endl;
            return *this;
        }
        for (int i = 0; i < sy; i++) {
            for (int j = 0; j < sx; j++) {
                m.insert(l[i][j] + n.l[i][j], i, j);
            }
        }return m;
    }
    
    void insert(T n, int i, int j) {
        if (sy < i + 1) {
            l.resize(sy + 1);
            sy++;
        }if (l[i].size() < j + 1) l[i].push_back(n);
        else l[i][j] = n;
        if (sx < j + 1) sx++;
    }
    
    Matrix operator=(Matrix n) {
        for (int i = 0; i < n.sy; i++) {
            for (int j = 0; j < n.sx; j++) {
                this->insert(n.l[i][j], i, j);
            }l[i].resize(n.sx);
        }l.resize(n.sy);
        sx = n.sx;
        sy = n.sy;
        return *this;
    }
    
    Matrix operator-(Matrix n) {
        Matrix<T> m;
        if (sy != n.sy or sx != n.sx) {
            std::cerr << "this action is not possible because the matrices are of different sizes" << std::endl << std::endl;
            return *this;
        }
        for (int i = 0; i < sy; i++) {
            for (int j = 0; j < sx; j++) {
                m.insert(l[i][j] - n.l[i][j], i, j);
            }
        }return m;
    }
    
    bool operator==(Matrix n) {
        if (sy != n.sy or sx != n.sx) return false;
        bool flag = true;
        for (int i = 0; i < sy; i++) {
            for (int j = 0; j < sx; j++) {
                if (l[i][j] != n.l[i][j]) flag = false;
            }
        }return flag;
    }
    
    Matrix operator*(int n) {
        Matrix<T> m;
        for (int i = 0; i < sy; i++) {
            for (int j = 0; j < sx; j++) {
                m.insert(l[i][j] * n, i, j);
            }
        }return m;
    }
    
    friend Matrix operator*(double scalar, Matrix& mat) {
        return mat * scalar;
    }
    
    Matrix operator*(Matrix n) {
        if (sx != n.sy) {
            std::cerr << "These matrices cannot be multiplied" << std::endl << std::endl;
            return *this;
        }
        Matrix<T> m;
        for (int i = 0; i < sy; i++) {
            for (int k = 0; k < n.sx; k++) {
                T res = 0;
                std::vector<T> temp = n.get_collomn(k);
                for (int j = 0; j < sx; j++) {
                    res += l[i][j] * temp[j];
                }m.insert(res, i, k);
            }
        }
        return m;
    }
    
    Matrix operator/(float n) {
        Matrix<T> m;
        for (int i = 0; i < sy; i++) {
            for (int j = 0; j < sx; j++) {
                m.insert(l[i][j] / n, i, j);
            }
        }return m;
    }
  
    std::vector<T> get_line(int i) {
        return l[i];
    }
    
    std::vector<T> get_collomn(int j) {
        std::vector<T> ans;
        for (int i = 0; i < sy; i++) {
            ans.push_back(l[i][j]);
        }return ans;
    }
    
    bool is_E() {
        if (sx != sy) return false;
        for (int i = 0; i < sy; i++) {
            for (int j = 0; j < sx; j++) if (not ((i == j and l[i][j] == 1) or (i != j and l[i][j] == 0))) return false;
        }return true;
    }
    
    bool is_O() {
        for (int i = 0; i < sy; i++) {
            for (int j = 0; j < sx; j++) {
                if (l[i][j]) return false;
            }
        }return true;
    }
    
    float det() {
        if (sy != sx) {
            std::cerr << "The matrix must be square" << std::endl << std::endl;
            return 0;
        }
        if (sy == 1) return (float)l[0][0];
        if (sy == 2) return l[0][0] * l[1][1] - l[0][1] * l[1][0];
        float res = 0;
        for (int i = 0; i < sy; i++) {
            float temp = 1;
            for (int j = 0; j < sy; j++) {
                temp *= (float)l[j][(i + j) % sy];
            }res += temp;
        }for (int i = 0; i < sy; i++) {
            float temp = 1;
            for (int j = 0; j < sy; j++) {
                temp *= (float)l[j][(sy + i - j) % sy];
            }res -= temp;
        }return res;
    }
    
    void make_E(int a) {
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < a; j++) {
                if (i == j) this->insert(1, i, j);
                else this->insert(0, i, j);
            }l[i].resize(a);
        }l.resize(a);
        sy = a; sx = a;
    
    
    }void make_O(int a, int b) {
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                this->insert(0, i, j);
            }l[i].resize(b);
        }l.resize(a);
        sy = a; sx = b;
    }
    
    int get_length() { return sx; }
    
    int get_width() { return sy; }
    
    T get_value(int i, int j) { return l[i][j]; }
    
    void print() {
        for (int i = 0; i < sy; i++) {
            for (int j = 0; j < sx; j++) {
                std::cout << l[i][j] << " ";
            }std::cout << std::endl;
        }std::cout << std::endl;
    }
    
    Matrix get_small(int i, int j) {
        Matrix<T> m;
        bool flag = false;
        for (int k = 0; k < sy; k++) {
            if (k != i) {
                bool flag1 = false;
                for (int g = 0; g < sx; g++) {
                    if (g != j) {
                        int k1, g1;
                        if (flag) k1 = k - 1;
                        else k1 = k;
                        if (flag1) g1 = g - 1;
                        else g1 = g;
                        m.insert(l[k][g], k1, g1);
                    }
                    else flag1 = true;
                }
            }
            else flag = true;
        }return m;
    }
    
    Matrix transpon() {
        Matrix<T> m;
        for (int i = 0; i < sy; i++) {
            for (int j = 0; j < sx; j++) {
                m.insert(l[i][j], j, i);
            }
        }return m;
    }
    
    Matrix findAlgebraicComplement() {
        if (sy != sx) {
            std::cerr << "The matrix must be square" << std::endl << std::endl;
            return *this;
        }
        Matrix<T> m;
        for (int i = 0; i < sy; i++) {
            for (int j = 0; j < sx; j++) {
                m.insert(this->get_small(i, j).det() * pow((-1), i + j), i, j);
            }
        }return m;
    }
    
    Matrix operator!() {
        if (!(this->det())) {
            std::cerr << "The matrix must be square" << std::endl << std::endl;
            return *this;
        }
        if (this->is_E()) return *this;
        if (this->is_O()) return *this;
        Matrix<T> m = (this->findAlgebraicComplement().transpon() / this->det());
        return m;
    }
    
    void empty() {
        sy = 0; sx = 0;
        l.resize(0);
    }
    
    void read(int a, int b) {
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                T temp;
                std::cin >> temp;
                this->insert(temp, i, j);
            }
        }
    }
    
    void readf(std::ifstream& f, int a, int b) {
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                T temp;
                f >> temp;
                this->insert(temp, i, j);
            }
        }
    }
    
    void printf(std::ofstream& f) {
        for (int i = 0; i < sy; i++) {
            for (int j = 0; j < sx; j++) {
                f << l[i][j] << " ";
            }f << "\n";
        }f << "\n";
    }
};
 
 
int main()
{
    Matrix<float> A;
    Matrix<float> B;
    Matrix<float> C;
    for (int i = 0; i < 10; i++) {
        A.insert(i + 1, i / 5, i % 5);
        B.insert(10 - i, i / 5, i % 5);
    }C = A + B;
    B = B.transpon();
    C = A * B;
    A.print();
    B.print();
    C.print();
    if (C == A) std::cout << "101 " << A.get_length() << " " << A.get_width() << std::endl << std::endl;
    A.make_E(3);
    std::cout << A.get_length() << " " << A.get_width() << std::endl << std::endl;
    std::cout << A.det() << std::endl;
    C = A.get_small(1, 1);
    A.print();
    C.print();
    B.print();
    C = A.findAlgebraicComplement();
    C.print();
    (!A).print();
    A.empty();
    A.print();
    for (int i = 1; i < 10; i++) {
        A.insert(i, (i - 1) / 3, (i - 1) % 3);
    }A.insert((float)10, 2, 2);
    A.print();
    std::cout << A.det() << std::endl << std::endl;
    (!A).print();
    A.empty();
    A.read(2, 2);
    A.print();
    A = 10 * A;
    A.print();
    A = A / 10;
    A = A * 10;
    A.print();
}
