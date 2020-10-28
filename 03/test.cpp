#include "matrix.h"
#include <cassert>

void testGetValue()
{
    vector<int> testMatrix1 = {1, 2,
                               3, 4};

    Matrix M1(2, 2, testMatrix1);
    //обратмся по индексам
    assert(M1[0][0] == 1);
    assert(M1[0][1] == 2);
    assert(M1[1][0] == 3);
    assert(M1[1][1] == 4);

    bool catch_error = false;

    try{
        M1[2][10] = 0;
    }catch(const out_of_range &){
        catch_error = true;
    }
    //проверим словилось ли исключение
    assert(catch_error);

    //присвоим значения по индексу
    M1[0][0] = -1;
    M1[1][1] = -4;

    assert(M1[0][0] == -1);
    assert(M1[1][1] == -4);

    int x = M1[0][1];
    //присовим значение переменной
    assert(x == 2);
}


void testMultNumber()
{
    vector<int> testMatrix1 = {1, 2,
                              3, 4};

    Matrix M1(2, 2, testMatrix1);

    Matrix M2 = M1 * -3;

    assert(M2[0][0] == -3);
    assert(M2[0][1] == -6);
    assert(M2[1][0] == -9);
    assert(M2[1][1] == -12);

    M2 *= -1;

    assert(M2[0][0] == 3);
    assert(M2[0][1] == 6);
    assert(M2[1][0] == 9);
    assert(M2[1][1] == 12);
}

void testAddMatrix()
{
    vector<int> testMatrix1 = {1, 2,
                               3, 4};

    vector<int> testMatrix2 = {-2, 2,
                               3, -5};

    vector<int> testMatrix3 = {1, 2, 3,
                              -4, -5, -6,
                               7, -8, 9};

    Matrix M1(2, 2, testMatrix1);
    Matrix M2(2, 2, testMatrix2);
    Matrix M3(3, 3, testMatrix3);

    Matrix M = M1 + M2;

    assert(M[0][0] == -1);
    assert(M[0][1] == 4);
    assert(M[1][0] == 6);
    assert(M[1][1] == -1);

    bool catch_error = false;

    try{
        Matrix M_err = M + M3; //матрицы разных размеров
    }catch(const out_of_range &){
        catch_error = true;
    }
    assert(catch_error);

    M = M3; //cкопируем матрицу

    Matrix M4 = M3 * 2;
    //складываем 2 одинаковые матрицы
    assert(M + M3 == M4);
}

void testIsEqualMatrix()
{
    vector<int> testMatrix1 = {1, 2,
                               3, 4};

    vector<int> testMatrix2 = {-2, 2,
                               3, -5};

    vector<int> testMatrix3 = {1, 2, 3,
                              -4, -5, -6,
                               7, -8, 9};

    Matrix M1(2, 2, testMatrix1);
    Matrix M2(2, 2, testMatrix2);
    Matrix M3(3, 3, testMatrix3);
    Matrix M4(2, 2);

    for(int i = 0; i < 2; i++){
        for(int k = 0; k < 2; k++){
            M4[i][k] = i * 2 + k + 1; //получим M1
        }
    }

    assert(M1 == M4);
    assert(M1 == M1);
    assert(!(M1 == M2)); //разные значения
    assert(!(M1 == M3)); //разные размеры
}

void testInitMatrix()
{
    vector<int> testMatrix1 = {1, 2,
                               3, 4};

    vector<int> testMatrix2 = {-2, 2, 3,
                               3, -5, -6};

    vector<int> testMatrix3= {1, 2, 3,
                             -4, -5, -6,
                              7, -8, 9};

    Matrix M1(2, 2, testMatrix1);
    Matrix M2(2, 3, testMatrix2);
    Matrix M3(3, 3, testMatrix3);

    assert(M1.getRows() == 2);
    assert(M1.getColumns() == 2);

    assert(M2.getRows() == 2);
    assert(M2.getColumns() == 3);

    assert(M3.getRows() == 3);
    assert(M3.getColumns() == 3);
}



void sampleWithOstrem()
{

    vector<int> testMatrix1 = {1, 2,
                               3, 4};

    vector<int> testMatrix2 = {-2, 2, 3,
                               3, -5, -6};

    vector<int> testMatrix3= {1, 2, 3,
                             -4, -5, -6,
                              7, -8, 9};

    Matrix M1(2, 2, testMatrix1);
    Matrix M2(2, 3, testMatrix2);
    Matrix M3(3, 3, testMatrix3);

    cout<<"M1: \n"<<M1;
    cout<<"M2: \n"<<M2;
    cout<<"M3: \n"<<M3;
}





int main(){

    testGetValue();
    testMultNumber();
    testAddMatrix();
    testIsEqualMatrix();
    testInitMatrix();
    sampleWithOstrem();

    cout<<"Success!"<<endl;
    return 0;
}
