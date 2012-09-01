package org.playerbot.ai.processors;

import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

import org.playerbot.ai.domain.Log;

public class CompositeProcessor implements Processor {
    private Map<String, Processor> map = new HashMap<String, Processor>();

    private ProcessorFactory factory;
    
    public CompositeProcessor(ProcessorFactory factory) {
        super();
        this.factory = factory;
    }

    @Override
    public void process(Log entry) {
        String bot = entry.getBot();
        if (!map.containsKey(bot))
            map.put(bot, factory.create());
        
        map.get(bot).process(entry);
    }

    @Override
    public String report() {
        StringBuilder sb = new StringBuilder();
        for (Entry<String, Processor> entry : map.entrySet()) {
            Processor processor = entry.getValue();
            
            sb.append("======================================================================\n");
            sb.append(String.format("%s - %s\n", entry.getKey(), processor.getName()));
            sb.append("======================================================================\n");
            
            sb.append(processor.report());
        }
        return sb.toString();
    }

    @Override
    public String getName() {
        return "Composite";
    }

}
