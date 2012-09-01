package org.playerbot.ai;

import java.util.Date;

import org.junit.Test;
import org.playerbot.ai.domain.Log;
import org.playerbot.ai.processors.PatternFinder;

public class PatternFinderTest {
    private PatternFinder counter = new PatternFinder(1);

    @Test
    public void count() throws Exception {
        counter.process(new Log(new Date(), 0, "bot", "A", "a1", "OK"));
        
        counter.process(new Log(new Date(), 0, "bot", "A", "a2", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "a3", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "a4", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "a5", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "a6", "OK"));
        
        counter.process(new Log(new Date(), 0, "bot", "A", "a3", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "a4", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "a5", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "a6", "OK"));
        
        counter.process(new Log(new Date(), 0, "bot", "A", "a2", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "a3", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "a4", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "a5", "OK"));
        counter.process(new Log(new Date(), 0, "bot", "A", "a6", "OK"));
        
        String report = counter.report();
        TestUtils.assertFileEquals("src/test/resources/PatternFinder.txt", report);
    }

}
