#include <iostream>

int getSimilarity(char a, char b) {
    switch (a) {
        case 'A': {
            switch (b) {
                case 'A':
                    return 5;
                case 'C':
                    return -1;
                case 'G':
                    return -2;
                case 'T':
                    return -1;
                case '-':
                    return -3;
            }
        }
        break;
        case 'C': {
            switch (b) {
                case 'A':
                    return -1;
                case 'C':
                    return 5;
                case 'G':
                    return -3;
                case 'T':
                    return -2;
                case '-':
                    return -4;
            }
        }
        break;
        case 'G': {
            switch (b) {
                case 'A':
                    return -2;
                case 'C':
                    return -3;
                case 'G':
                    return 5;
                case 'T':
                    return -2;
                case '-':
                    return -2;
            }
        }
        break;
        case 'T': {
            switch (b) {
                case 'A':
                    return -1;
                case 'C':
                    return -2;
                case 'G':
                    return -2;
                case 'T':
                    return 5;
                case '-':
                    return -1;
            }
        }
        break;
        case '-': {
            switch (b) {
                case 'A':
                    return -3;
                case 'C':
                    return -4;
                case 'G':
                    return -2;
                case 'T':
                    return -1;
                case '-':
                    return 0;
            }
        }
    }
}

int main() {
    int fir_length = 0;
    int sec_length = 0;
    std::cin >> fir_length;
    char *fir_string = new char[fir_length + 1];
    std::cin >> fir_string;
    std::cin >> sec_length;
    char *sec_string = new char[sec_length + 1];
    std::cin >> sec_string;
    int m_size = std::max(fir_length, sec_length) + 1;
    int **M = new int*[m_size];
    for (int i = 0; i < m_size; ++i) {
        M[i] = new int [m_size];
    }
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            M[i][j] = 0;
        }
    }
    int similarity = 0;
    for (int i = 0; i < fir_length; ++i) {
        M[0][i] = similarity;
        similarity += getSimilarity(sec_string[i], '-');
    }
    similarity = 0;
    for (int i = 0; i < sec_length; ++i) {
        M[i][0] = similarity;
        similarity += getSimilarity(fir_string[i], '-');
    }
    for (int i = 1; i <= fir_length; ++i) {
        for (int j = 1; j <= sec_length; ++j) {
            char c_1 = fir_string[i - 1];
            char c_2 = sec_string[j - 1];
            if(c_1 == c_2) {
                M[i][j] = M[i - 1][j - 1] + getSimilarity(c_1, c_2);
            } else {
                M[i][j] = std::max(std::max((M[i - 1][j - 1] + getSimilarity(c_1, c_2)), (M[i - 1][j] + getSimilarity(c_1, '-'))), (M[i][j - 1] + getSimilarity('-', c_2)));
            }
        }
    }
    std::cout << M[fir_length][sec_length] << std::endl;
    /*for (int i = 1; i <= fir_length; ++i) {
        for (int j = 1; j <= sec_length; ++j) {
            std::cout << M[i][j] << '\t';
        }
        std::cout << std::endl;
    }*/
}