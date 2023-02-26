//
// Created by enderoff on 26.02.23.
//

#include "imgui.h"
#include "ui.h"
#include "config.h"
#include "../utils/utils.h"


namespace MyApp {
    struct {
        char user_name[64] = "";
        char error[128] = "";
        int user_dick;
        bool is_user_calculated = false;
    } state;

    void renderUI() {
        ImGui::Begin("dickometor", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);

        ImGui::SetWindowSize(ImVec2((float)MyApp::config.width, (float)MyApp::config.height));
        ImGui::SetWindowPos(ImVec2(0, 0));

        if (strlen(state.error) > 0) {
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255,0,0,255));
            ImGui::Text("Error: %s", state.error);
            ImGui::PopStyleColor(1);
            ImGui::Separator();
        }

        ImGui::Text("Enter your name!");
        ImGui::InputText("Your name", state.user_name, 64);

        ImGui::Separator();

        if (state.is_user_calculated) {
            ImGui::Text("%s dick size: %d cm", state.user_name, state.user_dick);
            if (ImGui::Button("Reset")) {
                state.is_user_calculated = false;
            }
        }
        else {
            if (ImGui::Button("Calculate dick size")) {
                if (strlen(state.user_name) <= 0) {
                    strcpy(state.error, "Please enter name");
                }
                else {
                    state.user_dick = AppUtils::randRange(5, 20);
                    state.is_user_calculated = true;
                }
            }

            if (strlen(state.error) > 0) {
                if (strlen(state.user_name) > 0) {
                    strcpy(state.error, "");
                }
            }
        }



        ImGui::End();
    }
}