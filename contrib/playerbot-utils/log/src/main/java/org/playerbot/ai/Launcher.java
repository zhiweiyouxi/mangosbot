package org.playerbot.ai;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.PosixParser;

public class Launcher {
    
    private FileParser parser = new FileParser();

    private Watcher watcher = new Watcher();
    
    private LogProcessor processor = new LogProcessor();
    
    private LogBuffer buffer = new LogBuffer();
    

    public static void main(String[] args) throws Exception {
        Options options = new Options();
        options.addOption("in", true, "Input file");

        CommandLineParser parser = new PosixParser();
        CommandLine cmd = parser.parse(options, args);

        new Launcher().run(cmd.getOptionValue("in"));
    }

    private void run(String fileName) {
        parser.startParsing(buffer, fileName);
        watcher.startWatching(buffer, parser);
        processor.startProcessing(buffer);
    }

}
