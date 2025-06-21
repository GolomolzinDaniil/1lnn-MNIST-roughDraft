#include <stdio.h>

#define COUNT_TRAIN_IMAGES 60000 //< размер (кол-во изображений) обучающей выборки
#define COUNT_TESTS_IMAGES 10000 //< размер тестовой выборки
#define LEARNING_RATE 1 //< для однослойного MNIST приемлемо повезло
#define AREA 784 // 28*28
#define SIZE 28
#define DIGITS 10

// изображение
typedef struct {
    uint8_t pixels[AREA];
} Picture;

// получение одного изображения
Picture getOneImg(FILE *file);

// получение одной метки
uint8_t getOneLbl(FILE *file);

// перцептрон
typedef struct {
    double input[AREA];
    double weight[AREA];
    double bias;
    double output;
} Perceptron;

// слой перцептронов
typedef struct {
    Perceptron layer[DIGITS];
} Layer;

// создание слоя И инициализация значениями по умолчанию
void initLayer (Layer *l);

// вектор предположения
typedef struct {
    int res[DIGITS];
} VectorDigits;

// помечает целевую цифру (ставит 1 на месте цифры которая написана на изображении)
void initVectorDigits (uint8_t digit, VectorDigits *vector);

// переносит изображение в перцептрон
void setPixelsPerc (Perceptron *perc, Picture *img);

// функция активации, чтоб было от 0 до 1
double funcActive (double x);

// выход каждого перцептрона рассчитывается путем суммирования всех его 724 взвешенных входов + нормирование
void calcWeight (Perceptron *perc);

// рассчет ошибки вычисления
double getPercErr(Perceptron *perc, int target);

// обновление значений
void updateWeight(Perceptron *perc, double err);

// тренирует один перцептрон
void trainPerceptron(Perceptron *perc, Picture *img, int target);

// возвращает элемент который с наибольшей вероятностью
int getCurrRes (Layer *l);