// Copyright (c) 2002, 2003 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.

using System;

namespace fit {
    public class TimedActionFixture : ActionFixture {

    public string format = "hh:mm:ss";

        // Traversal ////////////////////////////////

        public override void doTable(Parse table) {
            base.doTable(table);
            table.parts.parts.last().more = td("time");
            table.parts.parts.last().more = td("split");
        }

        public override void DoCells(Parse cells) {
            DateTime start = time();
            base.DoCells(cells);
            long split = time().Ticks - start.Ticks;
            cells.last().more = td(start.ToString(format));
            cells.last().more = td(split<1000 ? "&nbsp;" : ((double)(split/1000.0)).ToString());
        }

        // Utility //////////////////////////////////

        public virtual DateTime time() {
            return DateTime.Now;
        }

        public virtual Parse td (String body) {
            return new Parse("td", info(body), null, null);
        }

    }
}