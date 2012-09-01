package org.playerbot.ai;

import java.util.Date;

import org.junit.Test;
import org.playerbot.ai.domain.Log;
import org.playerbot.ai.processors.NeverExecutedActionsFinder;

public class NeverExecutedActionsFinderTest {
    private NeverExecutedActionsFinder counter = new NeverExecutedActionsFinder();

    @Test
    public void count() throws Exception {
        counter.process(new Log(new Date(), 0, "bot", "A", "action1", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "action1", "IMPOSSIBLE"));
        counter.process(new Log(new Date(), 0, "bot", "A", "action2", "FAILED"));
    
        String report = counter.report();
        TestUtils.assertFileEquals("src/test/resources/NeverExecutedActionsFinder.txt", report);
    }

}
