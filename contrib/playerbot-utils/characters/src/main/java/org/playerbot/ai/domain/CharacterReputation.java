package org.playerbot.ai.domain;

import java.io.Serializable;

import javax.persistence.Column;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table(name = "character_reputation")
public class CharacterReputation extends AbstractEntity {
    public static class Key implements Serializable {
        @Column
        private long guid;
        @Column
        private long faction;
    }

    @Column
    private long standing;
    @Column
    private long flags;
    @EmbeddedId
    private Key key = new Key();

    @Override
    public long getGuid() {
        return key.guid;
    }

    @Override
    public void setGuid(long guid) {
        key.guid = guid;
    }

    public long getFaction() {
        return key.faction;
    }

    public void setFaction(long faction) {
        key.faction = faction;
    }

    public long getStanding() {
        return standing;
    }

    public void setStanding(long standing) {
        this.standing = standing;
    }

    public long getFlags() {
        return flags;
    }

    public void setFlags(long flags) {
        this.flags = flags;
    }

}
