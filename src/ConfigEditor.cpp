#include "ConfigEditor.h"

#include <stringstream>
#include <WPILib.h>

using ConfigEditor::ConfigVariable;

ConfigEditor::ConfigEditor()
{
    m_preferences = Preferences::GetInstance(); // Alias
}

/*
 * Static variable declarations
 */
ConfigVariable ConfigEditor::m_keys =
{{"Example1","int"},
 {"Example2","float"},
 {"Example3","double"},
 {"Example4","string"}};

int ConfigEditor::m_keysLength = sizeof(m_keys) / sizeof(ConfigVariable);

ConfigEditor::~ConfigEditor()
{
}

/*
 * Sends requested variable's value to drive station.
 */
void ConfigEditor::getConfig()
{
    std::string keyName = SmartDashboard::GetString("Key Name", "");

    int pos = -1;
    for(int i = 0; i < m_keysLength; i++)
    {
        if(keyName == m_keys[i])
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

    ConfigType type = m_keys[pos].type;
    std::stringstream convert;

    switch (type)
    {
    case CONFIG_INT:
	convert << m_preferences->GetInt(keyName, 0);
	break;
    case CONFIG_FLOAT:
	convert << m_preferences->GetFloat(keyName, 0);
	break;
    case CONFIG_DOUBLE:
	convert << m_preferences->GetDouble(keyName, 0);
	break;
    case CONFIG_STRING:
	convert << m_preferences->GetString(keyName, 0);
	break;
    }
    SmartDashboard::PutString("Key Value", convert.str());
}

/*
 * Updates variable as dictated by drive station.
 */
void ConfigEditor::saveConfig()
{
    std::string keyName = SmartDashboard::GetString("Key Name", "");
    std::string newValue = SmartDashboard::GetString("New Value", "");

    int pos = -1;
    for(int i = 0; i < m_keysLength; i++)
    {
        if(keyName == m_keys[i])
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

    ConfigType type = m_keys[pos].type;
    std::stringstream convert(newValue);

    try
    {
	union
	{
	    int i;
	    float f;
	    double d;
	};

        switch (type)
	{
	case CONFIG_INT:
	    convert >> i;
	    m_preferences->PutInt(keyName, i);
	    break;
	case CONFIG_FLOAT:
	    convert >> f;
	    m_preferences->PutFloat(keyName, f);
	    break;
	case CONFIG_DOUBLE:
	    convert >> d;
	    m_preferences->PutDouble(keyName, d);
	    break;
	case CONFIG_STRING:
	    m_preferences->PutInt(keyName, newValue);
	    break;
	}
    } catch (...)
    {
	std::cout << "Invalid value" << std::endl;
	return;
    }
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
        final += m_keys[i].name+"\t"+m_keys[i].type+"\n";
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

            if(i == 5)
                saveConfig();
            else if(i == 4)
                getConfig();
        }
    }
}

/*
 * Gets the value of the specified key.
 */
int ConfigEditor::getInt(std::string key, int defaultValue)
{
    return m_preferences->GetInt(key, defaultValue);
}

float ConfigEditor::getFloat(std::string key, float defaultValue)
{
    return m_preferences->GetFloat(key, defaultValue);
}

double ConfigEditor::getDouble(std::string key, double defaultValue)
{
    return m_preferences->GetDouble(key, defaultValue);
}

std::string ConfigEditor::getString(std::string key, std::string defaultValue)
{
    return m_preferences->GetString(key, defaultValue);
}

/*
 * Saves a double value to the key.
 */
void ConfigEditor::putProgDouble(std::string key, double value)
{
    if(key.find("prog") == 0)
        m_preferences->PutDouble(key, value);
}
