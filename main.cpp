#include <stdio.h>
#include <io.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <regex>
#include <fstream>

using namespace std;


/**
 * 获取文件后缀名
 * @param filename
 * @return 获取不到返回 ""
 */
string getExt(const string &filename) {
    char *ext;
    string returnStr = "";
    ext = strrchr(filename.c_str(), '.');
    if (ext == nullptr) { return ""; }

    int len = strlen(ext);
    if (len < 2) { return ""; }

    for (auto i = 0; i < len; ++i) {  // 去掉"."号
        if (i == 0) { continue; }
        returnStr += ext[i];
    }

    return returnStr;
}

/**
 * @param str
 * @param start  begin(arr[])
 * @param last  end(arr[])
 * @return
 */
bool inArray(string str, string *start, string *last) {
    for (; start != last; ++start) {
        if (str == *start) {
            return true;
        }
    }
    return false;
}

void movieProcess(const string &file) {
    smatch what;
    auto start = file.begin();
    auto end = file.end();

    std::cout << file << endl;
    while (regex_search(start, end, what, regex("\\d+"))) {
        std::cout << what[0] << std::endl;
        start += what.position() + what.length();
    }

}

vector<string> strSplit(const string &str, const string &split) {
    vector<string> res;
    size_t splitLen = split.length();
    size_t pos;
    string findStr = str;
    do {
        pos = findStr.find(split);
        res.push_back(findStr.substr(0, pos));
        findStr = findStr.substr(pos + splitLen);
    } while (pos != string::npos);
    return res;
}

bool inputMatched(string file, string inputName) {
    //全部转为小写
    transform(file.begin(), file.end(), file.begin(), ::tolower);
    transform(inputName.begin(), inputName.end(), inputName.begin(), ::tolower);

    smatch inputMatch;
    if (!regex_search(inputName, inputMatch, regex("#+"))) {
        return false;
    }

    vector<string> inputNameSplit = strSplit(inputName, inputMatch[0]);
    if (inputNameSplit.size() == 0) {
        return false;
    }

    for (int i = 0; i < inputNameSplit.size(); ++i) {
        if (string::npos == file.find(inputNameSplit[i])) {
            return false;
        }
    }


    return true;
}

void subsProcess(const string &path, const string &file, const string &inputName, const string &outputName) {
    if (!inputMatched(file, inputName)) {
        return;
    }

    smatch outputMatch;
    if (!regex_search(outputName, outputMatch, regex("#+"))) {
        return;
    }

    smatch inputMatch;
    if (!regex_search(inputName, inputMatch, regex("#+"))) {
        return;
    }

    unsigned inputMatchLen = (unsigned) inputMatch[0].length();
    string matchRepeat(inputMatchLen, '#');

    string strNum = file.substr(inputName.find(matchRepeat), inputMatchLen);
    string NewFilename = path + regex_replace(outputName, regex(matchRepeat), strNum);
    std::cout << " ---------------------------------------------------------- " << endl;
    std::cout << path + file + "\r\nrename to:\r\n" + NewFilename << endl;
    rename((path + file).c_str(), NewFilename.c_str());

    return;

    smatch what;
    auto start = file.begin();
    auto end = file.end();

    std::cout << file << endl;
    while (regex_search(start, end, what, regex("\\d+"))) {
        std::cout << what[0] << std::endl;
        start += what.position() + what.length();
    }

}

int main(void) {
    string inputName = "[ANK-Raws] Guilty Crown - ## (BDrip 1920x1080 x264 FLAC Hi10P).ass";
    string outputName = "Guilty Crown 2011 EP## [BD 1920x1080 23.976fps AVC-yuv420p10 FLACx2] - yan04000985&VCB-Studio.ass";
    string subPostfix[] = {"ssa", "ass", "smi", "str", "sub", "lrc", "sst", "txt", "xss", "psb", "ssb"};
    string moviePostfix[] = {"wmv", "asf", "asx", "rm", "rmvb", "mpg", "mpeg", "mpe", "3gp", "mov", "mp4", "m4v",
                             "avi",
                             "mkv", "flv", "vob"};


    inArray("mkv", begin(moviePostfix), end(moviePostfix));
    vector<string> subs, movies;

    _finddata_t fileDir;
    string path = "D:/Guilty Crown/";
    char *dir = "D:/Guilty Crown/*";
    int lfDir;

    if ((lfDir = _findfirst(dir, &fileDir)) != -1l) {
        do {
            if (strcmp(fileDir.name, ".") == 0 || strcmp(fileDir.name, "..") == 0 ||
                (fileDir.attrib & _A_SUBDIR) != 0) {
                continue;
            }

            string tmp = fileDir.name;
            tmp = path + tmp;
            string ext = getExt(fileDir.name);
            transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

            if (inArray(ext, begin(moviePostfix), end(moviePostfix))) {
//                movies.push_back(tmp);
                movies.push_back(fileDir.name);
            }
            if (inArray(ext, begin(subPostfix), end(subPostfix))) {
//                subs.push_back(tmp);
                subs.push_back(fileDir.name);
            }
        } while (_findnext(lfDir, &fileDir) == 0);
    }
    _findclose(lfDir);


    for (auto i = movies.begin(); i != movies.end(); ++i) {
//        movieProcess(*i);
    }

    for (auto i = subs.begin(); i != subs.end(); ++i) {
        subsProcess(path, *i, inputName, outputName);
    }

}
