#include <uuid/uuid.h>

#include "state.h"

namespace raft
{
    static uuid_t _id;
    static std::string uuid_str;

    void initialize_raft_id() {
        uuid_generate(_id);

        char* out = (char *)malloc(37); // size required for uuid
        uuid_unparse_lower(_id, out);
        uuid_str = std::string(out);
        free(out);
    }

    std::string get_raft_id() {
        return uuid_str;
    }
} // namespace raft