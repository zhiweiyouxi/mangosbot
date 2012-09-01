package org.playerbot.ai;

import java.util.Date;

import org.junit.Test;
import org.playerbot.ai.domain.Log;
import org.playerbot.ai.processors.ActionCounter;

public class ActionCounterTest {
    private ActionCounter counter = new ActionCounter("OK");

    @Test
    public void count() throws Exception {
        counter.process(new Log(new Date(), 0, "bot", "A", "action1", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "action2", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "action2", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "action3", "FAILED"));
        
        String report = counter.report();
        TestUtils.assertFileEquals("src/test/resources/ActionCounter.txt", report);
    }

}
