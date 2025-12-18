#include <iostream>
#include <string>
using namespace std;

/* =========================
   UI Component Interfaces
   ========================= */

class Button {
public:
    virtual void render() = 0;
};

class TextField {
public:
    virtual void render() = 0;
};

class Dialog {
public:
    virtual void show() = 0;
};

/* =========================
   Web Components
   ========================= */

class WebButton : public Button {
public:
    void render() override {
        cout << "Rendering Web Button\n";
    }
};

class WebTextField : public TextField {
public:
    void render() override {
        cout << "Rendering Web TextField\n";
    }
};

class WebDialog : public Dialog {
public:
    void show() override {
        cout << "Showing Web Dialog\n";
    }
};

/* =========================
   Android Components
   ========================= */

class AndroidButton : public Button {
public:
    void render() override {
        cout << "Rendering Android Button\n";
    }
};

class AndroidTextField : public TextField {
public:
    void render() override {
        cout << "Rendering Android TextField\n";
    }
};

class AndroidDialog : public Dialog {
public:
    void show() override {
        cout << "Showing Android Dialog\n";
    }
};

/* =========================
   Desktop Components
   ========================= */

class DesktopButton : public Button {
public:
    void render() override {
        cout << "Rendering Desktop Button\n";
    }
};

class DesktopTextField : public TextField {
public:
    void render() override {
        cout << "Rendering Desktop TextField\n";
    }
};

class DesktopDialog : public Dialog {
public:
    void show() override {
        cout << "Showing Desktop Dialog\n";
    }
};

/* =========================
   Abstract Factory
   ========================= */

class GUIFactory {
public:
    virtual Button* createButton() = 0;
    virtual TextField* createTextField() = 0;
    virtual Dialog* createDialog() = 0;
};

/* =========================
   Concrete Factories
   ========================= */

class WebFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new WebButton();
    }
    TextField* createTextField() override {
        return new WebTextField();
    }
    Dialog* createDialog() override {
        return new WebDialog();
    }
};

class AndroidFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new AndroidButton();
    }
    TextField* createTextField() override {
        return new AndroidTextField();
    }
    Dialog* createDialog() override {
        return new AndroidDialog();
    }
};

class DesktopFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new DesktopButton();
    }
    TextField* createTextField() override {
        return new DesktopTextField();
    }
    Dialog* createDialog() override {
        return new DesktopDialog();
    }
};

/* =========================
   Factory Provider
   ========================= */

class FactoryProvider {
public:
    static GUIFactory* getFactory(const string& platform) {
        if (platform == "WEB") return new WebFactory();
        if (platform == "ANDROID") return new AndroidFactory();
        if (platform == "DESKTOP") return new DesktopFactory();
        return nullptr;
    }
};

/* =========================
   Client Code
   ========================= */

int main() {
    // Change platform here only
    GUIFactory* factory = FactoryProvider::getFactory("ANDROID");

    Button* button = factory->createButton();
    TextField* textField = factory->createTextField();
    Dialog* dialog = factory->createDialog();

    button->render();
    textField->render();
    dialog->show();

    return 0;
}
