// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.

using System;
using System.Collections;

namespace fit {
    public class Summary : Fixture {
        public static String countsKey = "counts";

        public override void doTable(Parse table) {
            summary[countsKey] = counts.ToString();
            SortedList entries = new SortedList(summary);
            table.parts.more = rows(entries.Keys.GetEnumerator());
        }

        protected virtual Parse rows(IEnumerator keys) {
            if (keys.MoveNext()) {
                Object key = keys.Current;
                Parse result =
                    tr(
                    td(key.ToString(),
                    td(summary[key].ToString(),
                    null)),
                    rows(keys));
                if (key.Equals(countsKey)) {
                    mark (result);
                }
                return result;
            } else {
                return null;
            }
        }

        protected virtual Parse tr(Parse parts, Parse more) {
            return new Parse ("tr", null, parts, more);
        }

        protected virtual Parse td(string body, Parse more) {
            return new Parse ("td", info(body), null, more);
        }

        protected virtual void mark(Parse row) {
            // mark summary good/bad without counting beyond here
            Counts official = counts;
            counts = new Counts();
            Parse cell = row.parts.more;
            if (official.wrong + official.exceptions > 0) {
                wrong(cell);
            } else {
                right(cell);
            }
            counts = official;
        }
    }
}