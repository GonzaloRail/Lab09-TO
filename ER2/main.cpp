#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

using namespace std;

// Clase Bullet es el base Prototype
class Bullet {
protected:
    string bulletName;
    float speed;
    float firePower;
    float damagePower;
    float direction;

public:
    Bullet() {}

    Bullet(string bulletName, float speed, float firePower, float damagePower)
        : bulletName(bulletName), speed(speed), firePower(firePower), damagePower(damagePower) {}

    virtual ~Bullet() {}

    virtual unique_ptr<Bullet> clone() = 0;

    void fire(float direction) {
        this->direction = direction;
        cout << "Name       : " << bulletName << endl
             << "Speed      : " << speed << endl
             << "FirePower  : " << firePower << endl
             << "DamagePower: " << damagePower << endl
             << "Direction  : " << direction << endl << endl;
    }
};

class SimpleBullet : public Bullet {
public:
    SimpleBullet(string bulletName, float speed, float firePower, float damagePower)
        : Bullet(bulletName, speed, firePower, damagePower) {}

    unique_ptr<Bullet> clone() override {
        return make_unique<SimpleBullet>(*this);
    }
};

// ** GoodBullet is the Concrete Prototype */
class GoodBullet : public Bullet {
public:
    GoodBullet(string bulletName, float speed, float firePower, float damagePower)
        : Bullet(bulletName, speed, firePower, damagePower) {}

    unique_ptr<Bullet> clone() override {
        return std::make_unique<GoodBullet>(*this);
    }
};

enum BulletType {
    SIMPLE,
    GOOD
};

class BulletFactory {
private:
    unordered_map<BulletType, unique_ptr<Bullet>, hash<int>> m_Bullets;

public:
    BulletFactory() {
        m_Bullets[SIMPLE] = make_unique<SimpleBullet>("Simple Bullet", 50, 75, 75);
        m_Bullets[GOOD] = make_unique<GoodBullet>("Good Bullet", 75, 100, 100);
    }

    unique_ptr<Bullet> createBullet(BulletType bulletType) {
        return m_Bullets[bulletType]->clone();
    }
};

int main() {
    BulletFactory bulletFactory;

    auto bullet = bulletFactory.createBullet(SIMPLE);
    bullet->fire(90);

    bullet = bulletFactory.createBullet(GOOD);
    bullet->fire(100);

    return 0;
}
