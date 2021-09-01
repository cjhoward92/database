#ifndef __RAFT_STATE__
#define __RAFT_STATE__

#include <string>

namespace raft {

enum State : unsigned char {
    Follower = 0,
    Candidate = 10,
    Leader = 20,
};

void initialize_raft_id();
std::string get_raft_id();

unsigned long get_follower_next_index(const char *follower_id);
void decrement_follower_next_index(const char *follower_id);
void increment_follower_next_index(const char *follower_id);

void update_term(unsigned long term);
unsigned long get_term();

unsigned long get_last_index();

/**
 * Sets the initial election timeout per host from between 100-500ms
 */
void reset_election_timeout();

/**
 * Retrieves the currently configured election timeout
 * in milliseconds
 */
unsigned long get_election_timeout();

}
#endif