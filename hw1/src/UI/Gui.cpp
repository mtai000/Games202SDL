#include "Gui.h"
#include "Core/Renderer.h"
#include "Core/Game.h"
#include "Component/LightComponent.h"
#include "Core/Actor.h"
#include <vector>

CGUI::CGUI(Renderer* _r, SDL_Window* window, SDL_GLContext& gl_context)
    : mRenderer(_r)
    , mClearColor(ImVec4(0.25f,0.35f,0.40f,1.00f))
    , mBitShadow(1)
    , mGamma(1.0f/2.2f)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window,gl_context);
    ImGui_ImplOpenGL3_Init("#version 430");
}
CGUI::~CGUI()
{
    Quit();
}

void CGUI::NewFrame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    ImGui::Text((std::string("FPS: ") + std::to_string((int)(1000.0f / (float)(mRenderer->GetGame()->GetTicks())))).c_str());

    if(ImGui::RadioButton("default",mBitShadow & 0x1)){
        mBitShadow = 0x1;
    }
    if(ImGui::RadioButton("PCF",mBitShadow & 0x2)){
       mBitShadow = 0x2; 
    }
    if(ImGui::RadioButton("PCSS",mBitShadow & 0x4)){
        mBitShadow = 0x4;
    }

    ImGui::SliderFloat("Gamma value:",&mGamma,0.1f,0.7f);
    std::vector<LightComponent*> lights = mRenderer->GetLightComps();
    mLightCheck.resize(lights.size());
    for(int i = 0 ; i < lights.size(); i++){
        ImGui::PushID(i);
        // glm::vec3 pos = lights[i]->GetOwner()->GetPosition();
        // float _pos[3]  = {pos[0],pos[1],pos[2]};
        // ImGui::Checkbox("Invoke this light", reinterpret_cast<bool*>(&mLightCheck[i]));
        ImGui::Checkbox("use", &(lights[i]->IsValid()));
        ImGui::SameLine();
        ImGui::InputFloat3("position",reinterpret_cast<float*>(&lights[i]->GetOwner()->GetPosition()));
        // ImGui::InputFloat3("Position",_pos);
        // ImGui::InputFloat3("Intensity",reinterpret_cast<float*>(&lights[i]->GetIntensity()));
        ImGui::PopID();
    }
}
void CGUI::ProcessEvent(const SDL_Event& event){
    ImGui_ImplSDL2_ProcessEvent(&event);
}

void CGUI::Draw(){
    ImGui::End;
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void CGUI::Quit(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}




