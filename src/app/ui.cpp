//
// Created by enderoff on 26.02.23.
//

#include "imgui.h"
#include "../../inc/app/ui.h"
#include "../../inc/app/config.h"
#include "../../inc/services/RandomService.h"
#include "../../inc/services/ApiService.h"


namespace MyApp {
    struct TopEntry {
        int id;
        char user_name[64];
        int size;
        bool valid = false;
    };

    struct {
        char user_name[64] = "";
        char error[128] = "";
        int user_dick{};
        bool is_user_calculated = false;
        char status[64]{};
        char version[64]{};
        int statusHttpCode{};
        bool isStatusLoaded = false;
        TopEntry top[100]{};

        int isPublished = 0;
    } state;

    void renderUI() {
        if (!state.isStatusLoaded) {
            auto r = ApiService::ApiService::get(MyApp::config.GET_STATUS_URL);
            strcpy(state.status, r.jsonData["status"].asCString());
            strcpy(state.version, r.jsonData["version"].asCString());
            state.statusHttpCode = r.httpCode;
            printf("Loaded data, status: %s, version: %s", state.status, state.version);

            // top
            auto topR = ApiService::ApiService::get(MyApp::config.GET_TOP_URL);
            std::vector<TopEntry> v = {};
            for (Json::Value::ArrayIndex i = 0; i != topR.jsonData["top"].size(); i++)
            {
                TopEntry te = {};
                strcpy(te.user_name, topR.jsonData["top"][i]["name"].asCString());
                te.size = topR.jsonData["top"][i]["length"].asInt();
                te.id = topR.jsonData["top"][i]["id"].asInt();
                te.valid = true;
                v.push_back(te);
            }
            std::copy(v.begin(), v.end(), state.top);

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


        if (!state.is_user_calculated) {
            ImGui::Text("Enter your name!");
            ImGui::InputText("Your name", state.user_name, 64);

            ImGui::Separator();
        }

        if (state.is_user_calculated) {
            ImGui::Text("%s dick size: %d cm", state.user_name, state.user_dick);
            if (state.isPublished == 0 && ImGui::Button("Publish record")) {
                Json::Value val;
                val["name"] = state.user_name;
                val["length"] = state.user_dick;
                auto pR = ApiService::ApiService::post(MyApp::config.POST_RESULT_URL, val);
                state.isPublished = true;
                state.isStatusLoaded = false; // reloads top and status
                state.isPublished = -1;
            }
            if (state.isPublished == -1) {
                ImGui::Text("Your record is published.");
                ImGui::SameLine();
                if (ImGui::Button("Close")) {
                    state.isPublished = 1;
                }
            }
            if (ImGui::Button("Reset")) {
                state.is_user_calculated = false;
                state.isPublished = 0;
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

        // top
        ImGui::Separator();
        ImGui::Text("Top 5");
        for (int i = 0; i <= 5; i++) {
            auto te = state.top[i];

            if (!te.valid) continue;
            ImGui::Text("%d: %s - %d cm", i + 1, te.user_name, te.size);
        }

        ImGui::End();
    }
}