#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "libconfig.h"
#include "Config.h"

using namespace std ;
Config::Config(){
#ifndef _SUPPORT_APPLE_
    cfg = NULL;
#endif
    m_filename = NULL;
    m_filepath = NULL;
}

Config::~Config(){
#ifndef _SUPPORT_APPLE_
    if(cfg != NULL){
        config_destroy(cfg);
            free(cfg);
    }
#endif
    if(m_filename != NULL)
        free(m_filename);
    if(m_filepath != NULL)
        free(m_filepath);
}

int Config::load(const char *file){
    if(m_filename != NULL){
        free(m_filename);
        m_filename = NULL;
    }
    if (file != NULL) {
        m_filename = strdup(file);
    } else {
	return -1;
    }
#ifndef _SUPPORT_APPLE_ 
    if(cfg == NULL){
        cfg = (config_t*)malloc(sizeof(config_t));
        config_init(cfg);
    }
    struct stat st;
    stat(m_filename,&st);
    if(S_IFDIR & st.st_mode){
        if(m_filename != NULL){
            free(m_filename);
            m_filename = NULL;
        }
        m_filepath = strdup(file);
        return 0;
    }
    if(m_filename != NULL){
        int ret = config_read_file(cfg,m_filename);
        if(!ret){
            printf("read config file(%s) error,msg:%s,linenum:%d\n",m_filename,cfg->error_text,cfg->error_line);
            return -1;
        }
    }else{
        printf("no input configurate file\n");
    }
#endif
    return 0;
}
char *Config::GetFilepath(){
    if(m_filepath != NULL){
        if(strlen(m_filepath) > 0){
            return m_filepath;
        }else{
            return NULL;  
        }
    }else {
        if(m_filename == NULL){
            const char *filepath = "./";
            m_filepath = strdup(filepath);
            return m_filepath;
        }
        m_filepath = (char *)malloc(sizeof(char) * 256);
        if(m_filepath == NULL){
            printf("Config filepath malloc failed");
            return NULL;
        }
        bzero(m_filepath, sizeof(m_filepath));
        char *base_name = strrchr(m_filename,'/');
        if(base_name == NULL){
            strcpy(m_filepath,"./");
        }else{
            strcpy(m_filepath, m_filename);
            m_filepath[base_name - m_filename] = 0;
        }
        return m_filepath;
    }
}

void Config::GetValue(const char *name, bool& num, bool def){
    num = def ;
#ifndef _SUPPORT_APPLE_
    int entry ;
    if(config_lookup_bool(cfg,name,&entry))
        num = entry ;
#endif
    return ;
}

void Config::GetValue(const char *name, int& num, int def){
    num = def ;
#ifndef _SUPPORT_APPLE_
    if(!config_lookup_int(cfg,name,&num))
        num = def ;
#endif
    return ;
}

void Config::GetValue(const char *name, float& num, float def){
    num = def;
    double _num = def;
#ifndef _SUPPORT_APPLE_
    if(!config_lookup_float(cfg,name,&_num))
       _num = def ;
#endif
        num = _num ;
    return ;
}

void Config::GetString(const char *name, char  *str, const char *def){
    strcpy(str,def);
#ifndef _SUPPORT_APPLE_
    const char *entry ;
    if(config_lookup_string(cfg,name,&entry)){
        strcpy(str,entry);
    }else{
        strcpy(str,def);
    }
#endif
    return ;
}

int Config::GetLength(const char* name, int& length)
{
    int ret = 0;
    #ifndef _SUPPORT_APPLE_
    config_setting_t* scalar = config_lookup(cfg, name);
    if (NULL != scalar) {
        int len = config_setting_length(scalar);
        if (len != 0) {
            length = len;
        } else {
            ret = -1;
        }
    } else {
        ret = -1;
    }
    #endif
    return ret;
}

int Config::GetSettingIntElem(const char* name, int& value, int index, int def)
{
    value = def;
    int ret = 0;
    #ifndef _SUPPORT_APPLE_
    config_setting_t* scalar = config_lookup(cfg, name);
    if (NULL != scalar) {
        int len = config_setting_length(scalar);
        if (len > 0 && index < len && index >= 0) {
            value = config_setting_get_int_elem(scalar, index);
        } else {
            ret = -1;
        }
    } else {
        ret = -1;
    }
    #endif
    return ret;
}

