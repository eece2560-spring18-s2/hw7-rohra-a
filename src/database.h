#ifndef DATABASE_H_
#define DATABASE_H_

#include <vector>
#include <unordered_map>

#include "event.h"
#include "group.h"
#include "member.h"

namespace algdb {

class Database{
 private:
  void LoadEventData(const std::string &event_file, int limit);
  void LoadMemberData(const std::string &member_file, int limit);
  void LoadGroupData(const std::string &group_file, int limit);
  void AssociateMembersWithGroups();

 public:
  std::vector<Event *> events;
  std::vector<Member *> members;
  std::vector<Group *> groups;

  std::unordered_map<uint64_t, Group *> group_id_hash_index;
  std::unordered_map<uint64_t, Member *> member_id_hash_index;

  Database();
  ~Database();
  void LoadData(const std::string &data_folder_path, 
                int event_limit, int member_limit, int group_limit);
  void BuildMemberGraph();
  void RandomizeGraph(int num_connections);

  double BestGroupsToJoin(Member *root);
};
struct Compare {
    bool operator()(const Member* l, const Member* r)  {
        return r->key < l->key;
    }
};

}

#endif  // DATABASE_H_
