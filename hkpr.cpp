#include<iostream>

using namespace std;


void print_matrix(int **matrix, int m) // функция создания и заполнения двумерного массива 0 и 1
{
    for (int i = 0;i < m;i++)
    {
        for (int j = 0;j < m;j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int *Above_left(int i, int j, int **matrix, int m) // функция которая проверяет слева и справа
{
    int above, left;
    int *arr = new int[2];
    if (i > 0 && j > 0)
    {
        if (matrix[i][j] == matrix[i - 1][j - 1])
        {
            above = 2;
            left = 2;
        }
        else
        {
            above = matrix[i - 1][j];
            left = matrix[i][j - 1];
        }
    }
    else if (i > 0 && j == 0)
    {
        above = matrix[i - 1][j];
        left = 0;
    }
    else if (i == 0 && j > 0)
    {
        above = 0;
        left = matrix[i][j - 1];
    }
    else
    {
        above = 0;
        left = 0;
    }
    arr[0] = above;
    arr[1] = left;
    return arr;
}

int *Find_prim1(int **a, int b, int Lw) 
{
    int *row = new int[Lw];
    for (int i = 0;i < Lw;i++)
    {
        for(int j = 0;j < Lw;j++)
        {
            if (a[i][j] == b)
            {
                int k = 0;
                row[k] = i;//хранятся индексы по строкам 
                k++;
            }
        }
    }
    return row;
}


int *Find_Prim2(int **a, int b, int Lw)
{
    int *col = new int[Lw];
    for (int i = 0;i < Lw;i++)
    {
        for(int j = 0;j < Lw;j++)
        {
            if (a[i][j] == b)
            {
                int k = 0;
                col[k] = j;// хранятся индексы по столбцам
                k++;
            }
        }
    }
    return col;
}



int **Find(int **label,int a, int b, int c, int d, int Lw) // функция, которая объединяет кластеры
{
    int x = label[a][b];
    int y = label[c][d];
    int aa, bb;
    int *row = Find_prim1(label, x, Lw);
    int *col = Find_Prim2(label, x, Lw);
    for (int i = 0;i < Lw;i++)
    {
        aa = row[i];
        bb = col[i];
        label[aa][bb] = y;
    }
    delete[] row;
    delete[] col;
    return label;

}

int **Label(int **matrix, int m)
{
    int **label = new int*[m];//заполнен нулями 
    for (int i = 0;i < m;i++)
    {
        label[i] = new int[m];
        for (int j = 0;j < m;j++)
        {
            label[i][j] = 0;
        }
    }
    
    int id = 1;
    int above, left;
    int *l_a;
    for (int i = 0;i < m;i++)
    {
        for(int j = 0;j < m;j++)
        {
            if (matrix[i][j])
            {
                l_a = Above_left(i, j, matrix, m); // мы получаем массив из двух элемнтов
                above = l_a[0];
                left = l_a[1];
                // здесь определяем к какому кластеру будет принадлежать текущая ячейка 
                if (left == 0 && above == 0)
                {
                    label[i][j] = id;
                    id = id + 1;
                }
                else if (left == 1 && above == 0)
                {
                    label[i][j] = label[i][j - 1];
                }
                else if (left == 0 && above == 1)
                {
                    label[i][j] = label[i - 1][j];
                }
                else if (above == 2 && left == 2)
                {
                    label[i][j] = label[i - 1][j - 1];
                }
                else
                {
                    int **Lab_Prim = Find(label, i, j - 1, i - 1, j, m);
                    label = Lab_Prim;
                    label[i][j] = label[i - 1][j];
                }

            }
        }
    }
    delete[] l_a;
    return label;

}

int main()
{
    cout << "Enter the size :" << endl;
    int a;
    cin >> a;
    int **matrix;
    matrix = new int*[a];
    for (int i = 0;i < a;i++)
    {
        matrix[i] = new int[a];
        for (int j = 0;j < a;j++)
        {
            cin >> matrix[i][j];
        }
    }
    cout << "--input--" << endl;
    print_matrix(matrix, a);
    cout << "--output--" << endl;
    int **L = Label(matrix, a);
    print_matrix(L, a);
    return 0;
    for (int i = 0;i < a;i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    for (int i = 0;i < a;i++)
    {
        delete[] L[i];
    }
    delete[] L;
}