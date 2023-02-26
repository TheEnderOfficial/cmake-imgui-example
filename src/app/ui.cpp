//
// Created by enderoff on 26.02.23.
//

#include "imgui.h"
#include "../../inc/app/ui.h"
#include "../../inc/app/config.h"
#include "../../inc/services/RandomService.h"
#include "../../inc/services/ApiService.h"


namespace MyApp {
    struct {
        char user_name[64] = "";
        char error[128] = "";
        int user_dick;
        bool is_user_calculated = false;
        char status[64];
        char version[64];
        int statusHttpCode;
        bool isStatusLoaded = false;
    } state;

    void renderUI() {
        if (!state.isStatusLoaded) {
            auto r = ApiService::ApiService::get(MyApp::config.GET_STATUS_URL);
            strcpy(state.status, r.jsonData["status"].asCString());
            strcpy(state.version, r.jsonData["version"].asCString());
            state.statusHttpCode = r.httpCode;
            printf("Loaded data, status: %s, version: %s", state.status, state.version);

            Json::Value x;
            x["test"] = "zalupa chlena";

            auto r2 = ApiService::ApiService::post("http://localhost:3000/test", x);
            printf("%s", r2.jsonData.toStyledString().c_str());

            state.isStatusLoaded = true;
        }

        ImGui::Begin("dickometor", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);

        ImGui::SetWindowSize(ImVec2((float)MyApp::config.width, (float)MyApp::config.height));
        ImGui::SetWindowPos(ImVec2(0, 0));

        if (state.statusHttpCode == -100) {
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255,0,0,255));
            ImGui::Text("Error: %s", state.status);
            ImGui::PopStyleColor(1);
            ImGui::End();
            return;
        }

        if (strcmp(MyApp::config.version, state.version) != 0) {
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255,255,0,255));
            ImGui::Text("Warning: version of client and server not equal, please update, (client %s, server %s)", MyApp::config.version, state.version);
            ImGui::PopStyleColor(1);
            ImGui::Separator();
        }

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
                    state.user_dick = RandomService::RandomService::randInt(2, 20);
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