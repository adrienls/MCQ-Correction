//
// Created by jerem on 20/06/2019.
//

#ifndef SCAN_PROTOTYPE2_DEBUG_H
#define SCAN_PROTOTYPE2_DEBUG_H

#include "Scanner.h"
void findPositions(QImage &image){
    vector<int> xies = positions(image);
    vector<int> yies = positions(image, true);

    for (int i = 0; i < xies.size(); i++){
        for (int j = 0; j < yies.size(); j++){
            image.setPixel(xies[i], yies[j], qRgb(255, 0, 0));
        }
    }
}





#endif //SCAN_PROTOTYPE2_DEBUG_H
