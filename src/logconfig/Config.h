#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <string>
#ifndef _SUPPORT_APPLE_
typedef struct config_t config_t;
#endif

class Config{
public:
    Config();
    ~Config();
    int load(const char *filename);

    void GetValue(const char *name, float& num, float def);
    void GetValue(const char *name, int& num, int def);
    void GetValue(const char *name, bool& num, bool def);
    void GetString(const char *name, char  *str, const char *def);

    int GetLength(const char* name, int& length);
    int GetSettingIntElem(const char* name, int& value, int index, int def);
    int GetSettingStringElem(const char* name, std::string& value, int index, const std::string& def);

    void *GetSetting(const char* name);
    void *GetSetting(void *setting, int index);
    void *GetSetting(void *setting, const char *name);
    int  GetSettingLength(void *setting, int& length);
    int  GetSettingIntElem(void *setting, int& value, int index, int def);
    int  GetSettingStringElem(void *setting, std::string& value, int index, const std::string& def);
    void GetSettingValue(void *setting, const char *name, float& num, float def);
    void GetSettingValue(void *setting, const char *name, int& num, int def);
    void GetSettingValue(void *setting, const char *name, bool& num, bool def);
    void GetSettingString(void *setting, const char *name, char  *str, const char *def);

    char *GetFilename() const {
        return m_filename;
    }
    char *GetFilepath();
public:
    char *m_filename;
    char *m_filepath;
private:
#ifndef _SUPPORT_APPLE_
    config_t *cfg;
#endif
};


#endif

