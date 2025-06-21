#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "openMNIST.h"
#include "trainMNIST.h"

int main () {

    FILE *fileImages, *fileLabels;

    imgHeader imgHead;
    lblHeader lblHead;

    fileImages = readImgHeader(TRAIN_IMG_FILENAME, &imgHead);
    fileLabels = readLblHeader(TRAIN_LBL_FILENAME, &lblHead);


    Layer L1;
    initLayer(&L1);

    
    for (int e = 0; e < 10; e++) {

        rewind(fileImages);
        rewind(fileLabels);
        fseek(fileImages, sizeof(imgHeader), SEEK_SET);  // пропуск заголовка
        fseek(fileLabels, sizeof(lblHeader), SEEK_SET);  // пропуск заголовка

        int errCount = 0, correctCount = 0;

        

        for (int countImg = 0; countImg < COUNT_TRAIN_IMAGES; countImg++) {

            Picture img = getOneImg(fileImages);
            uint8_t lbl = getOneLbl(fileLabels);

            VectorDigits target;
            initVectorDigits(lbl, &target);

            // проходим по каждому из 10 перцептронов
            for (int countPerc = 0; countPerc < 10; countPerc++) {
                trainPerceptron(&L1.layer[countPerc], &img, target.res[countPerc]);
            }

            int res = getCurrRes(&L1);
            if (res != lbl) {
                errCount++;
            } else correctCount++;

        }
        
        printf("Correct: %d, Uncorrect: %d, Procent: %.2lf\n", correctCount, errCount, (double)correctCount / COUNT_TRAIN_IMAGES * 100);
    }
    
    printf("Done!!");
    return 0;
}