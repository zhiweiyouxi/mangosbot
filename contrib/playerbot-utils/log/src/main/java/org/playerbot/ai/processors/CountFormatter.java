package org.playerbot.ai.processors;

import java.util.Map;
import java.util.Map.Entry;
import java.util.TreeMap;

import org.playerbot.ai.ValueComparator;

public class CountFormatter {
    
    public static String format(Map<String, Integer> count) {
        Map<String, Integer> map = new TreeMap<String, Integer>(new ValueComparator<Integer>(count));
        map.putAll(count);
        
        StringBuilder sb = new StringBuilder();
        for (Entry<String, Integer> entry : map.entrySet()) {
            sb.append(String.format("%8d %s", entry.getValue(), entry.getKey()));
            sb.append("\n");
        }
        return sb.toString();
    }

}
