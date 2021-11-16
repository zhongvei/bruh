#ifndef TANK_H
#define TANK_H

#include "GameEntity.h"

class Tank: public GameEntity {
public:

    double get_attack_speed() const;
    void set_attack_speed(double attack_speed);

    double get_bullet_speed() const;
    void set_bullet_speed(double bullet_speed);

    double get_damage() const;
    void set_damage(double damage); 
    
private:
    double attack_speed;
    double bullet_speed;
    double damage;

protected:
    Tank(
        const double& health, const double& health_regen, const double& max_health, 
        const int& size, const int& vx, const int& vy,const double& xp,
        const double& attack_speed,
        const double& bullet_speed,
        const double& damage,
        const int& level
    );
};

//make all sub classes for the tank

#endif // TANK_H
