#include <stdio.h>
#include <io.h>
#include <iostream>
#include <string.h>

using namespace std;


int main(void) {
    _finddata_t fileDir;
    string path = "E:/1/";
    char *dir = "E:/1/*";
    long lfDir;

    if ((lfDir = _findfirst(dir, &fileDir)) != -1l) {
        do {
            if (strcmp(fileDir.name, ".") == 0 || strcmp(fileDir.name, "..") == 0 ||
                (fileDir.attrib & _A_SUBDIR) != 0) {
                continue;
            }

//            printf("%s\n", fileDir.name);
            string tmp = fileDir.name;
            string newFilename = path + tmp + "111";
            tmp = path + tmp;
            cout << tmp.c_str() << endl;
            cout << newFilename << endl;
//            cout << rename(tmp.c_str(), newFilename.c_str()) << endl;
        } while (_findnext(lfDir, &fileDir) == 0);
    }
    _findclose(lfDir);

    return 0;
}