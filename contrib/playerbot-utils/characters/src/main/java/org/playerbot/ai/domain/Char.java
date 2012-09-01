package org.playerbot.ai.domain;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "characters")
public class Char extends AbstractEntity {
    @Id
    @Column
    private long guid;

    @Column(name = "class")
    private long charClass;

    public long getGuid() {
        return guid;
    }

    public void setGuid(long guid) {
        this.guid = guid;
    }

    public long getCharClass() {
        return charClass;
    }

    public void setCharClass(long charClass) {
        this.charClass = charClass;
    }



}
