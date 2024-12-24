#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class FoodItem {
protected:
    string name;
    string expire_date;

public:
    FoodItem(const string& name, const string& expire_date)
        : name(name), expire_date(expire_date) {}

    void setName(const string& newName) {
        name = newName;
    }

    void setExpire_date(const string& newExpire_date) {
        expire_date = newExpire_date;
    }

    virtual ~FoodItem() {}

    virtual void displayInfo() const {
        cout << "\nНазвание: " << name << "\nСрок годности: " << expire_date << endl;
    }
};


class Vegetable : public FoodItem {
private:
    string type;

public:
    Vegetable(const string& name, const string& expire_date, const string& type)
        : FoodItem(name, expire_date), type(type) {}

    void setType(const string& newType) {
        type = newType;
    }
    
    void displayInfo() const override {
        cout << "\nНазвание: " << name << "\nСрок годности: " << expire_date << "\nТип: " << type << endl;
    }
};


class DairyProduct : public FoodItem {
private:
    int fatity;

public:
    DairyProduct(const string& name, const string& expire_date, int fatity)
        : FoodItem(name, expire_date), fatity(fatity) {}

    void setFatity(int newFatity) {
        fatity = newFatity;
    }

    void displayInfo() const override {
        cout << "\nНазвание: " << name << "\nСрок годности: " << expire_date << "\nЖирность: " << fatity << "%" << endl;
    }
};


void modifyFoodItem(FoodItem* item, const string& newName, const string& newExpire_date) {
    item->setName(newName);
    item->setExpire_date(newExpire_date);

    Vegetable* vegetable = dynamic_cast<Vegetable*>(item);
    if (vegetable) {
        vegetable->setType("Изменённый овощ");
    }

    DairyProduct* dairy = dynamic_cast<DairyProduct*>(item);
    if (dairy) {
        dairy->setFatity(30);
    }
}


int main() {
    setlocale(LC_ALL, "rus");
    system("chcp 1251");

    vector<shared_ptr<FoodItem>> foodItems;

    foodItems.push_back(make_unique<Vegetable>("Морковь", "2025-06-21", "Корнеплод"));
    foodItems.push_back(make_unique<Vegetable>("Огурец", "2025-06-22", "Ягода"));
    foodItems.push_back(make_unique<DairyProduct>("Сливочное Масло", "2030-06-18", 80));

    cout << "\nПродукты на хранении: " << endl;
    for (const auto& item : foodItems) {
        item->displayInfo();
    }

    cout << "\nИзменение характеристик продуктов:" << endl;
    modifyFoodItem(foodItems[0].get(), "Картофель", "2025-06-18");

    cout << "\nПродукты на хранении: " << endl;
    for (const auto& item : foodItems) {
        item->displayInfo();
    }
}