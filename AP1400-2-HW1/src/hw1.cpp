#include "hw1.h"
#include<iostream>
namespace algebra
{
    Matrix zeros(size_t n, size_t m)
    {
        Matrix a(n,std::vector<double>(m,0));
        return a;
    }

    Matrix ones(size_t n, size_t m)
    {
        Matrix a(n,std::vector<double>(m,1));
        return a;
    }

    Matrix random(size_t n, size_t m, double min, double max)
    {
        if (min >= max)
        {
            throw std::logic_error("interval left >= interval right");
        }
        Matrix a(n,std::vector<double>(m,rand() % (int)max + (int)min));
        return a;
    }

    void show(const Matrix& matrix)
    {
        for(auto& it1 : matrix)
        {
            for(auto& it2 : it1)
            {
                std::cout << it2 << ' ';
            }
            std::cout << std::endl;
        }
    }

    Matrix multiply(const Matrix& matrix, double c)
    {
        Matrix b(matrix);
        for(auto& it : b)
        {
            for(auto& item : it)
            {
                item *= c;
            }
        }
        return b;
    }

    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2)
    {
        if (matrix1.size() == 0) return matrix2;
        if (matrix2.size() == 0) return matrix1;
        int n = matrix1.size(),m = matrix2.size();
        int n1 = matrix1[0].size(),m1 = matrix2[0].size();
        if(n1 != m)
        {
            throw std::logic_error("doesn't match");
        }
        Matrix ans(n,std::vector<double>(m1,0));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m1; ++j)
            {
                for (int k = 0; k < n1; ++k)
                {
                    ans[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        return ans;
    }

    Matrix sum(const Matrix& matrix, double c)
    {
        if(matrix.size() == 0) return matrix;
        Matrix ans(matrix);
        for(auto& it : ans)
        {
            for(auto& item : it)
            {
                item += c;
            }
        }
        return ans;
    }

    Matrix sum(const Matrix& matrix1, const Matrix& matrix2)
    {
        Matrix res(matrix1);
        int n1 = matrix1.size();
        int n2 = matrix2.size();
        if(n2 == 0 &&  n1 == 0)
        {
            return matrix1;
        }
        if(n1 != n2)
        {
            throw std::logic_error("no matches");
        }
        int m1 = matrix1[0].size(),m2 = matrix2[0].size();
        if(m1 != m2)
        {
            throw std::logic_error("no matches");
        }
        for(int i = 0;i < n1;i ++)
         {
            for(int j = 0;j < m1;j ++)
            {
                res[i][j] += matrix2[i][j];
            }
        }
        return res;
    }

    Matrix transpose(const Matrix& matrix)
    {
        int n = matrix.size();
        if(n == 0)
        {
            return matrix;
        }
        int m = matrix[0].size();
        Matrix res(m,std::vector<double>(n));
        for(int i = 0 ;i < n;i ++)
        {
            for(int j = 0;j < m;j ++)
            {
                res[j][i] = matrix[i][j];
            }
        }
        return res;
    }

    Matrix minor(const Matrix& matrix, size_t n, size_t m)
    {
        if (matrix.size() == 0) return matrix;
        int n1 = matrix.size();
        if (n >= n1 || m >= n1)
        {
            throw std::logic_error("indices out of bound");
        }
        Matrix mat = zeros(n1 - 1, n1 - 1);
        for (int i = 0; i < n1 - 1; ++i)
        {
            for (int j = 0; j < n1 - 1; ++j) {
                int ii = (i < n) ? i : i + 1;
                int jj = (j < m) ? j : j + 1;
                mat[i][j] = matrix[ii][jj];
            }
        }
        return mat;
    }

    double determinant(const Matrix& matrix)
    {
        int n = matrix.size();
        if(n == 0)
        {
            return 1;
        }
        int m = matrix[0].size();
        if(n != m)
        {
            throw std::logic_error("error");
        }
        if(n == 1)
        {
            return matrix[0][0];
        }else if(n == 2)
        {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }
        double ans = 0;
        for(int i = 0;i < n;i ++)
        {
            Matrix tmp = minor(matrix,0,i);
            ans += pow(-1,i) * determinant(tmp) * matrix[0][i];
        }
        return ans;
    }

    Matrix inverse(const Matrix& matrix)
    {
        int n = matrix.size();
        if(n == 0)
        {
            return matrix;
        }
        int m = matrix[0].size();
        if(n != m)
        {
            throw std::logic_error("error");
        }
        double t = determinant(matrix);
        if(t == 0)
        {
            throw std::logic_error("error");
        }
        //求奇异矩阵
        Matrix tmp(n,std::vector<double>(m));
        for(int i = 0;i < n;i ++)
        {
            for(int j = 0;j < m;j ++)
            {
                Matrix mr = minor(matrix,i,j);
                tmp[i][j] = (int)pow(-1,i + j) * determinant(mr);
            }
        }
        Matrix mtx = transpose(tmp);
        return multiply(mtx,1 / t);
    }

    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis)
    {
        int n1, m1, n2, m2;
        n1 = matrix1.size();
        n2 = matrix2.size();
        if (n1 == 0) return matrix2;
        if (n2 == 0) return matrix1;
        Matrix mat;
        m1 = matrix1[0].size(), m2 = matrix2[0].size();
        if (axis == 0)
        {
            if (m1 != m2)
            {
                throw std::logic_error("column number doesn't match while axis = 0");
            }
            mat = zeros(n1 + n2, m1);
            for (int i = 0; i < n1 + n2; ++i)
            {
                for (int j = 0; j < m1; ++j) {
                    mat[i][j] = i < n1 ? matrix1[i][j] : matrix2[i - n1][j];
                }
            }
        }else if (axis == 1)
        {
            if (n1 != n2)
            {
                throw std::logic_error("error");
            }
            mat = zeros(n1, m1 + m2);
            for (int i = 0; i < n1; ++i)
            {
                for (int j = 0; j < m1 + m2; ++j)
                {
                    mat[i][j] = j < m1 ? matrix1[i][j] : matrix2[i][j - m1];
                }
            }
        }else
        {
            throw std::invalid_argument("error");
        }
        return mat;
    }

    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2)
    {
        int n1 = matrix.size();
        if (n1 == 0) return matrix;
        if (r1 >= n1 || r2 >= n1)
        {
            throw std::logic_error("error");
        }
        Matrix mat(matrix);
        std::swap(mat[r1], mat[r2]);
        return mat;
    }
    Matrix ero_multiply(const Matrix& matrix, size_t r, double c)
    {
        int n1 = matrix.size();
        if (n1 == 0) return matrix;
        if (r >= n1)
        {
            throw std::logic_error("error");
        }
        Matrix mat(matrix);
        auto& v = mat[r];
        for (auto& elem : v)
        {
            elem *= c;
        }
        return mat;
    }

    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2)
    {
        int n1 = matrix.size();
        if (n1 == 0) return matrix;
        if (r1 >= n1 || r2 >= n1)
        {
            throw std::logic_error("error");
        }
        Matrix mat(matrix);
        auto& v1 = mat[r1];
        auto& v2 = mat[r2];
        for (int i = 0; i < v1.size(); ++i)
        {
            v2[i] += v1[i] * c;
        }
        return mat;
    }
}
