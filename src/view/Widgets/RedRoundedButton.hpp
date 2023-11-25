#pragma once

namespace View::Widget
{

class RedRoundedButton
{
public:
    RedRoundedButton(const char *label, ImVec2 size = ImVec2(200.0f, 70.0f))
        : label(label), size(size)
    {
    }

    void Render()
    {
        // Calculate the position to center the button
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 buttonPos =
            ImVec2((windowSize.x - size.x) * 0.5f, (size.y) * 0.5f);

        // Set up the bigger button with curved corners and red font
        ImGui::PushStyleVar(
            ImGuiStyleVar_FrameRounding,
            4.0f); // Adjust the rounding value for curved corners
        ImGui::PushStyleColor(
            ImGuiCol_Button,
            ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // White color for button
        ImGui::PushStyleColor(
            ImGuiCol_ButtonHovered,
            ImVec4(0.9f, 0.9f, 0.9f, 1.0f)); // Slightly darker on hover
        ImGui::PushStyleColor(
            ImGuiCol_ButtonActive,
            ImVec4(0.8f, 0.8f, 0.8f, 1.0f)); // Darker when pressed
        ImGui::PushStyleColor(
            ImGuiCol_Text,
            ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red color for font

        // Set the cursor position to center the button
        ImGui::SetCursorPos(buttonPos);

        if (ImGui::Button("START", size))
        {
            // Button action when clicked
        }

        // Pop the style variables and colors
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(4);
    }

private:
    const char *label;
    ImVec2 size;
};

} // namespace View::Widget
