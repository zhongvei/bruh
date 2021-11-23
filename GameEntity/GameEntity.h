#ifndef GAMEENTITY_H
#define GAMEENTITY_H

class GameEntity
{
public:
    enum class category{
        TANK,
        BULLET,
        BLOCK
    };

    ~GameEntity() = default;

    double get_max_health() const;
    void set_max_health(double max_health);

    double get_health() const;
    void set_health(double health);

    double get_health_regen() const;
    void set_health_regen(double health_regen);

    int get_size() const;
    void set_size(int size);

    double get_vx() const;
    double get_vy() const;
    void set_vx(int vx);
    void set_vy(int vy);

    double get_xp() const;
    void set_xp(double xp);

    int get_level() const;
    void set_level(int level);

private:

    double max_health {};
    double health {};
    double health_regen {};

    int size {};
    int vx{}, vy{};
    double xp{};
    int level{};


protected:
    GameEntity(const double& health, const double& health_regen, const double& max_health, const int& size,
               const int& vx, const int& vy,const double& xp,const int& level);

};

#endif // GAMEENTITY_H
