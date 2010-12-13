#pragma once

namespace ai
{
	class CastSinisterStrikeAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastSinisterStrikeAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "sinister strike") {} 
	};

    class CastMutilateAction : public CastMeleeSpellAction 
    { 
    public: 
        CastMutilateAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "mutilate") {} 
    };

	class CastGougeAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastGougeAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "gouge") {} 
	};

    class CastBackstabAction : public CastMeleeSpellAction 
    { 
    public: 
        CastBackstabAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "backstab") {} 
    };
}