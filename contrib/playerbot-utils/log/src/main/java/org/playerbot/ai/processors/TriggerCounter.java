package org.playerbot.ai.processors;

import org.playerbot.ai.domain.Log;

public class TriggerCounter extends AbstractCounter {
    @Override
    public String getName() {
        return "Triggers";
    }

    @Override
    protected boolean isCountable(Log entry) {
        return "T".equals(entry.getEvent());
    }

}
