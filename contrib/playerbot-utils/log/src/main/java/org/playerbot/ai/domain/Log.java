package org.playerbot.ai.domain;

import java.io.Serializable;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.apache.commons.lang.builder.EqualsBuilder;
import org.apache.commons.lang.builder.HashCodeBuilder;

public class Log implements Serializable {
    private static final long serialVersionUID = 1L;

    public static final SimpleDateFormat DATE_FORMAT = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    private static class Key implements Serializable {
        private static final long serialVersionUID = 1L;
        
        public Key() {
            super();
        }

        public Key(Date date, long number) {
            this.date = date;
            this.number = number;
        }

        private Date date;

        private long number;
        
        @Override
        public int hashCode() {
            return new HashCodeBuilder().append(date).append(number).toHashCode();
        }

        @Override
        public boolean equals(Object obj) {
            if (this == obj)
                return true;

            if (obj == null || getClass() != obj.getClass())
                return false;

            return new EqualsBuilder().append(date, ((Key) obj).date).append(number, ((Key) obj).number).isEquals();
        }
    }
    
    private Key key = new Key();

    private String bot;

    private String event;

    private String text;

    private String status;

    public Log() {
        super();
    }

    public Log(Date date, long number, String bot, String event, String text, String status) {
        super();
        this.key = new Key(date, number);
        this.bot = bot;
        this.event = event;
        this.text = text;
        this.status = status;
    }

    public Date getDate() {
        return key.date;
    }

    public void setDate(Date date) {
        key.date = date;
    }

    public long getNumber() {
        return key.number;
    }
    
    public void setNumber(long number) {
        key.number = number;
    }
    
    public String getBot() {
        return bot;
    }

    public void setBot(String bot) {
        this.bot = bot;
    }

    public String getEvent() {
        return event;
    }

    public void setEvent(String event) {
        this.event = event;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return String.format("%s.%d %s %s:%s", DATE_FORMAT.format(key.date), key.number, bot, event, text);
    }

    @Override
    public int hashCode() {
        return key.hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;

        if (obj == null || getClass() != obj.getClass())
            return false;

        return key.equals(((Log) obj).key);
    }

}
