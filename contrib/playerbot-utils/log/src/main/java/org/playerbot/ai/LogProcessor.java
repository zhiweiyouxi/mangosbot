package org.playerbot.ai;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import org.playerbot.ai.domain.Log;
import org.playerbot.ai.processors.ActionCounter;
import org.playerbot.ai.processors.CompositeProcessor;
import org.playerbot.ai.processors.NeverExecutedActionsFinder;
import org.playerbot.ai.processors.PatternFinder;
import org.playerbot.ai.processors.Processor;
import org.playerbot.ai.processors.ProcessorFactory;
import org.playerbot.ai.processors.TittledProcessor;
import org.playerbot.ai.processors.TriggerCounter;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class LogProcessor implements Runnable {
    private Logger logger = LoggerFactory.getLogger("output");

    private LogBuffer buffer;

    private Collection<Processor> processors = new ArrayList<Processor>();

    private void initProcessors() {
        processors.add(new CompositeProcessor(new ProcessorFactory() {
            
            @Override
            public Processor create() {
                return new PatternFinder(5);
            }
        }));
        
        processors.add(new TittledProcessor(new NeverExecutedActionsFinder()));
        
        processors.add(new CompositeProcessor(new ProcessorFactory() {
            
            @Override
            public Processor create() {
                return new NeverExecutedActionsFinder();
            }
        }));
        
        processors.add(new CompositeProcessor(new ProcessorFactory() {
            
            @Override
            public Processor create() {
                return new TriggerCounter();
            }
        }));

        String[] statuses = { "OK", "FAILED", "IMPOSSIBLE", "UNKNOWN" };
        for (final String status : statuses) {
            processors.add(new CompositeProcessor(new ProcessorFactory() {
                
                @Override
                public Processor create() {
                    return new ActionCounter(status);
                }
            }));
        }
    }
    
    public void run() {
        while (!buffer.isClosed() || !buffer.isEmpty()) {
            if (buffer.isEmpty()) {
                Thread.yield();
                continue;
            }
            List<Log> copy;
            synchronized (buffer) {
                copy = new ArrayList<Log>(buffer.getData());
                buffer.clear();
            }
            process(copy);
        }
        
        report();
    }

    private void report() {
        for (Processor processor : processors) {
            String report = processor.report();
            logger.info(report);
        }
    }

    private void process(List<Log> buffer) {
        for (Log entry : buffer) {
            try {
                process(entry);
            } catch (Exception e) {
                logger.error("Error processing entry " + entry, e);
            }
        }
    }

    
    private void process(Log entry) {
        for (Processor processor : processors) {
            processor.process(entry);
        }
    }

    public Thread startProcessing(LogBuffer buffer) {
        this.buffer = buffer;
        initProcessors();
        
        Thread thread = new Thread(this);
        thread.start();
        return thread;

    }
}
