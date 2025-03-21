#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Util/Image.hpp"
#include "Util/GameObject.hpp"
#include "Util/Renderer.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <unordered_set>
#include <vector>
#include <string>

//--------------------------------------
// 場景背景
//--------------------------------------
class BackgroundImage : public Util::GameObject {
public:
    BackgroundImage()
        : GameObject(std::make_unique<Util::Image>("C:/Users/yello/Shawarma/Resources/Image/background/homePage.png"), 1) {
        m_Transform.scale = glm::vec2(0.65f, 0.65f);
    }
    explicit BackgroundImage(const std::string& imagePath)
        : GameObject(std::make_unique<Util::Image>(imagePath), 1) {
        m_Transform.scale = glm::vec2(1.8f, 1.85f);
    }
};

//--------------------------------------
// 按鈕類別
//--------------------------------------
class StartButton : public Util::GameObject {
public:
    StartButton()
        : GameObject(std::make_unique<Util::Image>("C:/Users/yello/Shawarma/Resources/Image/Object/startBtn1.png"), 5) {
        m_Transform.translation = glm::vec2(-328.0f, 45.0f);
        m_Transform.scale = glm::vec2(0.38f, 0.38f);
    }
    bool IsClicked() {
        glm::vec2 mousePos = Util::Input::GetCursorPosition();
        bool mousePressed = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB);
        float imageWidth = 450.0f * m_Transform.scale.x;
        float imageHeight = 600.0f * m_Transform.scale.y;
        glm::vec2 buttonMin = m_Transform.translation - glm::vec2(imageWidth / 2, imageHeight / 2);
        glm::vec2 buttonMax = m_Transform.translation + glm::vec2(imageWidth / 2, imageHeight / 2);
        return mousePressed &&
               mousePos.x >= buttonMin.x && mousePos.x <= buttonMax.x &&
               mousePos.y >= buttonMin.y && mousePos.y <= buttonMax.y;
    }
};

class ShopButton : public Util::GameObject {
public:
    ShopButton()
        : GameObject(std::make_unique<Util::Image>("C:/Users/yello/Shawarma/Resources/Image/Object/shopBtn.png"), 5) {
        m_Transform.translation = glm::vec2(-42.0f, -87.0f);
        m_Transform.scale = glm::vec2(0.35f, 0.35f);
    }
    bool IsClicked() {
        glm::vec2 mousePos = Util::Input::GetCursorPosition();
        bool mousePressed = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB);
        float imageWidth = 450.0f * m_Transform.scale.x;
        float imageHeight = 320.0f * m_Transform.scale.y;
        glm::vec2 buttonMin = m_Transform.translation - glm::vec2(imageWidth / 2, imageHeight / 2);
        glm::vec2 buttonMax = m_Transform.translation + glm::vec2(imageWidth / 2, imageHeight / 2);
        return mousePressed &&
               mousePos.x >= buttonMin.x && mousePos.x <= buttonMax.x &&
               mousePos.y >= buttonMin.y && mousePos.y <= buttonMax.y;
    }
};

class ReturnButton : public Util::GameObject {
public:
    ReturnButton()
        : GameObject(std::make_unique<Util::Image>("C:/Users/yello/Shawarma/Resources/Image/Object/startBtn.png"), 5) {
        m_Transform.translation = glm::vec2(-400.0f, 300.0f);
        m_Transform.scale = glm::vec2(0.2f, 0.2f);
    }
    bool IsClicked() {
        glm::vec2 mousePos = Util::Input::GetCursorPosition();
        bool mousePressed = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB);
        float imageWidth = 450.0f * m_Transform.scale.x;
        float imageHeight = 320.0f * m_Transform.scale.y;
        glm::vec2 buttonMin = m_Transform.translation - glm::vec2(imageWidth / 2, imageHeight / 2);
        glm::vec2 buttonMax = m_Transform.translation + glm::vec2(imageWidth / 2, imageHeight / 2);
        return mousePressed &&
               mousePos.x >= buttonMin.x && mousePos.x <= buttonMax.x &&
               mousePos.y >= buttonMin.y && mousePos.y <= buttonMax.y;
    }
};

