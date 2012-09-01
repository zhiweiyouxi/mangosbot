package org.playerbot.ai;

import java.text.ParseException;
import java.util.Arrays;
import java.util.Collection;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.playerbot.ai.domain.Log;

public class LineParser {
    private static final Pattern PATTERN = Pattern
            .compile("(\\d\\d\\d\\d-\\d\\d-\\d\\d \\d\\d:\\d\\d:\\d\\d)\\s([a-zA-Z]+)\\s([a-zA-Z]+):(.+)");

    private static final String[] STATUSES = new String[] { "OK", "FAILED", "IMPOSSIBLE", "UNKNOWN", "USELESS" };

    private static final Collection<String> EVENTS = Arrays.asList(new String[] { "PUSH", "A", "T" });

    public Log parse(String line) {
        Matcher matcher = PATTERN.matcher(line);

        if (!matcher.find())
            return null;

        Log log = new Log();

        String dateTime = matcher.group(1);
        try {
            log.setDate(Log.DATE_FORMAT.parse(dateTime));
        } catch (ParseException e) {
            return null;
        }

        log.setBot(matcher.group(2));

        String event = matcher.group(3);
        if (!EVENTS.contains(event))
            return null;

        log.setEvent(event);

        String text = matcher.group(4);
        log.setText(text);
        for (String status : STATUSES) {
            if (text.endsWith("- " + status)) {
                log.setText(text.substring(0, text.length() - status.length() - 3));
                log.setStatus(status);
                break;
            }
        }

        return log;
    }
}
