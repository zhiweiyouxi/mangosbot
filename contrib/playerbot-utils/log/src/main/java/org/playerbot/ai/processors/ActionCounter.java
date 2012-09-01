package org.playerbot.ai.processors;

import org.playerbot.ai.domain.Log;

public class ActionCounter extends AbstractCounter {
    private final String status;
    
    public ActionCounter(String status) {
        super();
        this.status = status;
    }

    @Override
    public String getName() {
        return status;
    }

    @Override
    protected boolean isCountable(Log entry) {
        return "A".equals(entry.getEvent()) && status.equals(entry.getStatus());
    }

}
