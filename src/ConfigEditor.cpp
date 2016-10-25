#include "ConfigEditor.h"

ConfigEditor::ConfigEditor(DriveStation* DriveStation):
    m_DriveStation(DriveStation)
{
}

ConfigEditor::~ConfigEditor()
{
}

/*
 * Sends requested variable's value to drive station.
 */
void ConfigEditor::getConfig()
{
    std::string keyName = m_DriveStation->getStringInput(10);

    int pos = -1;
    for(int i=0;i<ConfigVariables::numberOfVars;i++)
    {
        if(keyName == ConfigVariables::variables[i])
        {
            pos = i;
            break;
        }
    }

    if(pos == -1)
    {
        std::cout << "Key entered was not a valid variable" << std::endl;
        return;
    }

    std::string type = ConfigVariables::types[pos];

    if(type == "int")
    {
        std::stringstream ss;
        ss << Preferences::GetInstance()->GetInt(keyName, 0);
        m_DriveStation->setString(11, ss.str());
    } else if(type == "float")
    {
        std::stringstream ss;
        ss << Preferences::GetInstance()->GetFloat(keyName, 0);
        m_DriveStation->setString(11, ss.str());
    } else if(type == "double")
    {
        std::stringstream ss;
        ss << Preferences::GetInstance()->GetDouble(keyName, 0);
        m_DriveStation->setString(11, ss.str());
    } else
    {
        m_DriveStation->setString(11, Preferences::GetInstance()->GetString(keyName, 0));
    }
}

/*
 * Gets the value of the specified key.
 */
int ConfigEditor::getInt(std::string key, int defaultValue)
{
    return Preferences::GetInstance()->GetInt(key, defaultValue);
}

float ConfigEditor::getFloat(std::string key, float defaultValue)
{
    return Preferences::GetInstance()->GetFloat(key, defaultValue);
}

double ConfigEditor::getDouble(std::string key, double defaultValue)
{
    return Preferences::GetInstance()->GetDouble(key, defaultValue);
}

std::string ConfigEditor::getString(std::string key, std::string defaultValue)
{
    return Preferences::GetInstance()->GetString(key, defaultValue);
}

/*
 * Updates variable as dictated by drive station.
 */
void ConfigEditor::saveConfig()
{
    std::string keyName = m_DriveStation->getStringInput(10);
    std::string newValue = m_DriveStation->getStringInput(12);

    int pos = -1;
    for(int i=0;i<ConfigVariables::numberOfVars;i++)
    {
        if(keyName == ConfigVariables::variables[i])
        {
            pos = i;
            break;
        }
    }

    if(pos == -1)
    {
        std::cout << "Key entered was not a valid variable" << std::endl;
        return;
    }

    std::string type = ConfigVariables::types[pos];

    if(!isType(newValue,type))
    {
	std::cout << "" << std::endl;
        return;
    }

    if(type == "int")
    {
        Preferences::GetInstance()->PutInt(keyName, std::stoi(newValue));
    } else if(type == "float")
    {
        Preferences::GetInstance()->PutFloat(keyName, std::stof(newValue));
    } else if(type == "double")
    {
        Preferences::GetInstance()->PutDouble(keyName, std::stod(newValue));
    } else
    {
        Preferences::GetInstance()->PutString(keyName, newValue);
    }
}

/*
 * Checks if a string is the specified type of number.
 */
bool ConfigEditor::isType(std::string str, std::string type)
{
    if(type == "int")
        try
            std::stoi(str);
        catch(std::invalid_argument& e)
            return false;
    else if(type == "float")
        try
            std::stof(str);
        catch(std::invalid_argument& e)
            return false;
    else if(type == "double")
        try
            std::stod(str);
        catch(std::invalid_argument& e)
            return false;
    else
	return true;
}

/*
 * Outputs all of the keys to standard output
 * and SmartDashboard.
 */
void ConfigEditor::showAllKeys()
{
    std::string final = "";
    for(int i = 0; i < ConfigVariables::numberOfVars; i++)
    {
        final += ConfigVariables::variables[i]+"     "+ConfigVariables::types[i]+"\n";
    }
    std::cout << final << std::endl;
    SmartDashboard::PutString("Keys",final);
}

/*
 * Updates input from variable editor. Should be
 * executed every cycle.
 */
void ConfigEditor::update()
{
    for (int i = 0; i < 6; i++)
    {
        if (m_DriveStation->getButtonInput(i))
        {
            m_DriveStation->setButton(i, false);
            std::cout << "Button " << i << " was pressed" << std::endl;

            if(i==5)
                saveConfig();
            if(i==4)
                getConfig();
        }
    }
}

void ConfigEditor::putProgDouble(std::string key, double value)
{
    if(key.find("prog") == 0)
    {
        Preferences::GetInstance()->PutDouble(key, value);
    }
}
