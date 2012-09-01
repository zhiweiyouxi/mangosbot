package org.playerbot.ai;

import java.util.Comparator;
import java.util.Map;

public class ValueComparator<T> implements Comparator<String> {
    private Map<String, T> base;

    public ValueComparator(Map<String, T> base) {
        this.base = base;
    }

    public int compare(String a, String b) {
        T o1 = base.get(a);
        T o2 = base.get(b);
        
        if (o1 != null && o2 == null)
            return -1;
        
        if (o2 != null && o1 == null)
            return 1;
        
        if (o1 instanceof Comparable<?> && o2 instanceof Comparable<?>) {
            int compared = ((Comparable) o2).compareTo(o1);
            return compared < 0 ? -1 : 1;
        }

        throw new IllegalArgumentException(String.format("Types %s and %s are not supported", o1.getClass(), o2.getClass()));
    }
}
