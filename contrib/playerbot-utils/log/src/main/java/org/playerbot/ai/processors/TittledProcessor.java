package org.playerbot.ai.processors;

import org.playerbot.ai.domain.Log;

public class TittledProcessor implements Processor {
    private Processor processor;

    public TittledProcessor(Processor processor) {
        super();
        this.processor = processor;
    }

    @Override
    public void process(Log entry) {
        processor.process(entry);
    }

    @Override
    public String report() {
        StringBuilder sb = new StringBuilder();
        sb.append("======================================================================\n");
        sb.append(processor.getName()).append("\n");
        sb.append("======================================================================\n");
        sb.append(processor.report()).append("\n");
        return sb.toString();
    }

    @Override
    public String getName() {
        return processor.getName();
    }
    
    
}
