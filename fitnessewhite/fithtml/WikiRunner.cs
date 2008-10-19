// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.

using System;
using System.IO;

namespace fit {
    public class WikiRunner : FileRunner {

        public static void Main (string[] argv) {
            new WikiRunner().run(argv);
        }

        public override void process() {
            try {
                string[] tags = {"wiki", "table", "tr", "td"};
                tables = new Parse(input, tags);    // look for wiki tag enclosing tables
                fixture.doTables(tables.parts);     // only do tables within that tag
            } catch (Exception e) {
                exception(e);
            }
            tables.print(output);
        }

    }
}