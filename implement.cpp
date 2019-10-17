#include"header.h"
#include<QDir>
#include<QCryptographicHash>
#include<time.h>
#include<iostream>
#include<fstream>
#include<conio.h>
#include<string>
using namespace std;
char rt[20];
char dt[20];
int compareFiles(string ifile,string temp)
{

    const char* ip=ifile.c_str();
    const char* ip2=temp.c_str();
    FILE *f1;
    FILE *f2;
    f1=fopen(ip,"r");
    f2=fopen(ip2,"r");
    bool diff = 0;
        int N = 65536;
        char* b1 = (char*) calloc (1, N+1);
        char* b2 = (char*) calloc (1, N+1);
        size_t s1, s2;

        do {
            s1 = fread(b1, 1, N, f1);
            s2 = fread(b2, 1, N, f2);

            if (s1 != s2 || memcmp(b1, b2, s1)) {
                diff = 1;
                break;
            }
          } while (!feof(f1) || !feof(f2));

        free(b1);
        free(b2);

        if (diff) return 1;
        else return 0;

}

int countFiles(QString filePath)
{
    int n=0;
    QDir directory(filePath);
    QStringList files = directory.entryList(QStringList() << "*.txt" ,QDir::Files);
    foreach(QString filename, files) {
     n++;
    }
    return n;
}
void updateTime()
{
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime (rt,20,"%I:%M%p",timeinfo);
    strftime (dt,20,"%x",timeinfo);


}
void createVersion(QString path,string ifile,string user)
{
    string temp="C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\temp.txt";
    string filepath=path.toLocal8Bit().constData();
    string version;


    if(compareFiles(ifile,temp)==1){

    ifstream fp(ifile, std::ios::binary);

    int count = countFiles(path);
     version = to_string(count);
     string ofile=filepath+"\\"+"program"+user[5]+"."+version+".txt";
     ofstream vers(ofile, std::ios::binary);
     vers<<"Version:"<<user[5]<<"."<<version;
     vers<<"\n"<<"------------------------------------------------------------------------------------------------------------------"<<"\n";
     vers << fp.rdbuf();
     updateTime();
     vers<<"\n"<<"------------------------------------------------------------------------------------------------------------------";
     vers<<"\nDate Created:"<<dt;
     vers<<"\nTime Created:"<<rt;
     vers.close();
    }
    else {

    }

}
void revert(string filepath,string filename,int count)
{
    char vers=filename.at(9);
    int version=vers-'0';
    string ifile=filepath+"program"+filename[7]+"."+to_string(version)+".txt";
    string ofile=filepath+"program.txt";
    ifstream ip(ifile,ios::binary);
    ofstream fp(ofile,ios::binary);

    char ch;
    std::string file_contents = "";
    // READ FILE CONTENTS AS STRING
            while ( ip>> std::noskipws >> ch)
            {
                file_contents += ch;
            }
            // GET WORD TO BE DELETED
                    std::string word1="Version:";
                    string word2="Date Created:";
                    string word3="Time Created:";
                    string word4="------------------------------------------------------------------------------------------------------------------";


                    std::string::size_type found1;
                    string::size_type found2;
                    string::size_type found3;
                    string::size_type found4;

                    //DELETE WORDS FROM STRING
                    found1 = file_contents.find(word1);
                    if (found1!=std::string::npos )
                    file_contents.erase(found1, word1.length()+3);
                    found2=file_contents.find(word2);
                    if(found2!=std::string::npos)
                    file_contents.erase(found2, word2.length()+8);
                    found3=file_contents.find(word3);
                    if(found3!=std::string::npos)
                    file_contents.erase(found3, word3.length()+7);
                    found4=file_contents.find(word4);
                    if(found4!=std::string::npos )
                    file_contents.erase(found4, word4.length());
                    found4=file_contents.find(word4);
                    if(found4!=std::string::npos )
                    file_contents.erase(found4, word4.length());
                    fp<<file_contents;


    /* program 1.3.txt:1-userid-user[5],3-version no-file[9];*/
    for(int i=version+1;i<=count;i++)
    {
        string path=filepath+"program"+filename[7]+"."+to_string(i)+".txt";
        const char *finalpath=path.c_str();
        remove(finalpath);
    }


}