//--------------------------------------
// Topping 類別（用於各種食材）
//--------------------------------------
class Topping : public Util::GameObject {
public:
    // 建構子接受圖片路徑及食材類型識別字串
    Topping(const std::string& imagePath, const std::string& type)
        : Util::GameObject(std::make_unique<Util::Image>(imagePath), 4),
          m_Type(type), m_IsPlaced(false), m_IsDragging(false) {
        m_Transform.translation = glm::vec2(200.0f, -170.0f);
        m_Transform.scale = glm::vec2(0.5f, 0.5f);
    }
    bool IsClicked() {
        glm::vec2 mousePos = Util::Input::GetCursorPosition();
        bool mousePressed = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB);
        float imageWidth = 100.0f * m_Transform.scale.x;
        float imageHeight = 100.0f * m_Transform.scale.y;
        glm::vec2 buttonMin = m_Transform.translation - glm::vec2(imageWidth / 2, imageHeight / 2);
        glm::vec2 buttonMax = m_Transform.translation + glm::vec2(imageWidth / 2, imageHeight / 2);
        return mousePressed &&
               mousePos.x >= buttonMin.x && mousePos.x <= buttonMax.x &&
               mousePos.y >= buttonMin.y && mousePos.y <= buttonMax.y;
    }
    // 點擊後設定為已放置（例如放到料理上）
    void OnClick() {
        if (!m_IsPlaced && IsClicked()) {
            m_IsPlaced = true;
            m_Transform.translation = glm::vec2(200.0f, -170.0f);
        }
    }
    void Update() {
        if (!m_IsPlaced) {
            glm::vec2 mousePos = Util::Input::GetCursorPosition();
            bool mousePressed = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB);
            bool mouseDown = Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB);
            bool mouseReleased = Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB);
            if (mouseDown && IsClicked()) {
                m_IsDragging = true;
                m_Offset = m_Transform.translation - mousePos;
            }
            if (mousePressed && m_IsDragging) {
                m_Transform.translation = mousePos + m_Offset;
            }
            if (mouseReleased) {
                m_IsDragging = false;
            }
        }
    }
    const std::string& GetType() const { return m_Type; }
private:
    std::string m_Type;
    bool m_IsPlaced;
    bool m_IsDragging;
    glm::vec2 m_Offset;
};

//--------------------------------------
// 其他遊戲物件
//--------------------------------------
class Meat : public Util::GameObject {
public:
    Meat()
        : Util::GameObject(std::make_unique<Util::Image>("C:/Users/yello/Shawarma/Resources/Image/Food/meat.png"), 2) {
        m_Transform.translation = glm::vec2(-390.0f, 90.0f);
        m_Transform.scale = glm::vec2(0.34f, 0.34f);
    }
};

class Crust : public Util::GameObject {
public:
    Crust()
        : Util::GameObject(std::make_unique<Util::Image>("C:/Users/yello/Shawarma/Resources/Image/Food/crust.png"), 3),
          m_IsDragging(false) {
        m_Transform.translation = glm::vec2(200.0f, -170.0f);
        m_Transform.scale = glm::vec2(0.2f, 0.2f);
    }
    void Update() {
        glm::vec2 mousePos = Util::Input::GetCursorPosition();
        bool mousePressed = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB);
        bool mouseDown = Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB);
        bool mouseReleased = Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB);
        if (mouseDown && IsClicked()) {
            m_IsDragging = true;
            m_Offset = m_Transform.translation - mousePos;
        }
        if (mousePressed && m_IsDragging) {
            m_Transform.translation = mousePos + m_Offset;
        }
        if (mouseReleased) {
            m_IsDragging = false;
        }
    }
private:
    bool IsClicked() {
        glm::vec2 mousePos = Util::Input::GetCursorPosition();
        bool mousePressed = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB);
        float imageWidth = 700.0f * m_Transform.scale.x;
        float imageHeight = 250.0f * m_Transform.scale.y;
        glm::vec2 buttonMin = m_Transform.translation - glm::vec2(imageWidth / 2, imageHeight / 2);
        glm::vec2 buttonMax = m_Transform.translation + glm::vec2(imageWidth / 2, imageHeight / 2);
        return mousePressed &&
               mousePos.x >= buttonMin.x && mousePos.x <= buttonMax.x &&
               mousePos.y >= buttonMin.y && mousePos.y <= buttonMax.y;
    }
    bool m_IsDragging;
    glm::vec2 m_Offset;
};

class Knife : public Util::GameObject {
public:
    Knife()
        : Util::GameObject(std::make_unique<Util::Image>("C:/Users/yello/Shawarma/Resources/Image/Object/knife_origin.png"), 3),
          m_IsDragging(false) {
        m_Transform.translation = glm::vec2(-480.0f, -160.0f);
        m_Transform.scale = glm::vec2(0.2f, 0.2f);
    }
    void Update() {
        glm::vec2 mousePos = Util::Input::GetCursorPosition();
        bool mousePressed = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB);
        bool mouseDown = Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB);
        bool mouseReleased = Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB);
        if (mouseDown && IsClicked()) {
            m_IsDragging = true;
            m_Offset = m_Transform.translation - mousePos;
        }
        if (mousePressed && m_IsDragging) {
            m_Transform.translation = mousePos + m_Offset;
        }
        if (mouseReleased) {
            m_IsDragging = false;
        }
    }
private:
    bool IsClicked() {
        glm::vec2 mousePos = Util::Input::GetCursorPosition();
        bool mousePressed = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB);
        float imageWidth = 700.0f * m_Transform.scale.x;
        float imageHeight = 250.0f * m_Transform.scale.y;
        glm::vec2 buttonMin = m_Transform.translation - glm::vec2(imageWidth / 2, imageHeight / 2);
        glm::vec2 buttonMax = m_Transform.translation + glm::vec2(imageWidth / 2, imageHeight / 2);
        return mousePressed &&
               mousePos.x >= buttonMin.x && mousePos.x <= buttonMax.x &&
               mousePos.y >= buttonMin.y && mousePos.y <= buttonMax.y;
    }
    bool m_IsDragging;
    glm::vec2 m_Offset;
};

