package org.playerbot.ai.domain;

import java.io.Serializable;

import javax.persistence.Column;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table(name = "character_talent")
public class CharacterTalent extends AbstractEntity {
    public static class Key implements Serializable {
        @Column
        private long guid;

        @Column(name = "talent_id")
        private long talent;

        @Column
        private long spec;
    }


    @EmbeddedId
    private Key key = new Key();
    @Column
    private long current_rank;

    @Override
    public long getGuid() {
        return key.guid;
    }

    @Override
    public void setGuid(long guid) {
        key.guid = guid;
    }

    public long getTalent() {
        return key.talent;
    }

    public void setTalent(long talent) {
        key.talent = talent;
    }

    public long getCurrent_rank() {
        return current_rank;
    }

    public void setCurrent_rank(long current_rank) {
        this.current_rank = current_rank;
    }

    public long getSpec() {
        return key.spec;
    }

    public void setSpec(long spec) {
        key.spec = spec;
    }

}
