#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "openMNIST.h"


// смена endian ЛИБО big
uint32_t flip_bytes (uint32_t num) {

    uint32_t a0, a1, a2, a3;

    a0 = (num & 0x000000ff) << 24;
    a1 = (num & 0x0000ff00) << 8;
    a2 = (num & 0x00ff0000) >> 8;
    a3 = (num & 0xff000000) >> 24;
    
    return (a0 | a1 | a2 | a3);
}

// для заполнения структуры заголовка изображения
void fillImgHeader(FILE *file, imgHeader *header) {

    // чтение магического числа 0x00000803
    fread(&header->magicNumber, sizeof(uint32_t), 1, file);
    header->magicNumber = flip_bytes(header->magicNumber);

    // чтение кол-ва изображений
    fread(&header->countImg, sizeof(uint32_t), 1, file);
    header->countImg = flip_bytes(header->countImg);

    // чтение высоты изображения
    fread(&header->widthImg, sizeof(uint32_t), 1, file);
    header->widthImg = flip_bytes(header->widthImg);

    // чтения ширины изображения
    fread(&header->heightImg, sizeof(uint32_t), 1, file);
    header->heightImg = flip_bytes(header->heightImg);

}

// для чтения структуры заголовка изображения
FILE *readImgHeader(char *fileName, imgHeader *header) {

    FILE *images = fopen(fileName, "rb");
    if (images == NULL) {
        printf("WRONG OPEN IMG %s !!\n", fileName);
        exit(1);
    }

    fillImgHeader(images, header);

    return images;
}




// для заполнения структуры заголовка меток изображения
void fillLblHeader(FILE *file, lblHeader *header) {

    // чтение магического числа 0x00000801
    fread(&header->magicNumber, sizeof(uint32_t), 1, file);
    header->magicNumber = flip_bytes(header->magicNumber);

    // чтение кол-ва меток для изображений
    fread(&header->countLbl, sizeof(uint32_t), 1, file);
    header->countLbl = flip_bytes(header->countLbl);
}

// для чтения структуры заголовка меток изображения
FILE *readLblHeader(char *fileName, lblHeader *header) {

    FILE *labels = fopen(fileName, "rb");
    if (labels == NULL) {
        printf("WRONG OPEN LBL %s !!\n", fileName);
        exit(1);
    }

    fillLblHeader(labels, header);

    return labels;
}