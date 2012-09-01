package org.playerbot.ai;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Watcher implements Runnable {
    private Logger logger = LoggerFactory.getLogger(getClass());
    
    private FileParser parser;
    private LogBuffer buffer;

    public void run() {
        while (!buffer.isClosed()) {
            logger.info(parser.getLinesParsed() + " lines parsed, " + Runtime.getRuntime().totalMemory() / 1024 / 1024 + "M");

            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
            }
        }
    }

    public Thread startWatching(LogBuffer buffer, FileParser parser) {
        this.buffer = buffer;
        this.parser = parser;
        
        Thread thread = new Thread(this);
        thread.start();
        return thread;
    }
}