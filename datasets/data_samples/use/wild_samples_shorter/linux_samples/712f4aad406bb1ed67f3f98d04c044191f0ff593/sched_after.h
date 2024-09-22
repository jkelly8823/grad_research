	unsigned long mq_bytes;	/* How many bytes can be allocated to mqueue? */
#endif
	unsigned long locked_shm; /* How many pages of mlocked shm ? */
	unsigned long unix_inflight;	/* How many files in flight in unix sockets */

#ifdef CONFIG_KEYS
	struct key *uid_keyring;	/* UID specific keyring */
	struct key *session_keyring;	/* UID's default session keyring */