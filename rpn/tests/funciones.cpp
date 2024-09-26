#include<cmath>
#include<vector>
#include<string>

using std::vector;
using std::string;

double calcula_media(vector<double> datos) {
    double sum = 0;
    size_t len = datos.size();
    for (int i = 0; i < len; ++i) {
        sum += datos[i];
    }
    return sum/len;
}

double al_cubo(double a) {
    return a * a * a;
}

bool es_par(int n) {
    return n % 2 == 0 ? true : false;
}

string decir_hola(string nombre) {
    return "Hola " + nombre;
}

