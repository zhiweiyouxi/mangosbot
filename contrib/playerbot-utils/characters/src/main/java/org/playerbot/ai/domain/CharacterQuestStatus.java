package org.playerbot.ai.domain;

import java.io.Serializable;

import javax.persistence.Column;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table(name = "character_queststatus")
public class CharacterQuestStatus extends AbstractEntity {
    public static class Key implements Serializable {
        @Column
        private long guid;
        @Column
        private long quest;
    }

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

    @Column
    private long status;

    @Column
    private long rewarded;

    @Column
    private long explored;

    @Column
    private long timer;

    @Column
    private long mobcount1;

    @Column
    private long mobcount2;

    @Column
    private long mobcount3;

    @Column
    private long mobcount4;

    @Column
    private long itemcount1;

    @Column
    private long itemcount2;

    @Column
    private long itemcount3;

    @Column
    private long itemcount4;

    @Column
    private long itemcount5;

    @Column
    private long itemcount6;

    public long getQuest() {
        return key.quest;
    }

    public void setQuest(long quest) {
        key.quest = quest;
    }

    public long getStatus() {
        return status;
    }

    public void setStatus(long status) {
        this.status = status;
    }

    public long getRewarded() {
        return rewarded;
    }

    public void setRewarded(long rewarded) {
        this.rewarded = rewarded;
    }

    public long getExplored() {
        return explored;
    }

    public void setExplored(long explored) {
        this.explored = explored;
    }

    public long getTimer() {
        return timer;
    }

    public void setTimer(long timer) {
        this.timer = timer;
    }

    public long getMobcount1() {
        return mobcount1;
    }

    public void setMobcount1(long mobcount1) {
        this.mobcount1 = mobcount1;
    }

    public long getMobcount2() {
        return mobcount2;
    }

    public void setMobcount2(long mobcount2) {
        this.mobcount2 = mobcount2;
    }

    public long getMobcount3() {
        return mobcount3;
    }

    public void setMobcount3(long mobcount3) {
        this.mobcount3 = mobcount3;
    }

    public long getMobcount4() {
        return mobcount4;
    }

    public void setMobcount4(long mobcount4) {
        this.mobcount4 = mobcount4;
    }

    public long getItemcount1() {
        return itemcount1;
    }

    public void setItemcount1(long itemcount1) {
        this.itemcount1 = itemcount1;
    }

    public long getItemcount2() {
        return itemcount2;
    }

    public void setItemcount2(long itemcount2) {
        this.itemcount2 = itemcount2;
    }

    public long getItemcount3() {
        return itemcount3;
    }

    public void setItemcount3(long itemcount3) {
        this.itemcount3 = itemcount3;
    }

    public long getItemcount4() {
        return itemcount4;
    }

    public void setItemcount4(long itemcount4) {
        this.itemcount4 = itemcount4;
    }

    public long getItemcount5() {
        return itemcount5;
    }

    public void setItemcount5(long itemcount5) {
        this.itemcount5 = itemcount5;
    }

    public long getItemcount6() {
        return itemcount6;
    }

    public void setItemcount6(long itemcount6) {
        this.itemcount6 = itemcount6;
    }

}
