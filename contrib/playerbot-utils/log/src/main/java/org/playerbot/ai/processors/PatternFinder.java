package org.playerbot.ai.processors;

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import org.playerbot.ai.domain.Log;

public class PatternFinder implements Processor {
    
    private List<String> tmpActions = new LinkedList<String>(); 
    private String[] actions; 
    private Map<String, Integer> patterns = new HashMap<String, Integer>();
    private List<String> alreadyProcessedPatterns = new LinkedList<String>();
    private int minCount;

    public PatternFinder(int minCount) {
        super();
        this.minCount = minCount;
    }

    @Override
    public void process(Log entry) {
        if (!"A".equals(entry.getEvent()) || !"OK".equals(entry.getStatus()))
            return;
        
        String action = entry.getText();
        tmpActions.add(action);
        
        if (tmpActions.size() > 1000) {
            calculate();
        }
    }
    
    @Override
    public String report() {
        calculate();
        
        for (String pattern : new HashSet<String>(patterns.keySet())) {
            if (patterns.get(pattern) < minCount)
                patterns.remove(pattern);
        }
        
        return CountFormatter.format(patterns);
    }

    private void calculate() {
        actions = tmpActions.toArray(new String[tmpActions.size()]);
        tmpActions.clear();
        alreadyProcessedPatterns.clear();

        for (int i = 10; i > 3; i--)
            calculate(i);
    }
    
    private void calculate(int length) {
        for (int i = 0; i < actions.length - length; i++) {
            calculate(i, length);
        }        
    }

    private void calculate(int start, int length) {
        String formattedPattern = format(start, length);
        if (alreadyProcessedPatterns.contains(formattedPattern))
            return;
        
        alreadyProcessedPatterns.add(formattedPattern);
        
        for (String existingPattern : patterns.keySet()) {
            if (existingPattern.contains(formattedPattern))
                return;
        }
        
        outer: for (int i = 1 + start; i <= actions.length - length; i++) {
            for (int j = 0; j < length; j++) {
                String patternString = actions[start + j];
                String actionString = actions[i + j];
                if (patternString.hashCode() != actionString.hashCode() && !patternString.equals(actionString))
                    continue outer;
            }
            add(formattedPattern);
        }
    }

    private String format(int start, int length) {
        StringBuilder sb = new StringBuilder();
        for (int i = start; i < start + length; i++)
            sb.append(",").append(actions[i]);
        return sb.length() > 0 ? sb.substring(1).toString() : "";
    }

    private void add(String pattern) {
        if (!patterns.containsKey(pattern))
            patterns.put(pattern, 1);
        
        patterns.put(pattern, patterns.get(pattern) + 1);
    }

    @Override
    public String getName() {
        return "Patterns";
    }
}
