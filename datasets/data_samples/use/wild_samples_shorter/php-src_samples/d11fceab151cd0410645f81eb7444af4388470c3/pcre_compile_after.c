          so far in order to get the number. If the name is not found, leave
          the value of recno as 0 for a forward reference. */

          /* This patch (removing "else") fixes a problem when a reference is
          to multiple identically named nested groups from within the nest.
          Once again, it is not the "proper" fix, and it results in an
          over-allocation of memory. */

          /* else */
            {
            ng = cd->named_groups;
            for (i = 0; i < cd->names_found; i++, ng++)
              {