package org.playerbot.ai;

import java.util.LinkedList;
import java.util.Queue;

import org.playerbot.ai.domain.Log;

import com.google.common.base.Preconditions;

public class LogBuffer {
    private Queue<Log> data = new LinkedList<Log>();
    private volatile boolean closed = false;
    
    public boolean isClosed() {
        return closed;
    }
    
    public Queue<Log> getData() {
        return data;
    }

    public void close() {
        checkClosed();
        this.closed = true;
    }

    private void checkClosed() {
        Preconditions.checkState(!closed, "Buffer is closed");
    }

    public boolean isEmpty() {
        return data.isEmpty();
    }

    public void clear() {
        data.clear();
    }

    public long size() {
        return data.size();
    }

    public boolean add(Log log) {
        checkClosed();
        return data.add(log);
    }
}
