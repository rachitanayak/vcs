#ifndef HEADER_H
#define HEADER_H

#include<QString>
#include<string>
using namespace std;
int compareFiles(string file1,string file2);
int countFiles(QString pathToDirectory );
void createVersion(QString,string,string);
void revert(string filepath,string filename,int count);
void updateTime();

#endif // HEADER_H
