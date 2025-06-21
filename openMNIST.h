#include <stdio.h>

#define TRAIN_IMG_FILENAME "train-images.idx3-ubyte"
#define TRAIN_LBL_FILENAME "train-labels.idx1-ubyte"

#define TEST_IMG_FILENAME "t10k-images.idx3-ubyte"
#define TEST_LBL_FILENAME "t10k-labels.idx1-ubyte"


// смена endian ЛИБО big
uint32_t flip_bytes (uint32_t num);

// структура для хранения данных заголовка изображений
typedef struct {
    uint32_t magicNumber;
    uint32_t countImg;
    uint32_t widthImg;
    uint32_t heightImg;
} imgHeader;

// для заполнения структуры заголовка изображения
void fillImgHeader(FILE *file, imgHeader *header);

// для чтения структуры заголовка изображения
FILE *readImgHeader(char *fileName, imgHeader *header);


// структура для хранения данных заголовка меток изображений
typedef struct {
    uint32_t magicNumber;
    uint32_t countLbl;
} lblHeader;

// для заполнения структуры заголовка меток изображения
void fillLblHeader(FILE *file, lblHeader *header);

// для чтения структуры заголовка меток изображения
FILE *readLblHeader(char *fileName, lblHeader *header);