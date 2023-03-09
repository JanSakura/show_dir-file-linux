#include<iostream>
#include <sys/types.h>
#include <dirent.h>

unsigned int tabs=0;

void readDir(const std::string& dirName){
    DIR* dir=opendir(dirName.c_str());
    dirent* pDirent=nullptr;
    if(!dir){
        perror("dir nullptr,opendir err");
        return ;
    }
      //检查错误，虽然基本不会出错
    int err=errno;
    //循环打印当前目录下的文件名
    while(pDirent=readdir(dir)){
        const std::string& fName=pDirent->d_name;
        if(fName=="." || fName==".."){
            continue;
        } 
        if(pDirent->d_type==DT_DIR){
            for(unsigned i=0;i<tabs;++i){
                std::cout<<"    ";
            }
            if(dirName=="./"){
            std::cout<<dirName<<fName<<std::endl;
            const std::string childDirName=dirName+fName;
            ++tabs;
            readDir(childDirName);
            --tabs;
            }else{
            std::cout<<dirName<<"/"<<fName<<std::endl;
            const std::string childDirName=dirName+"/"+fName;
            ++tabs;
            readDir(childDirName);
            --tabs;
            }
        }else{
            for(unsigned i=0;i<tabs;++i){
                std::cout<<"    ";
            }
            if(dirName=="./"){
                std::cout<<dirName<<fName<<"  -F"<<std::endl;
            }else{
                std::cout<<dirName<<"/"<<fName<<"  -F"<<std::endl;
            }
        }
    }
    if(err!=errno){
        perror("readdir error");
        return ;
    }
    delete(pDirent);
    pDirent=nullptr;
    closedir(dir);
} 
int main(){
    readDir("./"); 
    return 0;
}
