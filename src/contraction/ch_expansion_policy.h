#ifndef WARTHOG_CH_EXPANSION_POLICY_H
#define WARTHOG_CH_EXPANSION_POLICY_H

// contraction/ch_expansion_policy.h
//
// An expansion policy for contraction hierarchies. 
//
// For more details see:
// [Geisbergerger, Sanders, Schultes and Delling. 
// Contraction Hierarchies: Faster and Simpler Hierarchical 
// Routing in Road Networks. In Proceedings of the 2008
// Workshop on Experimental Algorithms (WEA)]
//
// @author: dharabor
// @created: 2016-05-10
//

#include "contraction.h"
#include "expansion_policy.h"
#include "planar_graph.h"

#include <vector>

namespace warthog{

class problem_instance;
class search_node;

class ch_expansion_policy : public  expansion_policy
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
        ch_expansion_policy(warthog::graph::planar_graph* g, 
                std::vector<uint32_t>* rank, 
                bool backward=false);

        virtual 
        ~ch_expansion_policy() { }

		virtual void 
		expand(warthog::search_node*, warthog::problem_instance*);

        virtual void
        get_xy(uint32_t node_id, int32_t& x, int32_t& y)
        {
            g_->get_xy(node_id, x, y);
        }

        inline uint32_t
        get_rank(uint32_t id)
        {
            return rank_->at(id);
        }

        inline uint32_t
        get_num_nodes() { return g_->get_num_nodes(); }

        virtual warthog::search_node* 
        generate_start_node(warthog::problem_instance* pi);

        virtual warthog::search_node*
        generate_target_node(warthog::problem_instance* pi);

        virtual size_t
        mem();

    private:
        bool backward_;
        warthog::graph::planar_graph* g_;
        std::vector<uint32_t>* rank_;

        // we use function pointers to optimise away a 
        // branching instruction when fetching successors
        typedef warthog::graph::edge_iter
                (warthog::ch_expansion_policy::*chep_get_iter_fn) 
                (warthog::graph::node* n);
        chep_get_iter_fn fn_begin_iter_;
        chep_get_iter_fn fn_end_iter_;

        inline warthog::graph::edge_iter
        get_fwd_begin_iter(warthog::graph::node* n) 
        { return n->outgoing_begin(); }

        inline warthog::graph::edge_iter
        get_fwd_end_iter(warthog::graph::node* n) 
        { return n->outgoing_end(); }

        inline warthog::graph::edge_iter
        get_bwd_begin_iter(warthog::graph::node* n) 
        { return n->incoming_begin(); }

        inline warthog::graph::edge_iter
        get_bwd_end_iter(warthog::graph::node* n) 
        { return n->incoming_end(); }
};

}
#endif

