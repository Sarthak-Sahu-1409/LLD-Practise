#include <iostream>
#include <string>
#include <vector>
using namespace std;

/* =========================
   Metrics Client Interface
   ========================= */

class MetricsClient {
public:
    virtual void trackEvent(const string& name, const string& data) = 0;
};

/* =========================
   Simulated Third-Party SDKs
   ========================= */

class GoogleAnalyticsSdk {
public:
    void log(const string& event, const string& payload) {
        cout << "[GA SDK] " << event << " -> " << payload << "\n";
    }
};

class MixpanelSdk {
public:
    void send(const string& event, const string& payload) {
        cout << "[Mixpanel SDK] " << event << " -> " << payload << "\n";
    }
};

class InternalAnalyticsSdk {
public:
    void push(const string& event, const string& payload) {
        cout << "[Internal SDK] " << event << " -> " << payload << "\n";
    }
};

/* =========================
   Adapters (Adapter Pattern)
   ========================= */

class GoogleAnalyticsAdapter : public MetricsClient {
    GoogleAnalyticsSdk sdk;
public:
    void trackEvent(const string& name, const string& data) override {
        sdk.log(name, data);
    }
};

class MixpanelAdapter : public MetricsClient {
    MixpanelSdk sdk;
public:
    void trackEvent(const string& name, const string& data) override {
        sdk.send(name, data);
    }
};

class InternalAnalyticsAdapter : public MetricsClient {
    InternalAnalyticsSdk sdk;
public:
    void trackEvent(const string& name, const string& data) override {
        sdk.push(name, data);
    }
};

/* =========================
   Decorator Base Class
   ========================= */

class MetricsDecorator : public MetricsClient {
protected:
    MetricsClient* wrappee;
public:
    MetricsDecorator(MetricsClient* c) : wrappee(c) {}
};

/* =========================
   Concrete Decorators
   ========================= */

class LoggingMetricsDecorator : public MetricsDecorator {
public:
    LoggingMetricsDecorator(MetricsClient* c) : MetricsDecorator(c) {}

    void trackEvent(const string& name, const string& data) override {
        cout << "[LOG] Tracking event: " << name << "\n";
        wrappee->trackEvent(name, data);
    }
};

class BufferedMetricsDecorator : public MetricsDecorator {
public:
    BufferedMetricsDecorator(MetricsClient* c) : MetricsDecorator(c) {}

    void trackEvent(const string& name, const string& data) override {
        cout << "[BUFFER] Buffering event\n";
        wrappee->trackEvent(name, data);
    }
};

/* =========================
   Strategy Interface
   ========================= */

class MetricsStrategy {
public:
    virtual void sendEvent(const string& name, const string& data) = 0;
};

/* =========================
   Concrete Strategies
   ========================= */

class SingleProviderStrategy : public MetricsStrategy {
    MetricsClient* client;
public:
    SingleProviderStrategy(MetricsClient* c) : client(c) {}

    void sendEvent(const string& name, const string& data) override {
        client->trackEvent(name, data);
    }
};

class MultiProviderStrategy : public MetricsStrategy {
    vector<MetricsClient*> clients;
public:
    MultiProviderStrategy(const vector<MetricsClient*>& c) : clients(c) {}

    void sendEvent(const string& name, const string& data) override {
        for (auto c : clients) {
            c->trackEvent(name, data);
        }
    }
};

/* =========================
   Metrics Manager (Client)
   ========================= */

class MetricsManager {
    MetricsStrategy* strategy;
public:
    void setStrategy(MetricsStrategy* s) {
        strategy = s;
    }

    void track(const string& name, const string& data) {
        strategy->sendEvent(name, data);
    }
};

/* =========================
   Client Usage
   ========================= */

int main() {
    // Base adapters
    MetricsClient* ga = new GoogleAnalyticsAdapter();
    MetricsClient* mp = new MixpanelAdapter();

    // Decorate Google Analytics
    MetricsClient* loggedGa = new LoggingMetricsDecorator(ga);

    // Multi-provider strategy
    vector<MetricsClient*> providers = {
        loggedGa, mp
    };

    MetricsStrategy* strategy = new MultiProviderStrategy(providers);

    MetricsManager manager;
    manager.setStrategy(strategy);

    manager.track("UserSignup", "{userId:42}");

    return 0;
}
