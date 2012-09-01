package org.playerbot.ai.processors;

import org.playerbot.ai.domain.Log;

public interface Processor {
    void process(Log entry);

    String report();

    String getName();
}
