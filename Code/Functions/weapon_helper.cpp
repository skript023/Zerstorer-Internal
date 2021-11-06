#include "weapon_helper.hpp"
#include "../Classes/Weapon.h"
#include "../Natives.hpp"
#include "game_variable.hpp"

namespace big
{
    void weapon::infinite_ammo(bool Activation)
    {
        if (Activation)
        {
            for (auto WeaponHashes : var::AllWeaponHashes)
            {
                if (WEAPON::IS_WEAPON_VALID(joaat(WeaponHashes)))
                {
                    WEAPON::SET_PED_INFINITE_AMMO(PLAYER::PLAYER_PED_ID(), TRUE, joaat(WeaponHashes));
                }
            }
        }
        else
        {
            for (auto WeaponHashes : var::AllWeaponHashes)
            {
                if (WEAPON::IS_WEAPON_VALID(joaat(WeaponHashes)))
                {
                    WEAPON::SET_PED_INFINITE_AMMO(PLAYER::PLAYER_PED_ID(), FALSE, joaat(WeaponHashes));
                }
            }
        }
    }

    std::string weapon::get_weapon_name_from_hash(Hash weaponHash)
    {
        switch (weaponHash)
        {
        case WEAPON_UNARMED:
            return "Unarmed";
        case WEAPON_KNIFE:
            return "Knife";
        case WEAPON_NIGHTSTICK:
            return "Nightstick";
        case WEAPON_HAMMER:
            return "Hammer";
        case WEAPON_BAT:
            return "Bat";
        case WEAPON_GOLFCLUB:
            return "GolfClub";
        case WEAPON_CROWBAR:
            return "Crowbar";
        case WEAPON_PISTOL:
            return "Pistol";
        case WEAPON_PISTOL_MK2:
            return "Pistol MK2";
        case WEAPON_COMBATPISTOL:
            return "Combat Pistol";
        case WEAPON_APPISTOL:
            return "AP Pistol";
        case WEAPON_PISTOL50:
            return "Pistol 50";
        case WEAPON_MICROSMG:
            return "Micro SMG";
        case WEAPON_SMG:
            return "SMG";
        case WEAPON_SMG_MK2:
            return "SMG MK2";
        case WEAPON_ASSAULTSMG:
            return "Assault SMG";
        case WEAPON_ASSAULTRIFLE:
            return "Assault Riffle";
        case WEAPON_ASSAULTRIFLE_MK2:
            return "Assault Rifle MK2";
        case WEAPON_CARBINERIFLE:
            return "Carbine Riffle";
        case WEAPON_CARBINERIFLE_MK2:
            return "Carbine Riffle MK2";
        case WEAPON_ADVANCEDRIFLE:
            return "Advanced Riffle";
        case WEAPON_MG:
            return "MG";
        case WEAPON_COMBATMG:
            return "Combat MG";
        case WEAPON_COMBATMG_MK2:
            return "Combat MG MK2";
        case WEAPON_PUMPSHOTGUN:
            return "Pump Shotgun";
        case WEAPON_PUMPSHOTGUN_MK2:
            return "Pump Shotgun MK2";
        case WEAPON_SAWNOFFSHOTGUN:
            return "Sawed-Off Shotgun";
        case WEAPON_ASSAULTSHOTGUN:
            return "Assault Shotgun";
        case WEAPON_BULLPUPSHOTGUN:
            return "Bullpup Shotgun";
        case WEAPON_STUNGUN:
            return "Stun Gun";
        case WEAPON_SNIPERRIFLE:
            return "Sniper Rifle";
        case WEAPON_HEAVYSNIPER:
            return "Heavy Sniper";
        case WEAPON_HEAVYSNIPER_MK2:
            return "Heavy Sniper MK2";
        case WEAPON_GRENADELAUNCHER:
            return "Grenade Launcher";
        case WEAPON_GRENADELAUNCHER_SMOKE:
            return "Smoke Grenade Launcher";
        case WEAPON_RPG:
            return "RPG";
        case WEAPON_MINIGUN:
            return "Minigun";
        case WEAPON_GRENADE:
            return "Grenade";
        case WEAPON_STICKYBOMB:
            return "Sticky Bomb";
        case WEAPON_SMOKEGRENADE:
            return "Smoke Grenade";
        case WEAPON_BZGAS:
            return "BZGas";
        case WEAPON_MOLOTOV:
            return "Molotov";
        case WEAPON_FIREEXTINGUISHER:
            return "Fire Extinguisher";
        case WEAPON_PETROLCAN:
            return "Petrol Can";
        case 0xFDBADCED:
            return "Digital scanner";
        case 0x88C78EB7:
            return "Briefcase";
        case WEAPON_BALL:
            return "Ball";
        case WEAPON_FLARE:
            return "Flare";
        case WEAPON_BOTTLE:
            return "Bottle";
        case WEAPON_GUSENBERG:
            return "Gusenberg";
        case WEAPON_SPECIALCARBINE:
            return "Special Carabine";
        case WEAPON_SPECIALCARBINE_MK2:
            return "Special Carabine MK2";
        case WEAPON_HEAVYPISTOL:
            return "Heavy Pistol";
        case WEAPON_SNSPISTOL:
            return "SNS Pistol";
        case WEAPON_SNSPISTOL_MK2:
            return "SNS Pistol MK2";
        case WEAPON_BULLPUPRIFLE:
            return "Bullpup Rifle";
        case WEAPON_BULLPUPRIFLE_MK2:
            return "Bullpup Rifle MK2";
        case WEAPON_DAGGER:
            return "Dagger";
        case WEAPON_VINTAGEPISTOL:
            return "Vintage Pistol";
        case WEAPON_FIREWORK:
            return "Firework";
        case WEAPON_MUSKET:
            return "Musket";
        case WEAPON_HEAVYSHOTGUN:
            return "Heavy Shotgun";
        case WEAPON_MARKSMANRIFLE:
            return "Marksman Rifle";
        case WEAPON_MARKSMANRIFLE_MK2:
            return "Marksman Rifle MK2";
        case WEAPON_HOMINGLAUNCHER:
            return "Homing Launcher";
        case WEAPON_PROXMINE:
            return "Proximity Mine";
        case WEAPON_SNOWBALL:
            return "Snowball";
        case WEAPON_FLAREGUN:
            return "Flare Gun";
        case 0xE232C28C:
            return "Garbage Bag";
        case 0xD04C944D:
            return "Handcuffs";
        case WEAPON_COMBATPDW:
            return "Combat PDW";
        case WEAPON_MARKSMANPISTOL:
            return "Marksman Pistol";
        case WEAPON_KNUCKLE:
            return "Brass Knuckles";
        case WEAPON_RAILGUN:
            return "Railgun";
        case WEAPON_REVOLVER:
            return "Revolver";
        case WEAPON_REVOLVER_MK2:
            return "Revolver MK2";
        case WEAPON_COMBATSHOTGUN:
            return "Combat Shogun";
        case WEAPON_GADGETPISTOL:
            return "Perico Pistol";
        case WEAPON_MILITARYRIFLE:
            return "Military Rifle";
        }
        return "Unarmed";
    }
}