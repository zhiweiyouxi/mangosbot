package org.playerbot.ai.processors;

import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

import org.playerbot.ai.domain.Log;

public class NeverExecutedActionsFinder implements Processor {
    
    private Set<String> actions = new TreeSet<String>(); 
    private Set<String> okActions = new HashSet<String>(); 

    @Override
    public void process(Log entry) {
        if (!"A".equals(entry.getEvent()))
            return;
        
        String action = entry.getText();
        if ("OK".equals(entry.getStatus())) {
            actions.remove(action);
            okActions.add(action);
        }
        else if (!okActions.contains(action)) {
            actions.add(action);
        }
    }
    
    @Override
    public String report() {
        StringBuilder sb = new StringBuilder();
        for (String action : actions) {
            sb.append(action);
            sb.append("\n");
        }
        return sb.toString();
    }

    @Override
    public String getName() {
        return "Never Executed Actions";
    }
}
