#ifndef WARTHOG_CHAFBB_EXPANSION_POLICY_H
#define WARTHOG_CHAFBB_EXPANSION_POLICY_H

// contraction/chafbb_expansion_policy.h
//
// Contraction hierarchies + arc flags + bounding boxes
//
// @author: dharabor
// @created: 2016-05-10
//

#include "contraction.h"
#include "expansion_policy.h"
#include "planar_graph.h"

#include <vector>

namespace warthog{

class bbaf_filter;
class problem_instance;
class search_node;

class chafbb_expansion_policy : public  expansion_policy
{
    public:
        // NB: @param rank: the contraction ordering used to create
        // the graph. this is a total order given in the form of 
        // an array with elements v[x] = i where x is the id of the 
        // node and i is its contraction rank
        //
        // @param backward: when true successors are generated by following 
        // incoming arcs rather than outgoing arcs (default is outgoing)
        //
        // @param sd: determines which implicit graph of the hierarchy 
        // is being searched: the up graph or the down graph.
        // in the up graph all successors have a rank larger than the
        // current node (this is the default). in the down graph, all 
        // successors have a rank smaller than the current node 
        chafbb_expansion_policy(warthog::graph::planar_graph* g, 
                std::vector<uint32_t>* rank, 
                warthog::bbaf_filter* filter,
                bool backward=false,
                warthog::ch::search_direction sd = warthog::ch::UP);

        virtual 
        ~chafbb_expansion_policy() { }

		virtual void 
		expand(warthog::search_node*, warthog::problem_instance*);

        virtual void
        get_xy(uint32_t node_id, int32_t& x, int32_t& y)
        {
            g_->get_xy(node_id, x, y);
        }

        virtual size_t
        mem();

    private:
        bool backward_;
        warthog::graph::planar_graph* g_;
        std::vector<uint32_t>* rank_;
        warthog::ch::search_direction sd_;
        warthog::bbaf_filter* filter_;
        uint32_t search_id_;

        inline uint32_t
        get_rank(uint32_t id)
        {
            return rank_->at(id);
        }

};

}
#endif

