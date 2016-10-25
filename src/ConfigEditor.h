#ifndef SRC_CONFIGEDITOR_H_
#define SRC_CONFIGEDITOR_H_

#include "DriveStation.h"

class ConfigEditor
{
public:
    ConfigEditor(DriveStation* DriveStation);
    ~ConfigEditor(void);
    void update(void);

    void saveConfig(void);
    void getConfig(void);
    bool isType(std::string str, std::string type);
    void showAllKeys(void);

    int getInt(std::string key, int defaultValue = 0);
    float getFloat(std::string key, float defaultValue = 0.0f);
    double getDouble(std::string key, double defaultValue = 0.0);
    std::string getString(std::string key, std::string defaultValue = "");

    void putProgDouble(std::string key, double value);
private:
    DriveStation* m_DriveStation;
};

#endif /* SRC_CONFIGEDITOR_H_ */
