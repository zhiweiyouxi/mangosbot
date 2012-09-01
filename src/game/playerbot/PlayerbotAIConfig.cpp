#include "../pchdef.h"
#include "PlayerbotAIConfig.h"
#include "Policies/SingletonImp.h"
#include "playerbot.h"

using namespace std;

INSTANTIATE_SINGLETON_1(PlayerbotAIConfig);

PlayerbotAIConfig::PlayerbotAIConfig()
{
}

bool PlayerbotAIConfig::Initialize()
{
    sLog.outString("Initializing AI Playerbot by ike3, based on the original Playerbot by blueboy");

    if (!config.SetSource("aiplayerbot.conf"))
    {
        sLog.outString("AI Playerbot is Disabled. Unable to open configuration file aiplayerbot.conf");
        return false;
    }

    enabled = config.GetBoolDefault("AiPlayerbot.Enabled", true);
    if (!enabled)
        sLog.outString("AI Playerbot is Disabled in aiplayerbot.conf");

    globalCoolDown = (uint32) config.GetIntDefault("AiPlayerbot.GlobalCooldown", 500);
    teleportDelay = config.GetIntDefault("AiPlayerbot.TeleportDelay", 10000);
    reactDelay = (uint32) config.GetIntDefault("AiPlayerbot.ReactDelay", 100);

    sightDistance = config.GetFloatDefault("AiPlayerbot.SightDistance", 50.0f);
    spellDistance = config.GetFloatDefault("AiPlayerbot.SpellDistance", 25.0f);
    reactDistance = config.GetFloatDefault("AiPlayerbot.ReactDistance", 100.0f);
    grindDistance = config.GetFloatDefault("AiPlayerbot.GrindDistance", 75.0f);
    lootDistance = config.GetFloatDefault("AiPlayerbot.LootDistance", 20.0f);
    fleeDistance = config.GetFloatDefault("AiPlayerbot.FleeDistance", 15.0f);
    tooCloseDistance = config.GetFloatDefault("AiPlayerbot.TooCloseDistance", 7.0f);
    meleeDistance = config.GetFloatDefault("AiPlayerbot.MeleeDistance", 2.0f);
    followDistance = config.GetFloatDefault("AiPlayerbot.FollowDistance", 2.0f);

    criticalHealth = config.GetIntDefault("AiPlayerbot.CriticalHealth", 25);
    lowHealth = config.GetIntDefault("AiPlayerbot.LowHealth", 45);
    mediumHealth = config.GetIntDefault("AiPlayerbot.MediumHealth", 65);
    almostFullHealth = config.GetIntDefault("AiPlayerbot.AlmostFullHealth", 85);
    lowMana = config.GetIntDefault("AiPlayerbot.LowMana", 15);
    mediumMana = config.GetIntDefault("AiPlayerbot.MediumMana", 40);

    randomGearQuality = config.GetIntDefault("AiPlayerbot.RandomGearQuality", ITEM_QUALITY_RARE);

    iterationsPerTick = config.GetIntDefault("AiPlayerbot.IterationsPerTick", 10);

    allowGuildBots = config.GetBoolDefault("AiPlayerbot.AllowGuildBots", true);
    string accountStr = config.GetStringDefault("AiPlayerbot.RandomBotAccounts", "");
    vector<string> accounts = split(accountStr, ',');
    for (vector<string>::iterator i = accounts.begin(); i != accounts.end(); i++)
    {
        uint32 id = atoi((*i).c_str());
        if (!id)
            continue;
        randomBotAccounts.push_back(id);
    }

    string mapStr = config.GetStringDefault("AiPlayerbot.RandomBotMaps", "0,1,530,571");
    vector<string> maps = split(mapStr, ',');
    for (vector<string>::iterator i = maps.begin(); i != maps.end(); i++)
    {
        uint32 id = atoi((*i).c_str());
        if (!id)
            continue;
        randomBotMaps.push_back(id);
    }

    randomBotAutologin = config.GetBoolDefault("AiPlayerbot.RandomBotAutologin", false);
    minRandomBots = config.GetIntDefault("AiPlayerbot.MinRandomBots", 1);
    maxRandomBots = config.GetIntDefault("AiPlayerbot.MaxRandomBots", 10);
    randomBotUpdateInterval = config.GetIntDefault("AiPlayerbot.RandomBotUpdateInterval", 60);
    randomBotCountChangeInterval = config.GetIntDefault("AiPlayerbot.RandomBotCountChangeInterval", 5 * 24 * 3600);
    minRandomBotInWorldTime = config.GetIntDefault("AiPlayerbot.MinRandomBotInWorldTime", 2 * 3600);
    maxRandomBotInWorldTime = config.GetIntDefault("AiPlayerbot.MaxRandomBotInWorldTime", 14 * 24 * 3600);
    minRandomBotRandomizeTime = config.GetIntDefault("AiPlayerbot.MinRandomBotRandomizeTime", 2 * 3600);
    maxRandomRandomizeTime = config.GetIntDefault("AiPlayerbot.MaxRandomRandomizeTime", 14 * 24 * 3600);
    minRandomBotPvpTime = config.GetIntDefault("AiPlayerbot.MinRandomBotPvpTime", 120);
    maxRandomBotPvpTime = config.GetIntDefault("AiPlayerbot.MaxRandomBotPvpTime", 3 * 3600);
    randomBotTeleportDistance = config.GetIntDefault("AiPlayerbot.RandomBotTeleportDistance", 400);
    minRandomBotsPerInterval = config.GetIntDefault("AiPlayerbot.MinRandomBotsPerInterval", 1);
    maxRandomBotsPerInterval = config.GetIntDefault("AiPlayerbot.MaxRandomBotsPerInterval", 5);
    randomBotEnemyPercent = config.GetIntDefault("AiPlayerbot.RandomBotEnemyPercent", 30);

    splineFacing = config.GetBoolDefault("AiPlayerbot.SplineFacing", true);

    sLog.outString("AI Playerbot configuration loaded");
    return true;
}


