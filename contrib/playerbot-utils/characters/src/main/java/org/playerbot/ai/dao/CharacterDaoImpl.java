package org.playerbot.ai.dao;

import java.util.Collection;
import java.util.List;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceException;

import org.playerbot.ai.domain.AbstractEntity;
import org.playerbot.ai.domain.Char;
import org.springframework.beans.BeanUtils;
import org.springframework.orm.jpa.JpaCallback;
import org.springframework.orm.jpa.support.JpaDaoSupport;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

@Repository
public class CharacterDaoImpl extends JpaDaoSupport implements CharacterDao {
    @Transactional
    public <T extends AbstractEntity> void remove(final Class<T> type, final long output) {
        getJpaTemplate().execute(new JpaCallback<T>() {
            public T doInJpa(EntityManager em) throws PersistenceException {
                em.createQuery("delete " + type.getSimpleName() + " where guid = ?").setParameter(1, output)
                        .executeUpdate();
                return null;
            }
        });
    }

    @Transactional
    public <T extends AbstractEntity> void copy(final Class<T> type, final long output, T object)
            throws InstantiationException, IllegalAccessException {
        T copy = type.newInstance();
        BeanUtils.copyProperties(object, copy);
        copy.setGuid(output);
        getJpaTemplate().persist(copy);
    }

    @SuppressWarnings("unchecked")
    @Transactional(readOnly = true)
    public <T extends AbstractEntity> List<T> findAll(Class<T> type, long input) {
        return getJpaTemplate().find("from " + type.getSimpleName() + " where guid = ?", input);
    }

    @Transactional(readOnly = true)
    public Char findCharacterWithSameClass(final Long guid, final Collection<Long> guidsToSearchIn) {
        return getJpaTemplate().execute(new JpaCallback<Char>() {
            public Char doInJpa(EntityManager em) throws PersistenceException {
                Char source = em.getReference(Char.class, guid);
                return (Char) em.createQuery("from Char c where c.guid in (:guidsToSearchIn) and c.charClass = :charClass")
                        .setParameter("guidsToSearchIn", guidsToSearchIn)
                        .setParameter("charClass", source.getCharClass()).setMaxResults(1).getSingleResult();
            }
        });
    }

}
