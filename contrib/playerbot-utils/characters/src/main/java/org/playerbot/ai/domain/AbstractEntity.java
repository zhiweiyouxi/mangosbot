package org.playerbot.ai.domain;

import java.io.Serializable;

import javax.persistence.MappedSuperclass;

@MappedSuperclass
public abstract class AbstractEntity implements Serializable {


    public AbstractEntity() {
        super();
    }

    public abstract long getGuid();

    public abstract void setGuid(long guid);

}