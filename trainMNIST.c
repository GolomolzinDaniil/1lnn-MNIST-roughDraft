#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "trainMNIST.h"

// инициализация значениями по умолчанию
void initLayer (Layer *l) {

    for (int i = 0; i < DIGITS; i++) {
        for (int j = 0; j < AREA; j++) {

            l->layer[i].input[j]  = 0;
            l->layer[i].weight[j] = (rand() / (double)RAND_MAX);
        }
        l->layer[i].output = 0;
        l->layer[i].bias = (rand() / (double)RAND_MAX);
    }
}

// получение одного изображения
Picture getOneImg(FILE *file) {

    Picture img;
    size_t read = fread(&img.pixels, sizeof(uint8_t), AREA, file);

    if (read != AREA) {
        printf("WRONG READ IMG !!");
        exit(1);
    }

    return img;
}

// получение одной метки
uint8_t getOneLbl(FILE *file) {

    uint8_t lbl;
    size_t read = fread(&lbl, sizeof(uint8_t), 1, file);
    
    if (read != 1) {
        printf("WRONG READ LBL !!");
        exit(1);
    }

    return lbl;
}

// помечает целевую цифру
void initVectorDigits (uint8_t digit, VectorDigits *vector) {

    for (int i = 0; i < 10; i++) {
        vector->res[i] = 0;
    }
    vector->res[digit] = 1;
}

// переносит изображение в перцептрон
void setPixelsPerc (Perceptron *perc, Picture *img) {

    for (int i = 0; i < AREA; i++) {

        perc->input[i] = img->pixels[i] ? 1 : 0;
        // perc->input[i] = img->pixels[i] /  255.0;
    }
}

// функция активации, чтоб было от 0 до 1
double funcActive (double x) {
    // x = (x > 45.0) ? 1.0 : (x < -45.0) ? 0.0 : x;
    return 1.0 / (1.0 + exp(-x));
}

// выход каждого перцептрона рассчитывается путем суммирования всех его 724 взвешенных входов + нормирование
void calcWeight (Perceptron *perc) {

    perc->output = 0.0;
    for (int i = 0; i < AREA; i++) {

        perc->output += perc->input[i] * perc->weight[i];
    }
    perc->output = funcActive(perc->output + perc->bias);
}

// рассчет ошибки вычисления
double getPercErr(Perceptron *perc, int target) {
    return (double)target - perc->output;
}

// обновление значений
void updateWeight(Perceptron *perc, double err) {
    
    for (int i = 0; i < AREA; i++) {
        perc->weight[i] += err * perc->input[i] * LEARNING_RATE;
    }
    perc->bias += err * LEARNING_RATE;
}

// тренирует один перцептрон
void trainPerceptron(Perceptron *perc, Picture *img, int target) {

    setPixelsPerc(perc, img);

    calcWeight(perc);

    int err = getPercErr(perc, target);
    updateWeight(perc, err);

}

// возвращает элемент который с наибольшей вероятностью
int getCurrRes (Layer *l) {
    
    double maxValue = 0;
    int maxIndex = 0;

    for (int i = 0; i < DIGITS; i++) {

        if (l->layer[i].output > maxValue) {
            maxValue = l->layer[i].output;
            maxIndex = i;
        }
    }

    return maxIndex;
}