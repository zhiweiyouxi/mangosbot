package org.playerbot.ai;

import java.io.File;
import java.io.IOException;

import junit.framework.Assert;

import org.apache.commons.io.FileUtils;

public abstract class TestUtils {
    public static void assertFileEquals(String fileName, String report) throws IOException {
        Assert.assertEquals(FileUtils.readFileToString(new File(fileName)).replaceAll("\r", ""), report.replaceAll("\r", ""));
    }

}
