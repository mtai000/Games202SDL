#pragma once
#include "head.h"

class CGUI{
public:
    CGUI(class Renderer * _r, SDL_Window * _w, SDL_GLContext & gl_context);
    ~CGUI();
    void NewFrame();
    void ProcessEvent(const SDL_Event &event);
    void Quit();
    void Draw();
    int GetShadowType() const {return mBitShadow;}
    float GetGamma() const {return mGamma;}
private:
    class Renderer* mRenderer;
    ImVec4 mClearColor;
    int mBitShadow;
    int mLightIndex;
    float mGamma;
    std::vector<bool> mLightCheck;
};
