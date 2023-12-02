#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>

using namespace cv;
using namespace std;

// Estructura para almacenar los datos necesarios para procesar una parte de la imagen
struct ThreadData {
    Mat* image;
    int startRow;
    int endRow;
};

// Función que se ejecuta en cada hilo para procesar una parte de la imagen
void processImageThread(ThreadData data) {
    for (int r = data.startRow; r < data.endRow; r++) {
        for (int c = 0; c < data.image->cols; c++) {
            Vec3b& pixel = data.image->at<Vec3b>(r, c);
            // Aplicar el método de luminosidad para convertir a escala de grises
            uchar gray = pixel[0] * 0.114 + pixel[1] * 0.587 + pixel[2] * 0.299;
            pixel[0] = gray;
            pixel[1] = gray;
            pixel[2] = gray;
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 4) {
        cout << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida> <num_threads>" << endl;
        return 1;
    }

    // Cargar la imagen de entrada
    Mat image = imread(argv[1], IMREAD_COLOR);
    if (image.empty()) {
        cout << "No se pudo cargar la imagen de entrada." << endl;
        return 1;
    }

    // Obtener el número de threads desde el argumento de línea de comandos
    int numThreads = atoi(argv[3]);
    if (numThreads < 1) {
        cout << "Número inválido de threads." << endl;
        return 1;
    }

    // Dividir la imagen en partes iguales para cada hilo
    int rowsPerThread = image.rows / numThreads;
    vector<thread> threads;
    for (int i = 0; i < numThreads; i++) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? image.rows : (startRow + rowsPerThread);
        ThreadData threadData;
        threadData.image = &image;
        threadData.startRow = startRow;
        threadData.endRow = endRow;
        threads.emplace_back(processImageThread, threadData);
    }

    // Medir el tiempo de ejecución
    auto startTime = chrono::high_resolution_clock::now();

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        thread.join();
    }

    // Calcular el tiempo de ejecución total
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> totalTime = endTime - startTime;
    double totalTimeSeconds = totalTime.count();

    // Guardar la imagen resultante
    imwrite(argv[2], image);

    cout << "Imagen procesada y guardada correctamente." << endl;
    cout << "Tiempo de ejecución total: " << totalTimeSeconds << " segundos." << endl;

    return 0;
}