package org.playerbot.ai.domain;

import java.io.Serializable;

import javax.persistence.Column;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table(name = "character_spell")
public class CharacterSpell extends AbstractEntity  {
    public static class Key implements Serializable {
        @Column
        private long guid;
        @Column
        private long spell;
    }

    @EmbeddedId
    private Key key = new Key();
    @Column
    private boolean active;
    @Column
    private boolean disabled;

    @Override
    public long getGuid() {
        return key.guid;
    }

    @Override
    public void setGuid(long guid) {
        key.guid = guid;
    }

    public long getSpell() {
        return key.spell;
    }

    public void setSpell(long spell) {
        key.spell = spell;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }

    public boolean isDisabled() {
        return disabled;
    }

    public void setDisabled(boolean disabled) {
        this.disabled = disabled;
    }

}
