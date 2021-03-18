/*
 * Project: p5
 * File: p5/additional_init.cpp
 * -----
 * File Created: Wednesday, 3rd March 2021 2:32:08 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:31:16 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include <iostream>
#include <string>

class creature
{
private:
    int type;
    int strength;
    int hitpoints;

    std::string get_species() const;
public:
    creature() = default;
    constexpr creature(int type, int strength, int hitpoints) noexcept :
        type(type), strength(strength), hitpoints(hitpoints)
    {}

    constexpr int get_type() const noexcept { return type; }
    constexpr void set_type(int new_type) noexcept { type = new_type; }

    constexpr int get_strength() const noexcept { return strength; }
    constexpr void set_strength(int new_strength) noexcept { strength = new_strength; }

    constexpr int get_hitpoints() const noexcept { return hitpoints; }
    constexpr void set_hitpoints(int new_hitpoints) noexcept { hitpoints = new_hitpoints; }

    int get_damage() const noexcept;
};

std::string creature::get_species() const
{
    switch(type)
    {
    case 0: 
        return "Human";
    case 1: 
        return "Cyberdemon";
    case 2: 
        return "Balrog";
    case 3: 
        return "Elf";
    }
}

int creature::get_damage() const
{
    constexpr int DEMONIC_ATTACK = 50;
    int damage = rand() % strength + 1;

    std::cout << get_species() << " attacks for " << damage << " points!" << std::endl;

    if ((type == 1 || type == 2) && !(rand() % 20))
    {
        damage += DEMONIC_ATTACK;
        std::cout << "Demonic attack inflicts 50 additional damage points!" << std::endl;
    }
    if (type == 3 && !(rand() % 10))
    {
        damage *= 2;
        std::cout << "Magical attack inflicts " << damage << " additional damage points!" << std::endl;
    }
    if (type == 2)
    {
        int additional_damage = rand() % strength + 1;
        std::cout << "Balrog speed attack inflicts " << additional_damage << " additional damage points!" << std::endl;
        damage += additional_damage;
    }
    return damage;
}