#include "member.h"

#include <queue>
#include <limits>
#include "database.h"

namespace algdb {

void Member::DumpConnections() {
  std::cout << "(" << member_id << ")";
  for (auto &m : connecting_members) {
    auto conn = m.second;
    std::cout << "->" << conn.dst->member_id << 
      "(" << conn.group->group_id << ")";
  }
  std::cout << "\n";
}

void Member::PathToMemberBFS(uint64_t dst_member_id) {
  this->color = COLOR_GRAY;
  this->parent = NULL;
  std::queue<Member *> q;
  q.push(this);
  while (!q.empty()){
    auto x = q.front();
    q.pop();
     for(auto it = x->connecting_members.begin(); it != x->connecting_members.end(); ++it){
       auto curr = it->second.dst;
        if (curr->color == COLOR_WHITE){
          curr->color = COLOR_GRAY;
          curr->parent= x;
          q.push(curr);
        }
    }
    x->color = COLOR_BLACK;
  }
}

void Member::PathToMemberIDDFS(uint64_t dst_member_id) {
  // Fill in your code here
  for (int depth =0; depth < std::numeric_limits<double>::infinity(); depth++){
    auto found = DLS(this, depth, dst_member_id);
    if (found != NULL){
      //return found;
      break;
    }
  }
}
// Member* Member::DLS(Member *m, int depth, uint64_t dst_member_id){
//   if (depth == 0 && m->key == dst_member_id){
//     m->parent = NULL;
//     return m;
//   }
//     Member *found = new Member();
//   if (depth > 0){
//     for(auto it = m->connecting_members.begin(); it != m->connecting_members.end(); ++it){
//       it->second.dst->parent = m;
//         found = this->DLS(it->second.dst, depth-1, dst_member_id);  
//         if (found != NULL){
//           return found;
//         }
//   }
// }
// }
  
void Member::PrintPath(Member* dst) {
  Member *curr = dst;
  while(curr && curr != this) {
    std::cout << curr->member_name << " <- ";
    curr = curr->parent;
  }
  std::cout << this->member_name << "\n";
}

}
