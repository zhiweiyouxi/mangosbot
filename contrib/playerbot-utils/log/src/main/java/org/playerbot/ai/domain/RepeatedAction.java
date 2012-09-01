package org.playerbot.ai.domain;

public class RepeatedAction {
    private String name;
    private long count;

    public String getName() {
        return name;
    }

    public long getCount() {
        return count;
    }

    public RepeatedAction(String action, long count) {
        super();
        this.name = action;
        this.count = count;
    }

}
