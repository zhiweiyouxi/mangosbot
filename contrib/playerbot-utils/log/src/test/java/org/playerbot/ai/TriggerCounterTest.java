package org.playerbot.ai;

import java.util.Date;

import org.junit.Test;
import org.playerbot.ai.domain.Log;
import org.playerbot.ai.processors.TriggerCounter;

public class TriggerCounterTest {
    private TriggerCounter counter = new TriggerCounter();

    @Test
    public void count() throws Exception {
        counter.process(new Log(new Date(), 0, "bot", "T", "trigger1", null));
        counter.process(new Log(new Date(), 0, "bot", "T", "trigger2", null));
        counter.process(new Log(new Date(), 0, "bot", "T", "trigger2", null));
        
        String report = counter.report();
        TestUtils.assertFileEquals("src/test/resources/TriggerCounter.txt", report);
    }

}
