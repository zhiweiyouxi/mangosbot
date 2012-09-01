package org.playerbot.ai;

import junit.framework.Assert;

import org.junit.Test;
import org.playerbot.ai.domain.Log;

public class LineParserTest {
    private LineParser parser = new LineParser();

    @Test
    public void parse() throws Exception {
        String line = "2011-10-22 12:49:07 Jeni PUSH:judgement of justice 16.030001";
        Log log = parser.parse(line);
        
        Assert.assertNotNull(log);
        Assert.assertEquals("2011-10-22 12:49:07.0 Jeni PUSH:judgement of justice 16.030001", log.toString());
    }
    
    @Test
    public void status() throws Exception {
        String line = "2011-10-22 12:49:07 Jeni A:cleave - OK";
        Log log = parser.parse(line);
        
        Assert.assertNotNull(log);
        Assert.assertEquals("2011-10-22 12:49:07.0 Jeni A:cleave", log.toString());
        Assert.assertEquals("OK", log.getStatus());
    }
    
    @Test
    public void parseInvalid() throws Exception {
        String line = "MM   MM         MM   MM  MMMMM   MMMM   MMMMM";
        Log log = parser.parse(line);
        Assert.assertNull(log);
    }
}
