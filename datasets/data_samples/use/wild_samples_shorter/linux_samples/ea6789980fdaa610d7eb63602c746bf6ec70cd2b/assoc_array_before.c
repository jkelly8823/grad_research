		if ((edit->segment_cache[ASSOC_ARRAY_FAN_OUT] ^ base_seg) == 0)
			goto all_leaves_cluster_together;

		/* Otherwise we can just insert a new node ahead of the old
		 * one.
		 */
		goto present_leaves_cluster_but_not_new_leaf;
	}

split_node:
	pr_devel("split node\n");

	/* We need to split the current node; we know that the node doesn't
	 * simply contain a full set of leaves that cluster together (it
	 * contains meta pointers and/or non-clustering leaves).
	 *
	 * We need to expel at least two leaves out of a set consisting of the
	 * leaves in the node and the new leaf.
	 *
	 * We need a new node (n0) to replace the current one and a new node to
	 * take the expelled nodes (n1).
	 */
	pr_devel("<--%s() = ok [split node]\n", __func__);
	return true;

present_leaves_cluster_but_not_new_leaf:
	/* All the old leaves cluster in the same slot, but the new leaf wants
	 * to go into a different slot, so we create a new node to hold the new
	 * leaf and a pointer to a new node holding all the old leaves.
	 */
	pr_devel("present leaves cluster but not new leaf\n");

	new_n0->back_pointer = node->back_pointer;
	new_n0->parent_slot = node->parent_slot;
	new_n0->nr_leaves_on_branch = node->nr_leaves_on_branch;
	new_n1->back_pointer = assoc_array_node_to_ptr(new_n0);
	new_n1->parent_slot = edit->segment_cache[0];
	new_n1->nr_leaves_on_branch = node->nr_leaves_on_branch;
	edit->adjust_count_on = new_n0;

	for (i = 0; i < ASSOC_ARRAY_FAN_OUT; i++)
		new_n1->slots[i] = node->slots[i];

	new_n0->slots[edit->segment_cache[0]] = assoc_array_node_to_ptr(new_n0);
	edit->leaf_p = &new_n0->slots[edit->segment_cache[ASSOC_ARRAY_FAN_OUT]];

	edit->set[0].ptr = &assoc_array_ptr_to_node(node->back_pointer)->slots[node->parent_slot];
	edit->set[0].to = assoc_array_node_to_ptr(new_n0);
	edit->excised_meta[0] = assoc_array_node_to_ptr(node);
	pr_devel("<--%s() = ok [insert node before]\n", __func__);
	return true;

all_leaves_cluster_together:
	/* All the leaves, new and old, want to cluster together in this node
	 * in the same slot, so we have to replace this node with a shortcut to
	 * skip over the identical parts of the key and then place a pair of