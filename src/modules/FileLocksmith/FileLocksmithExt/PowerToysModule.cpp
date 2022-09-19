#include "pch.h"

#include "../../interface/powertoy_module_interface.h"
#include "../../../common/SettingsAPI/settings_objects.h"
#include "../../../common/logger/logger.h"

#include "Constants.h"

class FileLocksmithModule : public PowertoyModuleIface
{
public:
    virtual const wchar_t* get_name() override
    {
        return constants::localizable::PowerToyName;
    }

    virtual const wchar_t* get_key() override
    {
        return constants::nonlocalizable::PowerToyKey;
    }

    // Return JSON with the configuration options.
    // These are the settings shown on the settings page along with their current values.
    virtual bool get_config(_Out_ PWSTR buffer, _Out_ int* buffer_size) override
    {
        HINSTANCE hinstance = reinterpret_cast<HINSTANCE>(&__ImageBase);

        // Create a Settings object.
        PowerToysSettings::Settings settings(hinstance, get_name());
        settings.set_description(L"TODO: GET_RESOURCE_STRING(IDS_SETTINGS_DESCRIPTION");
        settings.set_icon_key(L"TODO: pt-file-locksmith");

        // Link to the GitHub PowerRename sub-page
        settings.set_overview_link(L"TODO: GET_RESOURCE_STRING(IDS_OVERVIEW_LINK)");

        return settings.serialize_to_buffer(buffer, buffer_size);
    }

    // Passes JSON with the configuration settings for the powertoy.
    // This is called when the user hits Save on the settings page.
    virtual void set_config(PCWSTR config) override
    {
        try
        {
            // Parse the input JSON string.
            PowerToysSettings::PowerToyValues values =
                PowerToysSettings::PowerToyValues::from_json_string(config, get_key());

            // TODO: Trace
            // Trace::SettingsChanged();
        }
        catch (std::exception& e)
        {
            Logger::error("Configuration parsing failed: {}", std::string{ e.what() });
        }
    }

    virtual void enable() override
    {
        Logger::info(L"File Locksmith enabled");
        m_enabled = true;
        // TODO
        // save_settings();
    }

    virtual void disable() override
    {
        Logger::info(L"File Locksmith disabled");
        m_enabled = false;
        // TODO
        // save_settings();
    }

    virtual bool is_enabled() override
    {
        return m_enabled;
    }

    virtual void destroy() override
    {
        delete this;
    }

    // This should be enough to create an instance

private:
    bool m_enabled;
};
