package org.playerbot.ai.dao;

import java.util.Collection;
import java.util.List;

import org.playerbot.ai.domain.AbstractEntity;
import org.playerbot.ai.domain.Char;

public interface CharacterDao {

    <T extends AbstractEntity> void remove(final Class<T> type, final long output);

    <T extends AbstractEntity> void copy(final Class<T> type, final long output, T object)
            throws InstantiationException, IllegalAccessException;

    <T extends AbstractEntity> List<T> findAll(Class<T> type, long input);

    Char findCharacterWithSameClass(Long guid, Collection<Long> guidsToSearchIn);
}