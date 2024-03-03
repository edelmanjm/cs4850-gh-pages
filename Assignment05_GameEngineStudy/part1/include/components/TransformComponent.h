#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <string>

#include <components/Component.h>

class TransformComponent : public Component {
public:
    TransformComponent();

    ~TransformComponent() override;

    ComponentType GetType() override;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

    void SetW(float w);
    void SetH(float h);
    void SetWH(float w, float h);

    [[nodiscard]] float GetW() const;
    [[nodiscard]] float GetH() const;

    void SetX(float x);
    void SetY(float y);
    void SetXY(float x, float y);

    [[nodiscard]] float GetX() const;
    [[nodiscard]] float GetY() const;

    [[nodiscard]] SDL_FRect GetRectangle() const;

private:
    SDL_FRect mRectangle{20.0f, 20.0f, 32.0f, 32.0f};
};
