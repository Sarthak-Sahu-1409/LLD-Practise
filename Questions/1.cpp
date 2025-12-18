#include <iostream>
#include <string>
using namespace std;

/* =======================
   Strategy Interfaces
   ======================= */

class PaymentStrategy {
public:
    virtual void pay(double amount) = 0;
};

class DiscountStrategy {
public:
    virtual double apply(double amount) = 0;
};

/* =======================
   Payment Implementations
   ======================= */

class CreditCardPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        cout << "Paid " << amount << " using Credit Card\n";
    }
};

class UpiPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        cout << "Paid " << amount << " using UPI\n";
    }
};

class WalletPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        cout << "Paid " << amount << " using Wallet\n";
    }
};

/* =======================
   Discount Implementations
   ======================= */

class CouponDiscount : public DiscountStrategy {
public:
    double apply(double amount) override {
        cout << "Applying Coupon Discount (10%)\n";
        return amount * 0.90;
    }
};

class FestivalDiscount : public DiscountStrategy {
public:
    double apply(double amount) override {
        cout << "Applying Festival Discount (20%)\n";
        return amount * 0.80;
    }
};

class LoyaltyDiscount : public DiscountStrategy {
public:
    double apply(double amount) override {
        cout << "Applying Loyalty Discount (₹100 off)\n";
        return amount - 100;
    }
};

/* =======================
   Factories
   ======================= */

class PaymentFactory {
public:
    static PaymentStrategy* createPayment(const string& type) {
        if (type == "credit") return new CreditCardPayment();
        if (type == "upi") return new UpiPayment();
        if (type == "wallet") return new WalletPayment();
        return nullptr;
    }
};

class DiscountFactory {
public:
    static DiscountStrategy* createDiscount(const string& type) {
        if (type == "coupon") return new CouponDiscount();
        if (type == "festival") return new FestivalDiscount();
        if (type == "loyalty") return new LoyaltyDiscount();
        return nullptr;
    }
};

/* =======================
   Checkout Service
   ======================= */

class CheckoutService {
    PaymentStrategy* payment;
    DiscountStrategy* discount;

public:
    CheckoutService(PaymentStrategy* p, DiscountStrategy* d)
        : payment(p), discount(d) {}

    void checkout(double amount) {
        cout << "Original Amount: " << amount << "\n";
        double finalAmount = discount->apply(amount);
        cout << "Final Amount: " << finalAmount << "\n";
        payment->pay(finalAmount);
    }
};

/* =======================
   Client Code
   ======================= */

int main() {
    PaymentStrategy* payment =
        PaymentFactory::createPayment("upi");

    DiscountStrategy* discount =
        DiscountFactory::createDiscount("festival");

    CheckoutService checkout(payment, discount);
    checkout.checkout(1000);
  
    return 0;
}
