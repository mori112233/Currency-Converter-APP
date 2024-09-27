#include "DrawThread.h"
#include "GuiMain.h"
#include "../../shared/ImGuiSrc/imgui.h"
#include <cstring>  // For _strnicmp
#include <unordered_set>  // For unordered_set
#include <unordered_map>  // For unordered_map

/**
 * @brief Function to draw the application window.
 * @param common_ptr Pointer to the common objects shared between threads.
 */
void DrawAppWindow(void* common_ptr)
{
    auto common = (CommonObjects*)common_ptr;
    static char to_currency[10] = "";  // Buffer to hold user input
    static std::string selected_from_currency = "USD";  // Default to USD
    static bool show_currency_list = false;  // Control variable to show/hide currency list
    static std::vector<std::string> unique_currencies;  // List to store unique currencies
    static std::unordered_map<std::string, double> conversion_map;  // Map to store conversion rates from USD
    static std::unordered_map<std::string, double> amount_map; // Map to store user-entered amounts

    // Update unique_currencies list and conversion_map if it's empty
    if (unique_currencies.empty() && common->data_ready)
    {
        std::unordered_set<std::string> currency_set;
        for (const auto& conversion : common->conversions)
        {
            currency_set.insert(conversion.to_currency);
            conversion_map[conversion.to_currency] = conversion.conversion_rate;
        }
        unique_currencies.assign(currency_set.begin(), currency_set.end());
    }

    // Change the background color of text boxes and add a small lighter gray frame
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));  // Dark gray background
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));  // Lighter gray border
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);  // Small border size

    // Change the background color of the header and buttons
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));  // Dark gray background for the header
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));  // Dark gray background for buttons
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));  // Slightly lighter gray when hovered
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));  // Slightly lighter gray when active

    ImGui::Begin("Connected!");
    ImGui::Text("Currency Conversion");

    // Add text box for "To currency"
    ImGui::InputText("To Currency", to_currency, sizeof(to_currency));

    // Display selected "From Currency"
    ImGui::Text("From Currency: ");
    ImGui::SameLine();
    if (ImGui::Button(selected_from_currency.c_str()))
    {
        show_currency_list = !show_currency_list;
    }

    // Show currency list when button is clicked
    if (show_currency_list)
    {
        ImGui::Begin("Select From Currency", &show_currency_list);
        for (const auto& currency : unique_currencies)
        {
            if (ImGui::Selectable(currency.c_str()))
            {
                selected_from_currency = currency;
                show_currency_list = false;  // Close the list after selection
            }
        }
        ImGui::End();
    }

    // Add the "Clear" button at the same level as the "From Currency" button but aligned to the right
    ImGui::SameLine(ImGui::GetWindowWidth() - 70);  // Adjust the value to move the button to the right
    if (ImGui::Button("Clear"))
    {
        for (auto& amount : amount_map)
        {
            amount.second = 0.0;  // Reset all amounts to zero
        }
    }

    if (common->data_ready)
    {
        std::lock_guard<std::mutex> lock(common->mutex);

        if (ImGui::BeginTable("Conversions", 4))  // Add a new column for the text box
        {
            ImGui::TableSetupColumn("From Currency");
            ImGui::TableSetupColumn("To Currency");
            ImGui::TableSetupColumn("Conversion Rate");
            ImGui::TableSetupColumn("Converted Amount");
            ImGui::TableHeadersRow();

            for (const auto& currency : unique_currencies)
            {
                if (currency != selected_from_currency &&
                    (to_currency[0] == '\0' || _strnicmp(currency.c_str(), to_currency, strlen(to_currency)) == 0))
                {
                    double conversion_rate = conversion_map[currency] / conversion_map[selected_from_currency];
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text(selected_from_currency.c_str());
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text(currency.c_str());
                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text("%.4f", conversion_rate);

                    ImGui::TableSetColumnIndex(3);
                    std::string amount_key = selected_from_currency + "_" + currency;
                    double& amount = amount_map[amount_key];
                    char amount_buf[64] = ""; // Buffer for the amount input
                    if (amount != 0.0) // Only display the amount if it's not zero
                    {
                        snprintf(amount_buf, sizeof(amount_buf), "%.2f", amount);
                    }
                    ImGui::PushItemWidth(100); // Set the width of the input text box
                    if (ImGui::InputText(("##amount_" + amount_key).c_str(), amount_buf, sizeof(amount_buf), ImGuiInputTextFlags_CharsDecimal))
                    {
                        // Update amount only if user enters a valid number
                        amount = atof(amount_buf);
                    }
                    ImGui::PopItemWidth();
                    ImGui::SameLine();
                    if (amount != 0.0) // Only display the conversion if the amount is not zero
                    {
                        ImGui::Text("%.2f %s is %.2f %s", amount, selected_from_currency.c_str(), amount * conversion_rate, currency.c_str());
                    }
                }
            }
            ImGui::EndTable();
        }
    }

    ImGui::End();
    ImGui::PopStyleColor(6);  // Revert the background color and border color changes
    ImGui::PopStyleVar();  // Revert the border size change
}

/**
 * @brief Operator function to run the draw thread.
 * @param common Reference to the common objects shared between threads.
 */
void DrawThread::operator()(CommonObjects& common)
{
    // Comment out or remove the demo window calls if present
    // ImGui::ShowDemoWindow();
    // ImGui::Text("Hello, world!");

    GuiMain(DrawAppWindow, &common);
    common.exit_flag = true;
}