class FrenchFries : public Util::GameObject {
public:
    FrenchFries()
        : Util::GameObject(
              std::make_unique<Util::Image>("C:/Users/yello/Shawarma/Resources/Image/Food/FrenchFries.png"),
              5), m_IsDragging(false) {
        m_Transform.translation = glm::vec2(100.0f, -100.0f); // 初始位置
        m_Transform.scale = glm::vec2(0.5f, 0.5f);             // 縮放大小
    }

    void Update() {
        glm::vec2 mousePos = Util::Input::GetCursorPosition();
        bool mousePressed  = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB);
        bool mouseDown     = Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB);
        bool mouseReleased = Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB);

        // 只有當沒有其他物件正在拖曳時，才開始拖曳
        if (mouseDown && IsClicked() && !s_IsDragging) {
            m_IsDragging = true;
            s_IsDragging = true;
            m_Offset = m_Transform.translation - mousePos;
        }

        if (mousePressed && m_IsDragging) {
            m_Transform.translation = mousePos + m_Offset;
        }

        if (mouseReleased && m_IsDragging) {
            m_IsDragging = false;
            s_IsDragging = false;  // 釋放全域拖曳旗標
        }
    }

private:
    bool IsClicked() {
        glm::vec2 mousePos = Util::Input::GetCursorPosition();
        bool mousePressed = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB);

        float imageWidth = 200.0f * m_Transform.scale.x;
        float imageHeight = 200.0f * m_Transform.scale.y;

        glm::vec2 buttonMin = m_Transform.translation - glm::vec2(imageWidth / 2, imageHeight / 2);
        glm::vec2 buttonMax = m_Transform.translation + glm::vec2(imageWidth / 2, imageHeight / 2);

        return mousePressed &&
               mousePos.x >= buttonMin.x && mousePos.x <= buttonMax.x &&
               mousePos.y >= buttonMin.y && mousePos.y <= buttonMax.y;
    }

    bool m_IsDragging;
    glm::vec2 m_Offset;

    // 靜態變數用來記錄是否已有物件正在被拖曳
    static bool s_IsDragging;
};



//--------------------------------------
// 客人類別（包含吃東西的狀態）
//--------------------------------------
class Customer : public Util::GameObject {
public:
    enum class EatState { NOT_EATEN, READY_TO_EAT, EATEN };
    Customer()
        : Util::GameObject(std::make_unique<Util::Image>("C:/Users/yello/Shawarma/Resources/Image/Customer/customer1.png"), 4),
          m_EatState(EatState::NOT_EATEN) {
        m_Transform.translation = glm::vec2(300.0f, -50.0f);
        m_Transform.scale = glm::vec2(0.5f, 0.5f);
    }
    bool IsNearFrenchFries(const FrenchFries& fries) {
        float distance = glm::distance(m_Transform.translation, fries.GetTransform().translation);
        return distance < 50.0f;
    }
    void SetEatState(EatState state) { m_EatState = state; }
    EatState GetEatState() const { return m_EatState; }
    void RecordFood(const std::string& food) { m_EatenFoods.push_back(food); }
    const std::vector<std::string>& GetEatenFoods() const { return m_EatenFoods; }
private:
    EatState m_EatState;
    std::vector<std::string> m_EatenFoods;
};

//--------------------------------------
// App 類別
//--------------------------------------
class App {
public:
    enum class State { START, UPDATE, END };
    enum class phase { phase1, phase2, phase3 };
    State GetCurrentState() const { return m_CurrentState; }
    void Start();
    void Update();
    void End();
private:
    void ValidTask();
private:
    State m_CurrentState = State::START;
    phase m_CurrentPhase = phase::phase1;
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<Util::Renderer> m_Renderer;
    std::shared_ptr<StartButton> m_StartButton;
    std::shared_ptr<ShopButton> m_ShopButton;
    std::shared_ptr<ReturnButton> m_ReturnButton;
    std::shared_ptr<Meat> m_Meat;
    std::shared_ptr<Crust> m_Crust;
    std::shared_ptr<Knife> m_Knife;
    // 食材以 Topping 物件表示（使用不同 type 參數）
    std::shared_ptr<Topping> m_Fries;
    std::shared_ptr<Topping> m_Sauce;
    std::shared_ptr<Topping> m_Pickle;
    std::shared_ptr<Topping> m_ShavedMeat;
    // 互動用的 FrenchFries 物件（例如用來檢查客人是否靠近）
    std::vector<std::shared_ptr<FrenchFries>> m_FrenchFriesList;
    std::vector<std::shared_ptr<Customer>> m_Customers;
    std::vector<std::shared_ptr<Topping>> toppings; // 其他新增的配料

};

#endif
