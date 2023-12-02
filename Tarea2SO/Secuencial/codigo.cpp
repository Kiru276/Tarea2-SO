#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

// Función para convertir una imagen a escala de grises utilizando el método de luminosidad
void convertirAEscalaDeGrises(Mat& imagen) {
    for (int r = 0; r < imagen.rows; r++) {
        for (int c = 0; c < imagen.cols; c++) {
            Vec3b& pixel = imagen.at<Vec3b>(r, c);
            // Cálculo de la luminosidad utilizando la fórmula: L = 0.299*R + 0.587*G + 0.114*B
            uchar gris = 0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0];
            pixel[0] = gris;
            pixel[1] = gris;
            pixel[2] = gris;
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Uso: " << argv[0] << " <nombre_imagen_color> <nombre_imagen_grises>" << endl;
        return 1;
    }

    // Leer la imagen a color
    Mat imagen = imread(argv[1], IMREAD_COLOR);

    if (imagen.empty()) {
        cout << "No se pudo leer la imagen." << endl;
        return 1;
    }

    // Obtener el tiempo de inicio
    high_resolution_clock::time_point inicio = high_resolution_clock::now();

    // Convertir la imagen a escala de grises
    convertirAEscalaDeGrises(imagen);

    // Obtener el tiempo de finalización
    high_resolution_clock::time_point fin = high_resolution_clock::now();

    // Calcular el tiempo de ejecución en segundos
    double tiempoTotal = duration_cast<duration<double>>(fin - inicio).count();

    // Mostrar el tiempo de ejecución total
    cout << "Tiempo de ejecucion: " << tiempoTotal << " segundos" << endl;

    // Guardar la imagen en escala de grises
    imwrite(argv[2], imagen);

    return 0;
}
