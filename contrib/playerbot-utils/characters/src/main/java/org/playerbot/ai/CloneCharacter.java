package org.playerbot.ai;

import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import javax.inject.Inject;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.PosixParser;
import org.playerbot.ai.dao.CharacterDao;
import org.playerbot.ai.domain.AbstractEntity;
import org.playerbot.ai.domain.Char;
import org.playerbot.ai.domain.CharacterQuestStatus;
import org.playerbot.ai.domain.CharacterReputation;
import org.playerbot.ai.domain.CharacterSpell;
import org.playerbot.ai.domain.CharacterTalent;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.stereotype.Component;

import com.google.common.base.Function;
import com.google.common.collect.Collections2;

@Component
public class CloneCharacter {

    @Inject
    private CharacterDao dao;

    private static final Function<String, Long> stringToLong = new Function<String, Long>() {
        public Long apply(String s) {
            return Long.parseLong(s);
        }
    };

    public static void main(String[] args) throws Exception {
        Options options = new Options();
        options.addOption("in", true, "Input character guid");
        options.addOption("out", true, "Output character guid");

        CommandLineParser parser = new PosixParser();
        CommandLine cmd = parser.parse(options, args);

        ClassPathXmlApplicationContext ctx = new ClassPathXmlApplicationContext("classpath:/META-INF/context.xml");
        CloneCharacter bean = ctx.getBean(CloneCharacter.class);
        String[] in = cmd.getOptionValue("in").split(",");
        String[] out = cmd.getOptionValue("out").split(",");
        bean.run(Collections2.transform(Arrays.asList(in), stringToLong),
                Collections2.transform(Arrays.asList(out), stringToLong));
    }

    private void run(Collection<Long> in, Collection<Long> out) throws Exception {
        for (Long outGuid : out) {
            Char character = dao.findCharacterWithSameClass(outGuid, in);
            System.out.println(String.format("%d -> %d", character.getGuid(), outGuid));
            run(character.getGuid(), outGuid);
        }
    }

    public void run(long input, long output) throws Exception {
        List<CharacterSpell> spells = dao.findAll(CharacterSpell.class, input);
        replace(CharacterSpell.class, spells, output);

        List<CharacterReputation> reputation = dao.findAll(CharacterReputation.class, input);
        replace(CharacterReputation.class, reputation, output);

        List<CharacterQuestStatus> questStatus = dao.findAll(CharacterQuestStatus.class, input);
        replace(CharacterQuestStatus.class, questStatus, output);

        List<CharacterTalent> talents = dao.findAll(CharacterTalent.class, input);
        replace(CharacterTalent.class, talents, output);
    }

    private <T extends AbstractEntity> void replace(final Class<T> type, List<T> objects, final long output)
            throws Exception {
        dao.remove(type, output);

        for (T object : objects) {
            dao.copy(type, output, object);
        }
    }
}