bool PlayerbotAIConfig::IsInRandomAccountList(uint32 id)
{
    return find(randomBotAccounts.begin(), randomBotAccounts.end(), id) != randomBotAccounts.end();
}

string PlayerbotAIConfig::GetValue(string name)
{
    ostringstream out;

    if (name == "GlobalCooldown")
        out << globalCoolDown;
    else if (name == "TeleportDelay")
        out << teleportDelay;
    else if (name == "ReactDelay")
        out << reactDelay;

    else if (name == "SightDistance")
        out << sightDistance;
    else if (name == "SpellDistance")
        out << spellDistance;
    else if (name == "ReactDistance")
        out << reactDistance;
    else if (name == "GrindDistance")
        out << grindDistance;
    else if (name == "LootDistance")
        out << lootDistance;
    else if (name == "FleeDistance")
        out << fleeDistance;

    else if (name == "CriticalHealth")
        out << criticalHealth;
    else if (name == "LowHealth")
        out << lowHealth;
    else if (name == "MediumHealth")
        out << mediumHealth;
    else if (name == "AlmostFullHealth")
        out << almostFullHealth;
    else if (name == "LowMana")
        out << lowMana;


    else if (name == "RandomGearQuality")
        out << randomGearQuality;
    else if (name == "IterationsPerTick")
        out << iterationsPerTick;

    return out.str();
}

void PlayerbotAIConfig::SetValue(string name, string value)
{
    istringstream out(value, istringstream::in);

    if (name == "GlobalCooldown")
        out >> globalCoolDown;
    else if (name == "TeleportDelay")
        out >> teleportDelay;
    else if (name == "ReactDelay")
        out >> reactDelay;

    else if (name == "SightDistance")
        out >> sightDistance;
    else if (name == "SpellDistance")
        out >> spellDistance;
    else if (name == "ReactDistance")
        out >> reactDistance;
    else if (name == "GrindDistance")
        out >> grindDistance;
    else if (name == "LootDistance")
        out >> lootDistance;
    else if (name == "FleeDistance")
        out >> fleeDistance;

    else if (name == "CriticalHealth")
        out >> criticalHealth;
    else if (name == "LowHealth")
        out >> lowHealth;
    else if (name == "MediumHealth")
        out >> mediumHealth;
    else if (name == "AlmostFullHealth")
        out >> almostFullHealth;
    else if (name == "LowMana")
        out >> lowMana;

    else if (name == "RandomGearQuality")
        out >> randomGearQuality;
    else if (name == "IterationsPerTick")
        out >> iterationsPerTick;
}