int Config::GetSettingStringElem(const char* name, string& value, int index, const string& def)
{
    value = def;
    int ret = 0;
    #ifndef _SUPPORT_APPLE_
    config_setting_t* scalar = config_lookup(cfg, name);
    if (NULL != scalar) {
        int len = config_setting_length(scalar);
        if (len > 0 && index < len && index >= 0) {
            value = config_setting_get_string_elem(scalar, index);
        } else {
            ret = -1;
        }
    } else {
        ret = -1;
    }
    #endif
    return ret;
}



void *Config::GetSetting(const char* name) {
    #ifndef _SUPPORT_APPLE_
    return (void*)config_lookup(cfg, name);
    #endif
    return NULL;
}

void *Config::GetSetting(void *setting, int index) {
    if (NULL == setting)
        return NULL;

    #ifndef _SUPPORT_APPLE_
    return (void*)config_setting_get_elem((config_setting_t*)setting, index);
    #endif
    return NULL;
}

void *Config::GetSetting(void *setting, const char *name) {
    if (NULL == setting)
        return NULL;

    #ifndef _SUPPORT_APPLE_
    return (void*)config_lookup_from((config_setting_t*)setting, name);
    #endif
    return NULL;
}

int Config::GetSettingLength(void *setting, int& length) {
    int ret = 0;
    #ifndef _SUPPORT_APPLE_
    config_setting_t* scalar = (config_setting_t*)setting;
    if (NULL != scalar) {
        int len = config_setting_length(scalar);
        if (len != 0) {
            length = len;
        } else {
            ret = -1;
        }
    } else {
        ret = -1;
    }
    #endif
    return ret;
}

int Config::GetSettingIntElem(void *setting, int& value, int index, int def) {
    value = def;
    int ret = 0;
    #ifndef _SUPPORT_APPLE_
    config_setting_t* scalar = (config_setting_t*)setting;
    if (NULL != scalar) {
        int len = config_setting_length(scalar);
        if (len > 0 && index < len && index >= 0) {
            value = config_setting_get_int_elem(scalar, index);
        } else {
            ret = -1;
        }
    } else {
        ret = -1;
    }
    #endif
    return ret;
}

int Config::GetSettingStringElem(void *setting, std::string& value, int index, const std::string& def) {
    value = def;
    int ret = 0;
    #ifndef _SUPPORT_APPLE_
    config_setting_t* scalar = (config_setting_t*)setting;
    if (NULL != scalar) {
        int len = config_setting_length(scalar);
        if (len > 0 && index < len && index >= 0) {
            value = config_setting_get_string_elem(scalar, index);
        } else {
            ret = -1;
        }
    } else {
        ret = -1;
    }
    #endif
    return ret;
}

void Config::GetSettingValue(void *setting, const char *name, float& num, float def) {
    num = def;
    #ifndef _SUPPORT_APPLE_
    config_setting_t* scalar = (config_setting_t*)setting;
    if (NULL != scalar) {
        double _num;
        if (config_setting_lookup_float(scalar, name, &_num))
            num = _num;
    } 
    #endif
    return ;
}

void Config::GetSettingValue(void *setting, const char *name, int& num, int def) {
    num = def;
    #ifndef _SUPPORT_APPLE_
    config_setting_t* scalar = (config_setting_t*)setting;
    if (NULL != scalar) {
        config_setting_lookup_int(scalar, name, &num);
    } 
    #endif
    return ;

}

void Config::GetSettingValue(void *setting, const char *name, bool& num, bool def) {
    num = def;
    #ifndef _SUPPORT_APPLE_
    config_setting_t* scalar = (config_setting_t*)setting;
    if (NULL != scalar) {
        int _num;
        if (config_setting_lookup_bool(scalar, name, &_num))
            num = _num;
    } 
    #endif
    return ;

}

void Config::GetSettingString(void *setting, const char *name, char  *str, const char *def) {
    strcpy(str, def);
    #ifndef _SUPPORT_APPLE_
    config_setting_t* scalar = (config_setting_t*)setting;
    if (NULL != scalar) {
        const char *entry;
        if (config_setting_lookup_string(scalar, name, &entry))
            strcpy(str, entry);
    } 
    #endif
    return ;
}
