#ifndef BAR_H
#define BAR_H
#include "QDataStream"
#include "QFile"
#include "QDebug"
#include <math.h>

#include "mainwindow.h"
#include "filestream.h"
class BARFile
{
public:
    std::vector<char> data;
    quint16 type=0;
    quint16 dup=0;
    char* id = new char[4];
};

class BAR
{
public:
    BAR();
    void load(QFile *Sfile);
    void save(QFile *file);
    int fileCount();
    std::vector<BARFile> fileList;

};
#endif // BAR_H
