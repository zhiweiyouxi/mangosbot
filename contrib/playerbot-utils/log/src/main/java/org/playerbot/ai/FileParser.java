package org.playerbot.ai;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Date;

import org.playerbot.ai.domain.Log;

public class FileParser implements Runnable {
    
    protected static final int MAX_BUFFER_SIZE = 5000;

    private LineParser parser = new LineParser();
    
    private LogBuffer buffer;

    private String fileName;
    
    private long linesParsed = 0; 

    public Thread startParsing(LogBuffer buffer, String fileName) {
        this.buffer = buffer;
        this.fileName = fileName;
        Thread thread = new Thread(this);
        thread.start();
        return thread;
    }

    public void run() {
        try {
            runInternal();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    private void runInternal() throws FileNotFoundException, IOException {
        BufferedReader reader = new BufferedReader(new FileReader(fileName));
        String line;
        Date previoslyParsed = new Date();
        int millisToAdd = 0;
        while ((line = reader.readLine()) != null) {
            Log log = parser.parse(line);
            if (log == null)
                continue;

            if (log.getDate().equals(previoslyParsed)) {
                log.setNumber(++millisToAdd);
            }
            else {
                millisToAdd = 0;
            }
            
            previoslyParsed = log.getDate();
            
            while (buffer.size() > MAX_BUFFER_SIZE) {
                Thread.yield();
            }

            synchronized (buffer) {
                buffer.add(log);
            }
            
            linesParsed++;
        }
        reader.close();

        buffer.close();
    }

    public long getLinesParsed() {
        return linesParsed;
    }
}
