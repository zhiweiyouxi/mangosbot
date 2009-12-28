#pragma once

class PlayerBotAiAware 
{
public:
    PlayerBotAiAware(PlayerbotAI* const ai) { this->ai = ai; }

protected:
    PlayerbotAI* ai;
};