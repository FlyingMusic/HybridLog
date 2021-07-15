#include "utility.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

bool createDirectory(const char *path) {
    if(path == NULL || path[0] == '\0'){
        printf("can't make directory(%s), path is not given", path);
        return false;
    }
    DIR *dir = opendir(path);
    if(dir != NULL){
        closedir(dir);
        return true;
    }

    FILE *fp = fopen(path,"a");
    if(fp != NULL){
        fclose(fp);
        return true;
    }

    char buf[1024] = {0};
    snprintf(buf,1024,"%s",path);
    char path_name[1024] = {0};
    char *sep;
    char *dirname = strtok_r(buf,"/",&sep);
    if(buf[0] == '/')
        path_name[0] = '/';
    while(dirname != NULL && dirname[0] != 0){
        strcat(path_name,dirname);
        strcat(path_name,"/");
        if(strcmp(dirname,".") != 0 && strcmp(dirname,"..") != 0 && strstr(dirname,".") != NULL)
            break;
        if((dir = opendir(path_name)) == NULL){
            if(ENOENT != errno){
                dirname = strtok_r(buf,"/",&sep);
                continue;
            }
            printf("directory(%s) is not exists, will create it",dirname);
            if(-1 == mkdir(path_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)){
                printf("mkdir %s failed in for. error info is [%s]", dirname, strerror(errno));
                return false;
            }
        }else{
            closedir(dir);
        }
        dirname = strtok_r(NULL,"/",&sep);
    }
    return true;
}

