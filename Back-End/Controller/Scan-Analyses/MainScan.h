//
// Created by adrien on 24/06/19.
//

#ifndef MCQ_CORRECTION_MAINSCAN_H
#define MCQ_CORRECTION_MAINSCAN_H

#include <vector>
#include <QString>
using std::vector;
using std::pair;

void MainScan(int argc, char** argv, int id_examination, int id_student, vector<pair <int,int>> &answers, QString &stringImage);

#endif //MCQ_CORRECTION_MAINSCAN_H
