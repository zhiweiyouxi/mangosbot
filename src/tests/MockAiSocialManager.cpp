#include "pch.h"
#include "MockAiSocialManager.h"
#include "MockedTargets.h"

using namespace std;
using namespace ai;

void MockAiSocialManager::Emote(uint32 emote)
{
	buffer->append(">emote");
}

void MockAiSocialManager::TellMaster(const char* text)
{
	buffer->append(text);
}
