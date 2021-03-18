/*
 * Project: p5
 * File: p5/additional.cpp
 * -----
 * File Created: Wednesday, 3rd March 2021 3:16:24 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:31:22 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include <string>
#include <iostream>

class creature
{
private:
    int strength;
    int hitpoints;

    virtual std::string get_species() const = 0;
public:
    creature() = default;
    constexpr creature(int strength, int hitpoints) noexcept :
        strength(strength), hitpoints(hitpoints)
    {}

    constexpr int get_strength() const noexcept { return strength; }
    constexpr void set_strength(int new_strength) noexcept { strength = new_strength; }

    constexpr int get_hitpoints() const noexcept { return hitpoints; }
    constexpr void set_hitpoints(int new_hitpoints) noexcept { hitpoints = new_hitpoints; }

    virtual int get_damage() const;
};

int creature::get_damage() const
{
    int damage = rand() % strength + 1;
    std::cout << get_species() << " attacks for " << damage << " points!" << std::endl;
    return damage;
}

class demon : public creature
{
public:
    demon() : creature() {}
    constexpr demon(int strength, int hitpoints) noexcept :
        creature(strength, hitpoints)
    {}

    int get_damage() const override;
};

int demon::get_damage() const
{
    constexpr int DEMONIC_ATTACK = 50;

    int damage = creature::get_damage();

    if (!(rand() % 20))
    {
        damage += DEMONIC_ATTACK;
        std::cout << "Demonic attack inflicts 50 additional damage points!" << std::endl;
    }

    return damage;
}

class elf : public creature
{
private:
    std::string get_species() const override;
public:
    elf() : creature() {}
    constexpr elf(int strength, int hitpoints) noexcept :
        creature(strength, hitpoints)
    {}

    int get_damage() const override;
};

int elf::get_damage() const
{
    int damage = creature::get_damage();

    if (!(rand() % 10))
    {
        std::cout << "Magical attack inflicts " << damage << " additional damage points!" << std::endl;
        damage *= 2;
    }

    return damage;
}

std::string elf::get_species() const
{
    return "Elf";
}

class human : public creature
{
private:
    std::string get_species() const override;
public:
    human() : creature() {}
    constexpr human(int strength, int hitpoints) noexcept :
        creature(strength, hitpoints)
    {}
};

std::string human::get_species() const
{
    return "Human";
}

class cyberdemon : public demon
{
private:
    std::string get_species() const override;
public:
    cyberdemon() : demon() {}
    constexpr cyberdemon(int strength, int hitpoints) noexcept :
        demon(strength, hitpoints)
    {}
};

std::string cyberdemon::get_species() const
{
    return "Cyberdemon";
}

class balrog : public demon
{
private:
    std::string get_species() const override;
public:
    balrog() : demon() {}
    constexpr balrog(int strength, int hitpoints) noexcept :
        demon(strength, hitpoints)
    {}

    int get_damage() const override;
};

int balrog::get_damage() const
{
    int damage = demon::get_damage();

    std::cout << "Speed attack, ";

    int additional_damage = creature::get_damage();

    return damage + additional_damage;
}

std::string balrog::get_species() const
{
    return "Balrog";
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    human h(10, 100);
    elf e(20, 100);
    balrog b(50, 100);
    cyberdemon c(75, 100);

    for (int i = 0; i < 10; ++i)
    {
        std::cout << h.get_damage() << std::endl;
        std::cout << e.get_damage() << std::endl;
        std::cout << b.get_damage() << std::endl;
        std::cout << c.get_damage() << std::endl;
    }

    return 0;
}