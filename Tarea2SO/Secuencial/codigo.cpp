#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

uchar pixelToGrayScale(const cv::Vec3b& pixel) {
    return static_cast<uchar>(0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0]);
}

void convertToGrayScale(const cv::Mat& inputImage, cv::Mat& outputImage) {
    for (int r = 0; r < inputImage.rows; ++r) {
        for (int c = 0; c < inputImage.cols; ++c) {
            outputImage.at<uchar>(r, c) = pixelToGrayScale(inputImage.at<cv::Vec3b>(r, c));
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " input_image_path output_image_path" << std::endl;
        return 1;
    }

    std::string inputImagePath = argv[1];
    std::string outputImagePath = argv[2];

    cv::Mat inputImage = cv::imread(inputImagePath, cv::IMREAD_COLOR);
    if (inputImage.empty()) {
        std::cout << "Error al leer la imagen." << std::endl;
        return 1;
    }

    cv::Mat outputImage(inputImage.rows, inputImage.cols, CV_8UC1);

    // Iniciar el temporizador.
    auto startTime = std::chrono::steady_clock::now();

    // Convertir la imagen a escala de grises de manera secuencial.
    convertToGrayScale(inputImage, outputImage);

    // Detener el temporizador y calcular el tiempo total transcurrido.
    auto endTime = std::chrono::steady_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    double totalTimeInSeconds = totalTime.count() / 1000.0;

    std::cout << "Imagen convertida correctamente.\n";
    std::cout << "Tiempo de ejecución: " << totalTimeInSeconds << " segundos." << std::endl;

    // Guardar la imagen de salida.
    cv::imwrite(outputImagePath, outputImage);

    return 0;
}
